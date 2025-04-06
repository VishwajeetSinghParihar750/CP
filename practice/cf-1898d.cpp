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
const int inf = INT32_MAX;
const int NN = 2e5 + 5;

// const int HASH_MOD = 1e18 + 1;
// mt19937_64 rng((int)chrono::steady_clock::now().time_since_epoch().count());
// const int HASH_MULT = uniform_int_distribution<int>((int)0, HASH_MOD - 1)(rng);
// tip if needed : use two hashes and pick min to really ensure minimal collisions

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

// vector<int> tkeepsb, tkeepsa; // keep N = n, n is size of array

// void build(const vi &a, int v, int tl, int tr, bool who)
// { // v = 1, tl = 0, tr = n-1
//     if (tl == tr)
//     {
//         if (who)
//             tkeepsa[v] = a[tl];
//         else
//             tkeepsb[v] = a[tl];
//     }
//     else
//     {
//         int mid = tl + (tr - tl) / 2;

//         build(a, 2 * v, tl, mid, who);
//         build(a, 2 * v + 1, mid + 1, tr, who);

//         if (who)
//             tkeepsa[v] = max(tkeepsa[2 * v], tkeepsa[2 * v + 1]);
//         else
//             tkeepsb[v] = max(tkeepsb[2 * v], tkeepsb[2 * v + 1]);
//     }
// }

// int findResult(int v, int tl, int tr, int l, int r, bool who)
// {
//     if (l > r)
//         return 0;

//     if ((l == tl) && (r == tr))
//     {
//         if (who)
//             return tkeepsa[v];
//         else
//             return tkeepsb[v];
//     }
//     else
//     {

//         int mid = tl + (tr - tl) / 2;

//         return max(findResult(2 * v, tl, mid, l, min(mid, r), who),
//                    findResult(2 * v + 1, mid + 1, tr, max(l, mid + 1), r, who));
//     }
// }

void solve()
{
    int n, m, k, inp;
    string s;

    cin >> n;
    vpii vec(n);
    fo(i, n) cin >> vec[i].first;
    fo(i, n) cin >> vec[i].second;
    //

    // vpii biggera, biggerb;
    // fo(i, n)
    // {
    //     if (vec[i].first > vec[i].second)
    //         biggera.pb(vec[i]);
    //     else
    //         biggerb.pb(vec[i]);
    // }

    // vi sorteda, bforsorteda;
    // vi sortedb, aforsortedb;

    // sort(biggerb.begin(), biggerb.end(), [](pii a, pii b)
    //      { return a.first < b.first; }); // a1 -- b1 -- a2 -- b2

    // deb("1");

    // fo(i, biggerb.size())
    // {
    //     sorteda.pb(biggerb[i].first);
    //     bforsorteda.pb(biggerb[i].second); //
    // }

    // //

    // deb(biggera.size());
    // sort(biggera.begin(), biggera.end(), [](pii a, pii b)
    //      { return a.second < b.second; }); // b1 -- a1 -- b2 -- a2

    // //
    // fo(i, biggera.size())
    // {
    //     sortedb.pb(biggera[i].second);
    //     aforsortedb.pb(biggera[i].first); //
    // }

    //

    // int szforkeepingbs = bforsorteda.size(), szforkeepingas = aforsortedb.size();

    // tkeepsa.assign(4 * szforkeepingas + 1, {});
    // tkeepsb.assign(4 * szforkeepingbs + 1, {});

    // deb(szforkeepingas);
    // deb(szforkeepingbs);

    // if (szforkeepingbs > 0)
    //     build(bforsorteda, 1, 0, szforkeepingbs - 1, 0); // // a1 -- b1 -- a2 -- b2
    // if (szforkeepingas > 0)
    //     build(aforsortedb, 1, 0, szforkeepingas - 1, 1); // // b1 -- a1 -- b2 -- a2

    //

    int ans = LLONG_MIN;

    int minbforbigb = 1e16, maxbforbiga = -1e16;
    int minaforbiga = 1e16, maxaforbigb = -1e16;

    fo(i, n)
    {
        //
        if (vec[i].first > vec[i].second)
        {
            maxbforbiga = max(maxbforbiga, vec[i].second);
            minaforbiga = min(minaforbiga, vec[i].first);

            // b1 --- a1 --- b2 --- a2
            //

            // auto it = lower_bound(sortedb.begin(), sortedb.end(), vec[i].first);

            // if (it != sortedb.end())
            // {
            //     int pos = it - sortedb.begin();

            //     int findmxa = findResult(1, 0, szforkeepingas - 1, pos, szforkeepingas - 1, 1);

            //     ans = max(ans, 2 * (findmxa - vec[i].second));
            // }
        }
        else
        {
            maxaforbigb = max(maxaforbigb, vec[i].first);
            minbforbigb = min(minbforbigb, vec[i].second);
            // a1 -- b1 -- a2 -- b2

            //
            // auto it = lower_bound(sorteda.begin(), sorteda.end(), vec[i].second);
            // if (it != sorteda.end())
            // {
            //     int pos = it - sorteda.begin();
            //     int findmxb = findResult(1, 0, n - 1, pos, szforkeepingbs - 1, 0);

            //     ans = max(ans, 2 * (findmxb - vec[i].first));
            // }
        }
    }

    // deb(ans);

    // deb(maxaforbigb), deb(minaforbiga);

    ans = max(ans, max(0ll, 2ll * (maxaforbigb - minaforbiga)));

    // deb(ans);
    ans = max(ans, max(0ll, 2ll * (maxbforbiga - minbforbigb)));

    // deb(ans);

    ans = max(ans, max(0ll, 2ll * (maxbforbiga - minaforbiga)));

    ans = max(ans, max(0ll, 2ll * (maxaforbigb - minbforbigb)));

    fo(i, n)
    {
        ans += abs(vec[i].first - vec[i].second);
        // deb(vec[i].first), deb(vec[i].second);
        // deb(i), deb(ans);
    }

    println(ans);
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