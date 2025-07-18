#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 1e5 + 5;

map<int, vector<int>> posMap;

int pow2[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        // For each element, store its position in the map
        int val = a[i];
        if (val == 0) continue; // Handle zero if needed
        if (posMap.find(val) == posMap.end()) {
            posMap[val].reserve(n);
        }
        posMap[val].push_back(i + 1); // 1-based index
    }
    
    // Precompute powers of 2 modulo MOD
    pow2[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pow2[i] = (pow2[i-1] * 2LL) % MOD;
    }
    
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        
        // Count the number of elements in [l, r] divisible by x
        int k = 0;
        if (posMap.find(x) != posMap.end()) {
            const vector<int>& pos = posMap[x];
            int left = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            int right = upper_bound(pos.begin(), pos.end(), r) - pos.begin();
            k = right - left;
        }
        
        int total = r - l + 1;
        int m = total - k;
        
        // Compute (k + 1) * pow(2, m) - 1
        long long part1 = (k + 1LL) * pow2[m] % MOD;
        long long ans = (part1 - 1 + MOD) % MOD;
        cout << ans << '\n';
    }
    
    return 0;
}