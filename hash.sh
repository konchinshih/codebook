SOURCEDIR='code'
OUTPUT='hash.sha256'
FILES="$(find "$SOURCEDIR" -type f)"

while IFS='' read -r file; do
  hval="$(openssl sha256 -r "$file" | cut -f1 -d' ')"
  printf '% 60s %s\n' "$file" "$hval"
done <<< "$FILES" | tee "$OUTPUT"
