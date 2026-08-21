#define debug(...) cerr << "\x1b[33m" #__VA_ARGS__ ": \x1b[0m", \
    [](auto&&... a){ ((cerr << a << ' '), ...); }(__VA_ARGS__), cerr << '\n'
#define output(...) \
    [](auto&&... a){ ((cout << a << ' '), ...); }(__VA_ARGS__), cout << '\n'
int v = 42;
format("{:b}", v);   // "101010"
format("{:#b}", v);  // "0b101010"
format("{:#x}", v);  // "0x2a"
format("{:#X}", v);  // "0X2A"
int x = 7;
format("{:05d}", x);     // "00007"
format("{:>5}", x);      // "    7"
format("{:<5}", x);      // "7    "
format("{:^5}", x);      // "  7  "
format("{:*^5}", x);     // "**7**"
double pi = 3.1415926535;
format("{:.2f}", pi);    // "3.14"
