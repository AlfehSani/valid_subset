#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 100005;

int mod_pow(int a, long long b) {
    long long res = 1;
    long long base = a;
    while (b) {
        if (b % 2) res = (res * base) % MOD;
        base = (base * base) % MOD;
        b /= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<int> pow2(n + 2, 1);
    for (int i = 1; i <= n + 1; ++i) {
        pow2[i] = (1LL * pow2[i - 1] * 2) % MOD;
    }
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        int cntA = 0;
        for (int i = l; i <= r; ++i) {
            if (a[i] % x == 0) {
                cntA++;
            }
        }
        int cntB = (r - l + 1) - cntA;
        int res = (1LL * (cntA + 1) * pow2[cntB] % MOD - 1 + MOD) % MOD;
        cout << res << '\n';
    }
    return 0;
}