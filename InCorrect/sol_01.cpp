#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const int MAXN = 1e5 + 5;

ll power(ll a, ll b, ll mod) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int q;
    cin >> q;
    
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        // Convert to 0-based index
        l -= 1;
        r -= 1;
        
        int d = 0;
        for (int i = l; i <= r; ++i) {
            if (a[i] % x == 0) {
                ++d;
            }
        }
        int k = (r - l + 1) - d;
        ll pow_2_k = power(2, k, MOD);
        ll ans = (pow_2_k * (d + 1) % MOD - 1 + MOD) % MOD;
        cout << ans << '\n';
    }
    
    return 0;
}