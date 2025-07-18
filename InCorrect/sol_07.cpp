#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 100005; // Slightly larger to handle up to 1e5 safely

// Precompute powers of 2 modulo MOD
int power[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // Precompute powers of 2
    power[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        power[i] = (1LL * power[i - 1] * 2) % MOD;
    }
    
    int n;
    cin >> n;
    vector<int> a(n + 1); // 1-indexed array
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    // For each x, store sorted list of indices where a[i] is divisible by x
    vector<vector<int>> divisors(MAXN);
    for (int i = 1; i <= n; ++i) {
        int val = a[i];
        // Efficiently find all divisors of val
        vector<int> divs;
        for (int d = 1; d * d <= val; ++d) {
            if (val % d == 0) {
                divs.push_back(d);
                if (d != val / d) {
                    divs.push_back(val / d);
                }
            }
        }
        // Add current index to all divisors of a[i]
        for (int d : divs) {
            if (d < MAXN) {
                divisors[d].push_back(i);
            }
        }
    }
    
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        
        // Count elements in [l, r] divisible by x
        int count_A = 0;
        if (x < MAXN && !divisors[x].empty()) {
            auto& vec = divisors[x];
            // Find lower and upper bounds in the sorted list
            auto left = lower_bound(vec.begin(), vec.end(), l);
            auto right_iter = upper_bound(vec.begin(), vec.end(), r);
            count_A = right_iter - left;
        }
        
        int total = r - l + 1;
        int count_B = total - count_A;
        
        // Calculate (count_A + 1) * 2^count_B - 1 mod MOD
        long long part1 = (1LL * (count_A + 1) * power[count_B]) % MOD;
        long long ans = (part1 - 1 + MOD) % MOD;
        cout << ans << endl;
    }
    
    return 0;
}