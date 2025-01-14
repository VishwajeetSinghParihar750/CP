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

vvi adj;
vi order;
vi sz;

void dfs(int v, int p)
{
    order.pb(v);
    sz[v] = 1;
    for (auto i : adj[v])
    {
        if (i == p)
            continue;

        dfs(i, v);

        sz[v] += sz[i];

        //
    }
}

struct segData
{
    // returns sum rn
    int val;
    segData() = default;
    segData(int val_) : val(val_) {}
    segData operator+(const segData &toAdd)
    {
        segData toret;
        toret.val = val + toAdd.val;
        return toret;
    }
};
vector<segData> t; // keep N = n, n is size of array

void build(const vi &a, int v, int tl, int tr)
{ // v = 1, tl = 0, tr = n-1
    if (tl == tr)
    {
        t[v] = a[tl];
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        build(a, 2 * v, tl, mid);
        build(a, 2 * v + 1, mid + 1, tr);

        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

segData findResult(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;

    if ((l == tl) && (r == tr))
        return t[v];

    else
    {
        int mid = tl + (tr - tl) / 2;

        return findResult(2 * v, tl, mid, l, min(mid, r)) +
               findResult(2 * v + 1, mid + 1, tr, max(l, mid + 1), r);
    }
}

void update(int v, int tl, int tr, int pos, int val)
{
    if (tl == tr)
    {
        t[v] = val;
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        if (pos > mid)
        {
            update(2 * v + 1, mid + 1, tr, pos, val);
        }
        else
            update(2 * v, tl, mid, pos, val);

        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);
    int q;

    adj.assign(n + 1, {});
    sz.assign(n + 1, 0);
    cin >> q;

    vi val(n);
    fo(i, n) cin >> val[i];

    fo(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    //

    dfs(0, -1);

    map<int, int> pos;
    fo(i, n) pos[order[i]] = i;

    vi orderedVal(n);
    fo(i, n) orderedVal[i] = val[order[i]];

    t.assign(4 * n + 5, 0);

    build(orderedVal, 1, 0, n - 1); //

    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int p, x;
            cin >> p >> x;
            p--;

            //

            update(1, 0, n - 1, pos[p], x);
        }
        else
        {
            int p;
            cin >> p;
            p--;
            int res = findResult(1, 0, n - 1, pos[p], pos[p] + sz[p] - 1).val;
            println(res);
        }
    }

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