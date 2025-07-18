#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAX_A = 1e5 + 5;

vector<int> divisors_list[MAX_A];
int pow2[100005];

// Function to compute all divisors of a number
vector<int> get_divisors(int n) {
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
    }

    // Precompute divisors for each element and build the list
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        vector<int> divisors = get_divisors(val);
        for (int d : divisors) {
            divisors_list[d].push_back(i + 1); // 1-based index
        }
    }

    // Precompute powers of 2 modulo MOD
    pow2[0] = 1;
    for (int i = 1; i <= 100000; ++i) {
        pow2[i] = (1LL * pow2[i - 1] * 2) % MOD;
    }

    int q;
    cin >> q;

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        // Handle x = 0 (though x >= 1 in constraints)
        if (x == 0) {
            cout << 0 << '\n';
            continue;
        }

        // Binary search to count elements in [l, r] divisible by x
        int s0 = 0;
        if (x < MAX_A && !divisors_list[x].empty()) {
            auto &lst = divisors_list[x];
            int left = lower_bound(lst.begin(), lst.end(), l) - lst.begin();
            int right = upper_bound(lst.begin(), lst.end(), r) - lst.begin();
            s0 = right - left;
        }

        int m = (r - l + 1) - s0;
        if (m < 0) m = 0;

        long long res = (1LL * (s0 + 1) * pow2[m]) % MOD;
        res = (res - 1 + MOD) % MOD;
        cout << res << '\n';
    }

    return 0;
}