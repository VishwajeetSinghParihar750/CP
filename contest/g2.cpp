// Author__ VISHWAJEET_SINGH_PARIHAR __
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

vi entryTime;
vi low;
vi howFar;

set<int> inLoop;

vector<bool> visited;

void dfs(int v, int p, vi &nodes)
{

    visited[v] = true;
    nodes.pb(v);

    entryTime[v] = entryTime[p] + 1;
    low[v] = entryTime[v];

    for (auto i : adj[v])
    {

        if (!visited[i])
            dfs(i, v, nodes);

        low[v] = min(low[v], low[i]);
    }

    if (entryTime[v] < low[adj[v][0]])
    {
        // goes to only one thats why

        howFar[v] = howFar[adj[v][0]] + 1;
    }
    else
    {
        inLoop.insert(v);
    }
}

int countNodes(int v)
{
    int cnt = 1;

    for (auto i : adj[v])
        cnt += countNodes(i);

    return cnt;
}

int dfsUtil(int n)
{

    Fo(i, 1, n + 1)
    {
        vi newAdditions;

        if (!visited[i])
        {
            dfs(i, 0, newAdditions);

            for (auto j : newAdditions)
            {
                low[j] = inf;
                entryTime[j] = inf;
            }
        }
    }

    Fo(i, 1, n + 1)
    {
        if (!inLoop.count(i))
        {
            int temp = adj[i][0];

            auto it = find(adj[i].begin(), adj[i].end(), temp);
            if (it != adj[i].end())
            {
                adj[i].erase(it);
            }

            adj[temp].pb(i);
        }
    }

    int mx = 0;
    for (auto i : inLoop)
    {
        for (auto j : adj[i])
        {
            if (!inLoop.count(j))
            {
                mx = max(mx, countNodes(j));
            }
        }
    }

    return mx;
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);

    adj.assign(n + 1, {});

    entryTime.assign(n + 1, 0);
    low.assign(n + 1, inf);
    howFar.assign(n + 1, 0);
    visited.assign(n + 1, false);
    inLoop.clear();

    fo(i, n)
    {
        cin >> inp;

        adj[i + 1].pb(inp);
    }

    int ans = dfsUtil(n);

    println(ans + 2);
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

    int T;
    in(T);
    while (T--)
    {

        solve();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    // cerr << "entryTime taken : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;

    return 0;
}