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
const int inf = INT32_MAX;
const int NN = 2e5 + 5;

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________
vi fuelHere;
vector<vpii> adj;
vvi dp;
int ans = 0;

void dfs(int v, int p)
{
    //

    int max1 = 0, max2 = 0;

    for (auto i : adj[v])
    {
        if (i.first == p)
            continue;
        //

        dfs(i.first, v);

        if (dp[i.first][0] - i.second >= max1)
        {
            max2 = max1;
            max1 = dp[i.first][0] - i.second;
        }
        else if (dp[i.first][0] - i.second > max2)
        {
            max2 = dp[i.first][0] - i.second;
        }
    }

    // deb(v), deb(max1), deb(max2);

    dp[v][0] = fuelHere[v] + max1;
    dp[v][1] = fuelHere[v] + max1 + max2;

    //
    // deb(dp[v][0]), deb(dp[v][1]);

    ans = max(ans, dp[v][1]);
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);

    fuelHere.assign(n + 1, 0);
    adj.assign(n + 1, {});
    dp.assign(n + 1, vi(2));

    fo(i, n) cin >> fuelHere[i + 1];
    fo(i, n - 1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].pb({b, c}), adj[b].pb({a, c});
    }

    dfs(1, 0);
    // deb(ans);
    println(ans);

    //
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