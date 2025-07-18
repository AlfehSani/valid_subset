#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, mod = 998244353; 
int spf[N];

void sieve()
{
    for (int i = 2; i < N; i++)
    {
        if (spf[i] == 0)
        {
            for (int j = i; j < N; j += i)
            {
                if (spf[j] == 0)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

vector<int> get_divisors(int x)
{
    vector<int> divisors;
    vector<pair<int, int>> prime_factors;
    while (x > 1)
    {
        int prime_factor = spf[x];
        int count = 0;
        while (x % prime_factor == 0)
        {
            x /= prime_factor;
            count++;    
        }
        prime_factors.push_back({prime_factor, count});
    }
    divisors.push_back(1); // 1 is a divisor of every number
    for(auto &[p, c] : prime_factors)
    {
        vector<int> current_divisors = divisors;
        for(int d:divisors)
        {
            int cur_num = d;
            for(int i = 1; i <= c; i++)
            {
                cur_num *= p;
                current_divisors.push_back(cur_num);
            }
        }
        divisors = current_divisors;
    }

    return divisors;
}

vector<int>multiple_of[N];
int power2[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    sieve(); // Precompute smallest prime factors

    
    int n;
    cin >> n;
    vector<int> a(n);
    power2[0] = 1;
    // cout << "helli" << endl;
    for (int i = 1; i <= n; i++)
    {
        power2[i] = (1LL * power2[i - 1] * 2) % mod;
    }
    // cout << "helli" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        assert(a[i] >= 1 && a[i] < N);
        auto divisors = get_divisors(a[i]);
        for (int d : divisors)
        {
            multiple_of[d].push_back(i + 1); // Store 1-based index
        }
    }
    int q; cin >> q;
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        auto itr = upper_bound(multiple_of[x].begin(), multiple_of[x].end(), r);
        auto itr1 = lower_bound(multiple_of[x].begin(), multiple_of[x].end(), l);
        int count_multiple = itr - itr1;
        int others = r - l + 1 - count_multiple;
        long long power_two = power2[others];
        long long ans = power_two * (count_multiple + 1);
        ans %= mod;
        ans += mod - 1; // To handle the case subset is empty
        ans %= mod;
        cout << ans << '\n';
    }


    return 0;


}