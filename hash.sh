SOURCEDIR='code'
OUTPUT='hash.sha256'
TMPFILE='/tmp/hashtmp'

calcHash(){
    printf '%s' "$1" | tr -d '[:space:]' > $TMPFILE
    printf '% 60s %s\n' "$1" "$(openssl sha256 "$TMPFILE" | cut -f2 -d' ')" >> $OUTPUT
    echo "$1 has been hashed"
}

FILES=$(find "$SOURCEDIR" | grep -P '.*/.*/.*')
FILECNT=$(echo "$FILES" | wc -l)
echo '' > $OUTPUT
i=1; while [ $i -le "$FILECNT" ]; do
    FILE=$(echo "$FILES" | tail -n "$i" | head -n1)
    calcHash "$FILE"
    i=$((i+1))
done
# clean tmp
rm "$TMPFILE"
