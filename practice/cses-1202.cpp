// Author__ VISHWAJEET_SINGH_PARIHAR __
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long
#define int ll
typedef int node; // make node whatever you want in o_set
#define gc getchar_unlocked
#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define deb(x) cout << #x << " = " << x << endl
#define println(n) cout << n << endl
#define print(n) cout << n << " "
#define in(n) cin >> n
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
template <typename T>
T pqInverseMod(T p, T q, T mod)
{
    long long expo;
    expo = mod - 2;
    while (expo)
    {
        if (expo & 1)
        {
            p = (p * q) % mod;
        }
        q = (q * q) % mod;
        expo >>= 1;
    }
    return p;
};
template <typename T>
T POWER(T a, T b, T mod)
{
    ll res = 1;
    while (b != 0)
    {
        if ((b & 1) == 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}
template <typename T>
T gcd(T a, T b)
{
    if (b == 0)
        return a;
    return (gcd(b, a % b));
}

//______________________________________________________________________________

const int MOD1 = 1000000007;
const int MOD2 = 998244353;
const int inf = 1e18;
const int NN = 2e5 + 5;

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

void solve()
{
    int n, m, k, inp;
    in(n);
    cin >> m;

    vector<vpii> adj(n + 1);

    vector<vpii> intome(n + 1);
    fo(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].emplace_back(b, c);

        intome[b].emplace_back(a, c);
    }

    vi dist(n + 1, inf);
    dist[1] = 0;

    set<pii> s;
    set<int> inset;

    s.emplace(0, 1);
    inset.insert(1);

    while (s.size())
    {
        pii t = *s.begin();
        s.erase(s.begin());
        inset.erase(t.second);

        for (auto p : adj[t.second])
        {
            int newdis = t.first + p.second;

            if (newdis < dist[p.first])
            {
                if (inset.count(p.first))
                {
                    s.erase({dist[p.first], p.first});
                }

                inset.insert(p.first);
                dist[p.first] = newdis;
                s.emplace(dist[p.first], p.first);
            }
        }
    } // finding the minimum distance

    //
    println(dist[n]);

    vi toposort;
    vector<bool> visited(n + 1, false);

    function<void(int)> gettopo = [&](int v) -> void
    {
        visited[v] = true;
        for (auto i : adj[v])
            if (!visited[i.first])
                gettopo(i.first);

        toposort.pb(v);
    }; // finding the topo sort

    gettopo(1);

    reverse(all(toposort));

    // vi ind(n + 1);
    // fo(i, n) ind[toposort[i]] = i;

    vvi dp(n + 1, vi(3));

    fo(i, n + 1)
        dp[i][1] = inf;

    dp[1][0] = 1;
    dp[1][1] = dp[1][2] = 1;

    for (auto i : toposort)
    {

        for (auto v : intome[i])
        {
            //

            if (dist[v.first] + v.second == dist[i])
            {
                // deb(i);
                (dp[i][0] += dp[v.first][0]) %= MOD1;

                dp[i][1] = min(dp[i][1], 1 + dp[v.first][1]);

                dp[i][2] = max(dp[i][2], 1 + dp[v.first][2]);
            }
        }
    }
    println(dp[n][0]);
    println(dp[n][1] - 1);
    println(dp[n][2] - 1);
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cerr << fixed << setprecision(10);
    auto start = std::chrono::high_resolution_clock::now();

    int T = 1;
    // in(T);
    fo(i, T)
    {

        // cout << "__________________________ TEST CASE " << i << "________________________" << endl;
        solve();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    // cerr << "Time taken : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;

    return 0;
}