//   目前這份 沒有支援線段／射線插入；insert(line x) 代表這條線在整個 \([0,\text{maxn})\) 都有效。

// 但這份結構很好改，直接外掛一個 range insert：

// void insert_seg(line x, int ql, int qr,
//                 int i = 1, int l = 0, int r = maxn) {
//     if (qr <= l || r <= ql) return;
//     if (ql <= l && r <= qr) {
//         insert(x, i, l, r);
//         return;
//     }
//     insert_seg(x, ql, qr, i << 1, l, m);
//     insert_seg(x, ql, qr, i << 1 | 1, m, r);
// }

// 這樣：

// insert_seg(L, l, r);     // L 只在 [l,r) 有效
// insert_seg(L, x, maxn);  // 向右射線
// insert_seg(L, 0, x + 1); // 向左射線（若 x 是整數且含端點）

// 複雜度大約變成

// $$ O(\log^2 C) $$

// 每次 segment insertion；point query 還是 \(O(\log C)\)。

// 不過你們這份還有一個值得修的地方：arr 是 global static，所以預設 line 是 \(y=0\)。如果合法答案可能是負數，空節點會錯誤貢獻 0。最好加 bool has[] 或初始化成真正的 \(-\infty\) line。
