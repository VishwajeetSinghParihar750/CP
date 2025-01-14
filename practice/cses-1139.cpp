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
// #define int ll
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

vvi adj;
vi color;

vi flatTree;
vi sz;

void dfs(int v, int p)
{
    flatTree.pb(v);
    sz[v] = 1;
    for (auto i : adj[v])
    {
        if (i != p)
        {
            //

            dfs(i, v);
            sz[v] += sz[i];
        }
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);

    adj.assign(n + 1, {});
    color.assign(n + 1, 0);
    sz.assign(n + 1, 0);

    fo(i, n) cin >> color[i + 1];
    //
    fo(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }

    dfs(1, 0);

    //

    vpii ranges;
    fo(i, n)
    {
        int start = i, end = i + sz[flatTree[i]] - 1;

        ranges.pb({start, end});
    }

    sort(ranges.begin(), ranges.end(), [](pii a, pii b)
         {
        if (a.first == b.first) return a.second > b.second;
        return a.first > b.first; });

    //
    ordered_set<int> uniq; // this keeps indexes
    map<int, int> lastIndex;

    //

    vi orderedColor(n);
    fo(i, n) orderedColor[i] = color[flatTree[i]];

    int curPos = n - 1;

    vi ans(n + 1);
    fo(i, n)
    {

        int a = ranges[i].first, b = ranges[i].second;
        //

        while (curPos >= a)
        {

            if (lastIndex.count(orderedColor[curPos]))
            {
                uniq.erase(lastIndex[orderedColor[curPos]]);
            }

            lastIndex[orderedColor[curPos]] = curPos;
            uniq.insert(curPos);

            curPos--;
        }

        //
        ans[flatTree[a]] = uniq.order_of_key(b + 1);

        //
    }

    Fo(i, 1, n + 1) print(ans[i]);
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