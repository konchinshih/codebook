  輸出每個 pattern 在 text 中第一次出現的位置，若不存在則輸出 -1。\
  走 AC 自動機時 `if (val[ptr] == -1) val[ptr] = i;` 接著 pull DP\
  `if (val[x] == -1) continue;`\
  `if (val[fail[x]] == -1) val[fail[x]] = val[x];`\
  `else val[fail[x]] = min(val[fail[x]], val[x]);`\
