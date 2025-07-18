#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 1e5 + 5;

vector<long long> power2;
map<int, vector<int>> div_map;

vector<int> get_divisors(int n) {
    vector<int> res;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n + 1); // 1-based index
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        vector<int> divisors = get_divisors(a[i]);
        for (int d : divisors) {
            if (!div_map.count(d)) {
                div_map[d] = vector<int>();
            }
            div_map[d].push_back(i);
        }
    }

    // Precompute power2 up to 1e5 + 5
    power2.resize(1e5 + 5);
    power2[0] = 1;
    for (int i = 1; i < 1e5 + 5; ++i) {
        power2[i] = (power2[i-1] * 2) % MOD;
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        int C = 0;
        if (div_map.count(x)) {
            const vector<int>& lst = div_map[x];
            auto left = lower_bound(lst.begin(), lst.end(), l);
            auto right = upper_bound(lst.begin(), lst.end(), r);
            C = right - left;
        } else {
            C = 0;
        }

        int total_elem = r - l + 1;
        int K = total_elem - C;

        long long part1 = (power2[K] - 1 + MOD) % MOD;
        long long part2 = (C * (long long)power2[K]) % MOD;
        long long ans = (part1 + part2) % MOD;

        cout << ans << endl;
    }

    return 0;
}