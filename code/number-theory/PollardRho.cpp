// Author: Unknown
// Function: Find a non-trivial factor of a big number in O(n^(1/4) log^2(n))

ll find_factor(ll number) {
    __int128 x = 2;
    for (__int128 cycle = 1; ; cycle++) {
        __int128 y = x;
        for (int i = 0; i < (1<<cycle); i++) {
            x = (x * x + 1) % number; 
            __int128 factor = __gcd(x - y, number);
            if (factor > 1)
                return factor;
        }
    }
}
