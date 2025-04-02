#include <bits/stdc++.h>
#include <ext/random>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int)(v).size()

typedef long long ll;
typedef pair<int, int> pii;

__gnu_cxx::sfmt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &a)
{
    for (const T &x : a)
    {
        os << x << ' ';
    }
    return os;
}

const ll INF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        ll x;
        cin >> n >> k >> x;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            a[i] -= x;
        }
        x *= 2;
        vector<ll> pref(n + 1), mn(n + 1), mn2(n + 1, INF);
        ll ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            pref[i] = pref[i - 1] + a[i];
            mn[i] = min(pref[i], mn[i - 1]);
            if (i >= k)
            {
                mn2[i] = min(mn2[i - 1], pref[i]);
            }
            for (int j = i - 1; j >= 0 && i - j <= k; --j)
            {
                ans = max(ans, pref[i] - pref[j] + (i - j) * x);
            }
            for (int j = 0; j <= k && j < i; ++j)
            {
                int must = max(0, k + (i - j) - n);
                ans = max(ans, pref[i] - pref[j] + must * x);
            }
            if (i >= k)
            {
                ans = max(ans, pref[i] - mn[i - k] + k * x);
                ans = max(ans, pref[i] - mn2[i]);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
