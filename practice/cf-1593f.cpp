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
// tip : if using unordered containers set container.max_load_factor = 0.2
//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

void solve()
{
    int n, m, k, inp;
    string s;

    int a, b;
    cin >> n >> a >> b;

    cin >> s;
    reverse(all(s));
    //

    int mid = n / 2;
    //
    vi bmodsright(1 << mid, -1);
    vi amodsright(1 << mid, -1);

    amodsright[0] = 0, bmodsright[0] = 0;

    vector<vvi> rightinfo(mid + 1, vvi(a, vi(b, -1)));
    // for each len of a mask =>
    // for each mod of a
    // cnt of each mod of b

    for (int mask = 1; mask < (1 << mid); mask++)
    {
        //
        fo(sh, mid)
        {
            if (mask & (1 << sh))
            {

                int bmodsum = ((s[sh] - '0') + bmodsright[mask ^ (1 << sh)] * 10) % b;

                bmodsright[mask] = bmodsum;
                break;
            }
        }
    }

    for (int mask = 0; mask < (1 << mid); mask++)
    {
        //
        int len = 0;

        if (mask > 0)
        {
            len = __builtin_popcount(mask);

            fo(sh, mid)
            {
                if (mask & (1 << sh))
                {

                    int amodsum = (((s[sh] - '0')) + amodsright[mask ^ (1 << sh)] * 10) % a;

                    amodsright[mask] = amodsum;

                    break;
                }
            }
        }
        int bsmask = ((1 << mid) - 1) ^ mask;

        rightinfo[len][amodsright[mask]][bmodsright[bsmask]] = bsmask;
    }

    //

    // for left side now
    int remlen = n - mid;

    vi amodsleft(1 << remlen), bmodsleft(1 << remlen);

    for (int mask = 1; mask < (1 << remlen); mask++)
    {
        //
        fo(sh, remlen)
        {
            if (mask & (1 << sh))
            {

                int bmodsum = ((s[sh + mid] - '0') + bmodsleft[mask ^ (1 << sh)] * 10) % b;

                bmodsleft[mask] = bmodsum;
                break;
            }
        }
    }

    int ans = inf;
    int bleftchosen = -1, brightchosen = -1;

    for (int mask = 0; mask < (1 << remlen); mask++)
    {
        //
        int len = 0;

        if (mask != 0)
        {
            len = __builtin_popcount(mask);

            fo(sh, remlen)
            {
                if (mask & (1 << sh))
                {

                    int amodsum = (((s[sh + mid] - '0')) + amodsleft[mask ^ (1 << sh)] * 10) % a;

                    amodsleft[mask] = amodsum;

                    break;
                }
            }
        }

        int bsmask = ((1 << remlen) - 1) ^ mask;

        //

        for (int l = 0; l <= mid; l++)
        {
            //

            if (mask == 0 && l == 0)
                continue;

            int aleftmod = (amodsleft[mask] * POWER(10ll, l, a)) % a;
            int bleftmod = (bmodsleft[bsmask] * POWER(10ll, mid - l, b)) % b;

            int amodneeded = (a - aleftmod) % a;

            int bmodneeded = (b - bleftmod) % b;

            if (rightinfo[l][amodneeded][bmodneeded] != -1)
            {
                int newdif = abs((len + l) - ((remlen - len) + (mid - l)));

                if (newdif < ans)
                {
                    bleftchosen = bsmask, brightchosen = rightinfo[l][amodneeded][bmodneeded];

                    ans = newdif;
                }
            }
        }
    }

    string res(n, 'R');
    fo(i, mid)
    {
        if (brightchosen & (1 << i))
        {
            res[i] = 'B';
        }
    }
    fo(i, remlen)
    {
        if (bleftchosen & (1 << i))
        {
            res[i + mid] = 'B';
        }
    }

    reverse(all(res));

    if (ans == inf)
        println(-1);
    else
        println(res);
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