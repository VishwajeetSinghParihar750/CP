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
vi tPre; // keep N = n, n is size of array
vi lazyPre;

void buildPre(const vi &a, int v, int tl, int tr)
{ // v = 1, tl = 0, tr = n-1
    if (tl == tr)
    {
        tPre[v] = a[tl];
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        buildPre(a, 2 * v, tl, mid);
        buildPre(a, 2 * v + 1, mid + 1, tr);

        tPre[v] = max(tPre[2 * v], tPre[2 * v + 1]);
    }
}

void pushPre(int v)
{
    lazyPre[2 * v] += lazyPre[v];
    lazyPre[2 * v + 1] += lazyPre[v];

    tPre[2 * v] += lazyPre[v];
    tPre[2 * v + 1] += lazyPre[v];

    lazyPre[v] = 0;
}

int maxPresum(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return -1e16;

    if ((l == tl) && (r == tr))
    {
        return tPre[v];
    }

    else
    {
        pushPre(v);

        int mid = tl + (tr - tl) / 2;

        return max(maxPresum(2 * v, tl, mid, l, min(mid, r)),
                   maxPresum(2 * v + 1, mid + 1, tr, max(l, mid + 1), r));
    }
}

void updatePre(int v, int tl, int tr, int l, int r, int val)
{
    if (l > r)
        return;

    if ((tl == l) and (tr == tr))
    {
        tPre[v] += val;
        lazyPre[v] += val;
    }
    else
    {
        pushPre(v);

        int mid = tl + (tr - tl) / 2;

        updatePre(2 * v + 1, mid + 1, tr, max(l, mid + 1), r, val);
        updatePre(2 * v, tl, mid, l, min(r, mid), val);

        tPre[v] = max(tPre[2 * v], tPre[2 * v + 1]);
    }
}

vi tSuf; // keep N = n, n is size of array
vi lazySuf;

void buildSuf(const vi &a, int v, int tl, int tr)
{ // v = 1, tl = 0, tr = n-1
    if (tl == tr)
    {
        tSuf[v] = a[tl];
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        buildSuf(a, 2 * v, tl, mid);
        buildSuf(a, 2 * v + 1, mid + 1, tr);

        tSuf[v] = max(tSuf[2 * v], tSuf[2 * v + 1]);
    }
}

void pushSuf(int v)
{
    lazySuf[2 * v] += lazySuf[v];
    lazySuf[2 * v + 1] += lazySuf[v];

    tSuf[2 * v] += lazySuf[v];
    tSuf[2 * v + 1] += lazySuf[v];

    lazySuf[v] = 0;
}

int maxSufsum(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return -1e16;

    if ((l == tl) && (r == tr))
    {
        return tSuf[v];
    }

    else
    {
        pushSuf(v);

        int mid = tl + (tr - tl) / 2;

        return max(maxSufsum(2 * v, tl, mid, l, min(mid, r)),
                   maxSufsum(2 * v + 1, mid + 1, tr, max(l, mid + 1), r));
    }
}

void updateSuf(int v, int tl, int tr, int l, int r, int val)
{
    if (l > r)
        return;

    if ((tl == l) and (tr == tr))
    {
        deb(val);
        tSuf[v] += val;
        lazySuf[v] += val;
    }
    else
    {
        pushSuf(v);

        int mid = tl + (tr - tl) / 2;

        updateSuf(2 * v + 1, mid + 1, tr, max(l, mid + 1), r, val);
        updateSuf(2 * v, tl, mid, l, min(r, mid), val);

        tSuf[v] = max(tSuf[2 * v], tSuf[2 * v + 1]);
    }
}

vi t; // keep N = n, n is size of array

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

        int midMax = tSuf[2 * v] + tPre[2 * v + 1];

        t[v] = max(t[2 * v], t[2 * v + 1]);
        t[v] = max(t[v], midMax);
    }
}

int findAns(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return -1e16;

    if ((l == tl) && (r == tr))
    {
        //     deb(v);
        //     deb(t[v]);
        return t[v];
    }

    else
    {
        int mid = tl + (tr - tl) / 2;

        int midMax = maxSufsum(2 * v, tl, mid, l, min(mid, r)) +
                     maxPresum(2 * v + 1, mid + 1, tr, max(l, mid + 1), r);

        int ans = max(findAns(2 * v, tl, mid, l, min(mid, r)),
                      findAns(2 * v + 1, mid + 1, tr, max(l, mid + 1), r));

        // deb(midMax);
        // deb(ans);

        return max(ans, midMax);
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

        int ans = max(t[2 * v], t[2 * v + 1]);

        deb(v);
        deb(tSuf[2 * v]), deb(tPre[2 * v + 1]);
        int midMax = tSuf[2 * v] + tPre[2 * v + 1];
        deb(ans), deb(midMax);

        t[v] = max(ans, midMax);
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);
    //
    cin >> m;
    vi vec(n), pre(n);
    fo(i, n)
    {
        cin >> vec[i];
        pre[i] = (i > 0 ? pre[i - 1] : 0) + vec[i];
    }
    vi suf(n);
    Fo(i, n - 1, -1) suf[i] = (i < n - 1 ? suf[i + 1] : 0) + vec[i];

    t.assign(4 * n, 0);
    tPre.assign(4 * n, 0);
    tSuf.assign(4 * n, 0);

    lazyPre.assign(4 * n, 0);
    lazySuf.assign(4 * n, 0);

    buildPre(pre, 1, 0, n - 1);
    buildSuf(suf, 1, 0, n - 1);
    build(vec, 1, 0, n - 1);
    // fo(i, 4 * n) print(t[i]);

    while (m--)
    {
        //
        int pos, x;
        cin >> pos >> x;
        pos--;

        int iniVal = vec[pos];
        int dif = x - iniVal;

        vec[pos] = x;

        deb(pos);

        updatePre(1, 0, n - 1, pos, n - 1, dif);
        updateSuf(1, 0, n - 1, 0, pos, dif);
        update(1, 0, n - 1, pos, x);

        int ans = findAns(1, 0, n - 1, 0, n - 1);
        println(ans);
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