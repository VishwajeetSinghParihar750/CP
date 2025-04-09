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
const int inf = 1e16;
const int NN = 2e5 + 5;

// const int HASH_MOD = 1e18 + 1;
// mt19937_64 rng((int)chrono::steady_clock::now().time_since_epoch().count());
// const int HASH_MULT = uniform_int_distribution<int>((int)0, HASH_MOD - 1)(rng);
// tip if needed : use two hashes and pick min to really ensure minimal collisions

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

vvi adj;
struct info
{
    int sum = 0;
    int mx = 0; // mx prefix
    int mn = 0; // mn prefix

    int mxr = 0;
    int mnr = 0;

    int par = -1;

    info() = default;
    info(int val, int par) : sum(val), mx(max(val, 0ll)), mn(min(val, 0ll)),
                             mxr(max(0ll, val)), mnr(min(0ll, val)), par(par) {}

    info operator+(info &bigger)
    {
        info toret;
        toret.par = bigger.par;

        toret.sum = sum + bigger.sum;

        toret.mxr = max(mxr, bigger.mxr);
        toret.mxr = max(toret.mxr, bigger.mx + (sum - mn));

        toret.mnr = min(mnr, bigger.mnr);
        toret.mnr = min(toret.mnr, bigger.mn + (sum - mx));

        toret.mn = min(mn, bigger.mn + sum);
        toret.mx = max(mx, bigger.mx + sum);

        return toret;
    }

    void printall()
    {
        deb(sum), deb(mx), deb(mn), deb(mxr), deb(mnr), deb(par);
        println("_______________________");
    }
};

void solve()
{
    int n, m, k, inp;
    string s;

    int qr;
    cin >> qr;

    vvi q;
    vpii edges;

    vi nodeval;
    nodeval.pb(1); // for 0

    int v = 1;
    fo(i, qr)
    {
        //
        char c;
        cin >> c;
        if (c == '+')
        {
            //
            int u, x;

            cin >> u >> x;
            u--;

            edges.pb({u, v});
            v++;

            nodeval.pb(x);
        }
        else
        {

            //
            int a, b, k;
            cin >> a >> b >> k;
            a--, b--;

            q.pb({a, b, k});
        }
    }

    //

    n = edges.size() + 1;

    adj.assign(n, {});
    for (auto [a, b] : edges)
    {
        adj[a].pb(b);
        adj[b].pb(a);
    }

    //

    //
    vector<vector<info>> dp;
    dp.assign(n, vector<info>(20));

    //
    dp[0][0] = {1, -1};

    //
    vi tin(n), tout(n);
    int timer = 0;

    auto dfs = [&](auto self, int v, int p) -> void
    {
        tin[v] = timer++;
        for (auto i : adj[v])
        {
            if (i != p)
            {
                dp[i][0] = {nodeval[i], v}; // self

                self(self, i, v); // self have been made
            }
        }
        tout[v] = timer++;
    };

    dfs(dfs, 0, -1); // fill stuff

    //

    //

    auto isAncestor = [&](int u, int p) -> bool
    {
        return (u != -1) && (p == -1 || (tin[u] >= tin[p] && tout[u] <= tout[p]));
    }; //

    //

    //
    for (int p = 1; p < 20; p++)
    {
        fo(i, n)
        {
            int par = dp[i][p - 1].par;

            if (par != -1)
            {
                dp[i][p] = dp[i][p - 1] + dp[par][p - 1];
            }
        }
    }

    //

    //

    vi ans(q.size());

    fo(it, q.size())
    {
        int u = q[it][0], v = q[it][1], k = q[it][2];
        //
        if (u == v)
        {
            if (nodeval[u] == k || k == 0)
                println("YES");
            else
                println("NO");
            continue;
        }

        //
        info uans;

        for (int i = 19; i >= 0; i--)
        {
            if (!isAncestor(v, dp[u][i].par))
            {
                if (uans.par == -1)
                    uans = dp[u][i];
                else
                    uans = uans + dp[u][i];
                u = dp[u][i].par;
            }
        }

        info vans;
        for (int i = 19; i >= 0; i--)
        {
            if (!isAncestor(u, dp[v][i].par))
            {
                if (vans.par == -1)
                    vans = dp[v][i];
                else
                    vans = vans + dp[v][i];

                v = dp[v][i].par;
            }
        }

        if ((uans.mnr <= k && uans.mxr >= k) || (vans.mnr <= k && vans.mxr >= k))
        {
            println("YES");
            continue;
        }

        info newans;
        if (isAncestor(u, v))
        {
            // if (uans.par == -1)
            //     newans = dp[u][1];
            // else
            newans = uans + dp[u][1];
        }
        else if (isAncestor(v, u))
        {
            // if (vans.par == -1)
            //     newans = dp[v][1];
            // else
            newans = vans + dp[v][1];
        }
        else
        {
            // if (vans.par == -1)
            //     vans = dp[v][1];
            // else
            vans = vans + dp[v][1];

            // if (uans.par == -1)
            //     uans = dp[u][1];
            // else
            uans = uans + dp[u][1];

            //
            newans.mxr = max(vans.mxr, uans.mxr);

            int a1 = vans.sum - vans.mn;
            int a2 = uans.sum - uans.mn;
            if (a1 != 0 && a2 != 0)
                newans.mxr = max(newans.mxr, (vans.sum - vans.mn) + (uans.sum - uans.mn) - nodeval[dp[u][0].par]);

            //
            newans.mnr = min(vans.mnr, uans.mnr);

            a1 = vans.sum - vans.mx;
            a2 = uans.sum - uans.mx;

            if (a1 != 0 && a2 != 0)
                newans.mnr = min(newans.mnr, (vans.sum - vans.mx) + (uans.sum - uans.mx) - nodeval[dp[u][0].par]);
        }

        //
        if ((newans.mnr <= k && newans.mxr >= k))
        {
            println("YES");
        }
        else
            println("NO");
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
    // cerr << "Time taken : " << ((long double)duration.count())/((long double) 1e9) <<"s " << endl;

    return 0;
}