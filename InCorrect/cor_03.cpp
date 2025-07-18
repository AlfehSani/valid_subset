#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 1e5 + 5;

vector<int> divisors[MAXN];
int power[MAXN];

// Function to get all divisors of n
void getDivisors(int n, vector<int>& res) {
    res.clear();
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) {
                res.push_back(n / i);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // Precompute powers of 2 modulo MOD
    power[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        power[i] = (1LL * power[i - 1] * 2) % MOD;
    }
    
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        vector<int> divs;
        getDivisors(a[i], divs);
        for (int d : divs) {
            if (d >= MAXN) continue;
            divisors[d].push_back(i);
        }
    }
    
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        
        // Count elements divisible by x in [l, r]
        int count_A = 0;
        if (x < MAXN && !divisors[x].empty()) {
            auto& vec = divisors[x];
            auto left = lower_bound(vec.begin(), vec.end(), l);
            auto right = upper_bound(vec.begin(), vec.end(), r);
            count_A = right - left;
        }
        
        int total = r - l + 1;
        int count_B = total - count_A;
        
        long long part1 = (count_A + 1LL) * power[count_B] % MOD;
        long long ans = (part1 - 1 + MOD) % MOD;
        cout << ans << endl;
    }
    
    return 0;
}