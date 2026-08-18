#!/usr/bin/env python3
"""Apply a semantic JSON palette to a TextMate .tmTheme file."""

from __future__ import annotations

import argparse
import colorsys
import json
import os
import plistlib
import re
import stat
import tempfile
from pathlib import Path
from typing import Any


HEX_COLOR = re.compile(r"^#[0-9A-Fa-f]{6}$")
NUMBER = r"[+-]?(?:\d+(?:\.\d*)?|\.\d+)"
HSL_COLOR = re.compile(
    rf"^hsl\(\s*({NUMBER})\s*(?:deg)?\s*,\s*({NUMBER})%\s*,\s*({NUMBER})%\s*\)$",
    re.IGNORECASE,
)
ALLOWED_SETTINGS = {"foreground", "fontStyle"}
REPO_ROOT = Path(__file__).resolve().parent


def fail(message: str) -> None:
    raise SystemExit(f"error: {message}")


def color_to_hex(label: str, value: str) -> str:
    """Convert a palette color to the #RRGGBB format used by tmTheme."""
    if HEX_COLOR.fullmatch(value):
        return value.upper()

    match = HSL_COLOR.fullmatch(value)
    if not match:
        fail(f"{label} must be #RRGGBB or hsl(H, S%, L%)")

    hue, saturation, lightness = (float(part) for part in match.groups())
    if not 0 <= saturation <= 100:
        fail(f"{label} saturation must be between 0 and 100")
    if not 0 <= lightness <= 100:
        fail(f"{label} lightness must be between 0 and 100")

    red, green, blue = colorsys.hls_to_rgb(
        (hue % 360) / 360,
        lightness / 100,
        saturation / 100,
    )
    channels = [
        max(0, min(255, int(channel * 255 + 0.5)))
        for channel in (red, green, blue)
    ]
    return "#{:02X}{:02X}{:02X}".format(*channels)


def load_palette(path: Path) -> dict[str, dict[str, str]]:
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError:
        fail(f"palette file not found: {path}")
    except json.JSONDecodeError as exc:
        fail(f"invalid JSON in {path}: {exc}")

    if not isinstance(data, dict):
        fail("the palette root must be an object")

    styles = data.get("styles", {})
    if not isinstance(styles, dict):
        fail("palette key 'styles' must be an object")

    def validate_settings(label: str, settings: Any) -> dict[str, str]:
        if not isinstance(settings, dict):
            fail(f"{label} must be an object")
        result: dict[str, str] = {}
        for key, value in settings.items():
            if key not in ALLOWED_SETTINGS:
                fail(f"{label} contains unsupported setting: {key}")
            if not isinstance(value, str):
                fail(f"{label}.{key} must be a string")
            result[key] = (
                color_to_hex(f"{label}.{key}", value)
                if key == "foreground"
                else value
            )
        return result

    validated_styles = {
        name: validate_settings(f"styles.{name}", settings)
        for name, settings in styles.items()
    }
    return validated_styles


def load_theme(path: Path) -> dict[str, Any]:
    try:
        with path.open("rb") as file:
            theme = plistlib.load(file)
    except FileNotFoundError:
        fail(f"theme file not found: {path}")
    except plistlib.InvalidFileException as exc:
        fail(f"invalid tmTheme file {path}: {exc}")

    if not isinstance(theme, dict) or not isinstance(theme.get("settings"), list):
        fail("the tmTheme must contain a settings array")
    return theme


def apply_palette(theme: dict[str, Any], styles: dict[str, dict[str, str]]) -> None:
    entries = theme["settings"]
    if not entries or not isinstance(entries[0], dict):
        fail("the tmTheme settings array has no base entry")
    base_settings = entries[0].get("settings")
    if not isinstance(base_settings, dict):
        fail("the tmTheme base entry has no settings object")
    # Typst ignores the global foreground/background settings.
    base_settings.pop("foreground", None)
    base_settings.pop("background", None)

    named_entries: dict[str, dict[str, Any]] = {}
    for entry in entries[1:]:
        if isinstance(entry, dict) and isinstance(entry.get("name"), str):
            named_entries[entry["name"]] = entry

    missing = sorted(set(styles) - set(named_entries))
    if missing:
        fail("theme styles not found: " + ", ".join(missing))

    for name, settings in styles.items():
        target = named_entries[name].get("settings")
        if not isinstance(target, dict):
            fail(f"theme style '{name}' has no settings object")
        # Per-scope backgrounds are not supported by Typst's raw theme model.
        target.pop("background", None)
        target.update(settings)


def write_theme(path: Path, theme: dict[str, Any]) -> None:
    payload = plistlib.dumps(theme, fmt=plistlib.FMT_XML, sort_keys=False)
    mode = stat.S_IMODE(path.stat().st_mode)
    descriptor, temporary_name = tempfile.mkstemp(
        dir=path.parent,
        prefix=f".{path.name}.",
        suffix=".tmp",
    )
    try:
        with os.fdopen(descriptor, "wb") as file:
            file.write(payload)
        os.chmod(temporary_name, mode)
        os.replace(temporary_name, path)
    except Exception:
        try:
            os.unlink(temporary_name)
        except FileNotFoundError:
            pass
        raise


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Apply a JSON palette to a TextMate .tmTheme file."
    )
    parser.add_argument(
        "--palette",
        type=Path,
        default=REPO_ROOT / "themes" / "codeblock-palette.json",
        help="palette JSON file (default: themes/codeblock-palette.json)",
    )
    parser.add_argument(
        "--theme",
        type=Path,
        default=REPO_ROOT / "themes" / "codeblock-theme.tmTheme",
        help="tmTheme file to update (default: themes/codeblock-theme.tmTheme)",
    )
    args = parser.parse_args()

    styles = load_palette(args.palette)
    theme = load_theme(args.theme)
    apply_palette(theme, styles)
    write_theme(args.theme, theme)
    print(f"updated {args.theme} from {args.palette}")


if __name__ == "__main__":
    main()
