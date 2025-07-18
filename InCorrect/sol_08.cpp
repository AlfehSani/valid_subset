#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAX = 100005;

map<int, vector<int>> divisors_map;
int pow2[MAX];

void precompute_powers() {
    pow2[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pow2[i] = (1LL * pow2[i - 1] * 2) % MOD;
    }
}

vector<int> get_all_divisors(int n) {
    vector<int> divisors;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    return divisors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        vector<int> divisors = get_all_divisors(a[i]);
        for (int d : divisors) {
            divisors_map[d].push_back(i + 1); // 1-based index
        }
    }

    precompute_powers();

    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        int A = 0;
        if (divisors_map.find(x) != divisors_map.end()) {
            const vector<int>& pos_list = divisors_map[x];
            auto left = lower_bound(pos_list.begin(), pos_list.end(), l);
            auto right = upper_bound(pos_list.begin(), pos_list.end(), r);
            A = right - left;
        }
        int total = r - l + 1;
        int B = total - A;
        if (B < 0) B = 0;
        if (B >= MAX) B = MAX - 1;
        long long term1 = (A + 1LL) % MOD;
        long long pow_val = pow2[B];
        long long product = (term1 * pow_val) % MOD;
        long long ans = (product - 1 + MOD) % MOD;
        cout << ans << endl;
    }

    return 0;
}