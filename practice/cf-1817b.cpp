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
}
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

#ifndef DEBUG_H
#define DEBUG_H

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[ ";
    for (const auto &x : v)
        os << x << " ";
    return os << "]";
}

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &s)
{
    os << "{ ";
    for (const auto &x : s)
        os << x << " ";
    return os << "}";
}

template <typename T, typename U>
ostream &operator<<(ostream &os, const map<T, U> &m)
{
    for (const auto &[key, value] : m)
        os << key << " - " << value << endl;
    return os;
}

void debug_out() { cout << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    cout << H;
    debug_out(T...);
}

#define debug(...) cout << "[ " << #__VA_ARGS__ << " ] :" << endl, debug_out(__VA_ARGS__)

#endif // DEBUG_H

//______________________________________________________________________________

const int MOD = 1000000007;
const int MOD2 = 998244353;
const int inf = INT32_MAX;
const int NN = 2e5 + 5;

// const int HASH_MOD = 1e18 + 1;
// mt19937_64 rng((int)chrono::steady_clock::now().time_since_epoch().count());
// const int HASH_MULT = uniform_int_distribution<int>((int)0, HASH_MOD - 1)(rng);
// tip if needed : use two hashes and pick min to really ensure minimal collisions
// tip : if using unordered containers set container.max_load_factor = 0.2
//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

vector<unordered_set<int>> adj;

int curstarter = 0;
vi working;
vi connected;

int workingstarter = -1;

vector<bool> visited;

void dfs(int v, int p, vi &vec, vi &mine)
{

    if (adj[curstarter].count(v))
        mine.pb(v);

    if (p != -1)
        vec.pb(v);

    visited[v] = true;

    for (auto i : adj[v])
    {

        if (!visited[i])
        {
            dfs(i, v, vec, mine);
        }
        else if (i == curstarter && i != p && workingstarter == -1 && mine.size() <= adj[curstarter].size() - 2)
        {
            working = vec;
            workingstarter = curstarter;
            connected = mine;
        }
    }

    if (adj[curstarter].count(v))
        mine.pop_back();

    if (p != -1)
        vec.pop_back();
}

void solve()
{
    int n, m, k, inp;
    string s;

    //
    cin >> n >> m;
    //

    adj.assign(n, {});
    working.clear();
    connected.clear();
    workingstarter = -1;

    fo(i, m)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v), adj[v].insert(u);
        //
    }

    fo(i, n)
    {
        if (workingstarter == -1)
        {
            curstarter = i;
            visited.assign(n, false);

            vi usevec, mine;
            dfs(i, -1, usevec, mine);
        }
        else
            break;
    }

    if (workingstarter == -1)
        println("NO");
    else
    {

        //
        vpii edges;
        int sz = working.size();

        edges.emplace_back(workingstarter, working[0]);
        edges.emplace_back(workingstarter, working[sz - 1]);
        fo(i, sz - 1)
        {
            edges.emplace_back(working[i], working[i + 1]);
        }

        for (auto i : connected)
            adj[workingstarter].erase(i);

        int itr = 0;
        for (auto i : adj[workingstarter])
        {
            edges.emplace_back(workingstarter, i);

            if (++itr == 2)
                break;
        }

        println("YES");
        println(edges.size());
        for (auto [a, b] : edges)
            print(a + 1), println(b + 1);
    }
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
    cerr << "Time taken : " << ((long double)duration.count()) / ((long double)1e9) << "s " << endl;

    return 0;
}