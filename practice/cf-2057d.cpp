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

struct segData
{
    //
    int min1, min2, max1, max2, ans;

    segData() = default;

    segData(int added, int subtracted)
        : min1(added), min2(subtracted), max1(added), max2(subtracted), ans(0) {}

    segData operator+(const segData &toAdd)
    {
        segData toret;
        toret.max1 = max(toAdd.max1, max1);
        toret.max2 = max(toAdd.max2, max2);

        toret.min1 = min(min1, toAdd.min1);
        toret.min2 = min(min2, toAdd.min2);

        toret.ans = max(ans, toAdd.ans);

        toret.ans = max(toret.ans, toAdd.max2 - min2);
        toret.ans = max(toret.ans, max1 - toAdd.min1);

        return toret;
    }
};

vector<segData> t; // keep N = n, n is size of array

void build(const vi &a, const vi &s, int v, int tl, int tr)
{ // v = 1, tl = 0, tr = n-1
    if (tl == tr)
    {
        t[v] = segData(a[tl], s[tl]);
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        build(a, s, 2 * v, tl, mid);
        build(a, s, 2 * v + 1, mid + 1, tr);

        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

void update(int v, int tl, int tr, int pos, int addval, int subval)
{
    if (tl == tr)
    {
        t[v] = segData(addval, subval);
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        if (pos > mid)
        {
            update(2 * v + 1, mid + 1, tr, pos, addval, subval);
        }
        else
            update(2 * v, tl, mid, pos, addval, subval);

        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

void solve()
{
    int m, k, inp;
    string s;
    int n, q;
    cin >> n >> q;

    t.assign(4 * n, {});

    //
    vi vec(n);

    vi add(n), sub(n);
    fo(i, n)
    {
        cin >> vec[i];
        add[i] = vec[i] + i;
        sub[i] = vec[i] - i;
    }

    build(add, sub, 1, 0, n - 1);

    println(t[1].ans);

    while (q--)
    {
        int p, x;
        cin >> p >> x;
        p--;
        update(1, 0, n - 1, p, x + p, x - p);

        println(t[1].ans);
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

    int T;
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