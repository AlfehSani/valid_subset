#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, mod = 998244353;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int q; cin >> q;
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        r--;
        int count_multiple = 0;
        for (int i = l; i <= r; i++)
        {
            if (a[i] % x == 0)
            {
                count_multiple++;
            }
        }
        int others = r - l + 1 - count_multiple;
        long long power_two = 1;
        while (others > 0)
        {
            power_two *= 2;
            power_two %= mod;
            others--;
        }
        long long ans = power_two * count_multiple;
        ans %= mod;
        ans += mod - 1; // To handle the case subset is empty
        ans %= mod;
        cout << ans << '\n';
    }

    return 0;


}


