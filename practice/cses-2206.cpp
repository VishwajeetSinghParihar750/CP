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
vpii t; // min and max
// min of piz - a, and min of a  - piz

void build(const vi &a, int v, int tl, int tr)
{ // v = 1, tl = 0, tr = n-1
    if (tl == tr)
    {
        t[v] = {a[tl] - tl, tl + a[tl]};
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        build(a, 2 * v, tl, mid);
        build(a, 2 * v + 1, mid + 1, tr);

        t[v].first = min(t[2 * v].first, t[2 * v + 1].first);
        t[v].second = min(t[2 * v].second, t[2 * v + 1].second);
    }
}

int findMin(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 1e16;

    if ((l == tl) && (r == tr))
        return t[v].first;

    else
    {
        int mid = tl + (tr - tl) / 2;

        return min(findMin(2 * v, tl, mid, l, min(mid, r)),
                   findMin(2 * v + 1, mid + 1, tr, max(l, mid + 1), r));
    }
}

int findMin2(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 1e16;

    if ((l == tl) && (r == tr))
        return t[v].second;

    else
    {
        int mid = tl + (tr - tl) / 2;

        return min(findMin2(2 * v, tl, mid, l, min(mid, r)),
                   findMin2(2 * v + 1, mid + 1, tr, max(l, mid + 1), r));
    }
}

void update(int v, int tl, int tr, int pos, int val)
{
    if (tl == tr)
    {
        t[v] = {val - tl, val + tl};
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

        t[v].first = min(t[2 * v].first, t[2 * v + 1].first);
        t[v].second = min(t[2 * v].second, t[2 * v + 1].second);
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);
    int q;
    cin >> q;

    //
    vi vec(n);
    fo(i, n) cin >> vec[i];

    t.assign(4 * n, {});

    build(vec, 1, 0, n - 1);

    //

    while (q--)
    {

        int o;
        cin >> o;
        if (o == 1)
        {
            int pos, x;
            cin >> pos >> x;

            pos--;
            update(1, 0, n - 1, pos, x);
        }
        else
        {
            int pos;
            cin >> pos;
            pos--;

            int mn2 = findMin2(1, 0, n - 1, pos + 1, n - 1);
            int mn = findMin(1, 0, n - 1, 0, pos);

            println(min(mn2 - pos, pos + mn));
        }
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

    solve();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    // cerr << "Time taken : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;

    return 0;
}