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
map<int, map<int, int>> adj;

vector<bool> visited;

set<pii> loop;
vi parent;

//
vi entry, leave;
int timer = 0;

void dfs(int v)
{
    visited[v] = true;
    entry[v] = ++timer;

    for (auto [child, wt] : adj[v])
    {
        if (!visited[child])
        {
            parent[child] = v;

            dfs(child);
        }
        else if (!loop.count({child, v}) and child != parent[v])
        {
            loop.insert({v, child});
        }
    }

    leave[v] = ++timer;
}

bool isAncestor(int u, int anc)
{
    return (entry[u] > entry[anc] and leave[anc] > leave[u]);
}

void solve()
{
    int n, m, k, inp;

    string s;

    cin >> n >> m;

    adj.clear();
    loop.clear();
    visited.assign(n, false);

    parent.assign(n, -1);

    entry.assign(n, 0);
    leave.assign(n, 0);
    timer = 0;

    fo(i, m)
    {
        int u, v, w;
        cin >> u >> v >> w;

        u--, v--;

        adj[u][v] = w;
        adj[v][u] = w;
    }

    //
    fo(i, n) if (!visited[i]) dfs(i);

    // ancestor precomputation

    int till = log2(n) + 5;
    vvi parentup(n, vi(till, -1)), mini(n, vi(till, inf));

    for (int anc = 0; anc < till; anc++)
    {
        fo(i, n)
        {
            if (anc == 0)
            {
                if (parent[i] != -1)
                    parentup[i][0] = parent[i], mini[i][0] = adj[i][parent[i]];
            }
            else
            {
                if (parentup[i][anc - 1] != -1 and parentup[parentup[i][anc - 1]][anc - 1] != -1)
                {
                    parentup[i][anc] = parentup[parentup[i][anc - 1]][anc - 1];
                    mini[i][anc] = min(mini[i][anc - 1], mini[parentup[i][anc - 1]][anc - 1]);
                }
            }
        }
    }

    // find min
    int totalminedgeans = inf;
    pii minloop;

    for (auto couple : loop)
    {
        int to = couple.second, from = couple.first;
        int minedge = adj[to][from];

        for (int i = till - 1; i >= 0; i--)
        {
            if (parentup[from][i] != -1 and isAncestor(parentup[from][i], to))
            {

                minedge = min(minedge, mini[from][i]);
                from = parentup[from][i];
            }
        }
        // coz dint get to to
        minedge = min(minedge, adj[from][to]);

        if (totalminedgeans > minedge)
        {
            minloop = couple;
            totalminedgeans = minedge;
        }
    }

    // trace min loop
    vi ans;
    for (int i = minloop.first; i != minloop.second; i = parent[i])
    {
        ans.pb(i);
    }
    ans.pb(minloop.second);

    print(totalminedgeans);
    println(ans.size());
    for (auto i : ans)
        print(i + 1);
    println("");
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
    in(T);
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