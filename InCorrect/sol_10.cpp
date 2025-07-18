#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;
const int MAXN = 100010;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Precompute pow2 up to n+2
    vector<ll> pow2(n + 2);
    pow2[0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    // Precompute for each divisor, the positions of elements divisible by it
    vector<vector<int>> pos_div(MAXN);
    for (int i = 1; i <= n; ++i) {
        int val = a[i];
        // Find all divisors of val
        for (int j = 1; j * j <= val; ++j) {
            if (val % j == 0) {
                pos_div[j].push_back(i);
                int other = val / j;
                if (other != j) {
                    pos_div[other].push_back(i);
                }
            }
        }
    }

    // Sort each pos_div list
    for (int i = 0; i < MAXN; ++i) {
        if (!pos_div[i].empty()) {
            sort(pos_div[i].begin(), pos_div[i].end());
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        // Count the number of elements in [l..r] divisible by x
        int k = 0;
        if (x >= MAXN) {
            // x is too large, no elements in pos_div[x]
            k = 0;
        } else {
            const vector<int>& arr = pos_div[x];
            int low = lower_bound(arr.begin(), arr.end(), l) - arr.begin();
            int high = upper_bound(arr.begin(), arr.end(), r) - arr.begin();
            k = high - low;
        }
        int m = (r - l + 1) - k;
        ll ans = ((ll)(k + 1) * pow2[m] % MOD - 1 + MOD) % MOD;
        cout << ans << endl;
    }

    return 0;
}