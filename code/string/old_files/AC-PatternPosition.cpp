// Author: Gino, Return the first occurrence of each pattern in the text
  if (val[ptr] == -1) val[ptr] = i;  // ending index
   }
   for (int x : span(order, order_cnt) | views::reverse) {
     if (val[x] == -1) continue;
     if (val[fail[x]] == -1) val[fail[x]] = val[x];
      else val[fail[x]] = min(val[fail[x]], val[x]);
   }
   for (auto& i : pid)
     // ay(3)bab(5, val[i] == 4)
     cout << (val[i] == -1 ? val[i] : val[i] - len[i] + 2) << endl;
  } 