#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
const int MAXN = 1e5 + 5;

int pow2[MAXN * 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // Precompute powers of 2 modulo MOD
    pow2[0] = 1;
    for (int i = 1; i < MAXN * 2; ++i) {
        pow2[i] = (1LL * pow2[i - 1] * 2) % MOD;
    }
    
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--; // Convert to 0-based index
        int A = 0, B = 0;
        for (int i = l; i < r; ++i) {
            if (a[i] % x == 0) {
                A++;
            } else {
                B++;
            }
        }
        int powB = pow2[B];
        int ans = (1LL * (A + 1) * powB - 1 + MOD) % MOD;
        cout << ans << endl;
    }
    
    return 0;
}