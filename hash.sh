SOURCEDIR='code'
OUTPUT='hash.sha256'
FILES="$(find "$SOURCEDIR" -type f)"

while IFS='' read -r file; do
  tmpfile="$(mktemp)"
  if [[ "$file" == *.cpp ]]; then
    cpp -dD -P < "$file" | tr -d '[:space:]' > "$tmpfile"
  else
    cp "$file" "$tmpfile"
  fi
  hval="$(openssl sha256 -r "$tmpfile" | cut -f1 -d' ')"
  printf '% 60s %s\n' "$file" "$hval"
done <<< "$FILES" | tee "$OUTPUT"
