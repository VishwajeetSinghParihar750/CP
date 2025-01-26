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
const int inf = LLONG_MAX;
const int NN = 2e5 + 5;

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

struct segData
{
    // returns sum rn
    int val = 0;
    int toPush = 0;
    segData() = default;
    segData(int val_) : val(val_) {}

    segData operator+(const segData &toAdd)
    {
        segData toret;
        toret.val = min(val, toAdd.val);
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
        return inf;

    if ((l == tl) && (r == tr))
        return t[v];

    else
    {
        // t[v].push(t[2 * v], t[2 * v + 1]);

        int mid = tl + (tr - tl) / 2;

        return findResult(2 * v, tl, mid, l, min(mid, r)) +
               findResult(2 * v + 1, mid + 1, tr, max(l, mid + 1), r);
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    cin >> n >> k;
    vi vec(n), pre(n + 1);

    fo(i, n)
    {
        cin >> vec[i];

        pre[i + 1] = pre[i] + vec[i];
    }

    t.assign(4 * (n + 1), 0);

    build(pre, 1, 0, n);
    //

    int ans = -1;

    auto check = [&](int curpos, int mid)
    {
        int pref = pre[curpos - 1];
        //

        int minpre = findResult(1, 0, n, curpos, mid).val;

        return -k <= (minpre - pref);
    };

    int ansl = -1, ansr = -1;

    fo(i, n)
    {

        //

        int l = i, r = n + 1;

        while (r - l > 1)
        {
            int mid = (l + r) / 2;

            //
            if (check(i + 1, mid))
                l = mid;
            else
                r = mid;
        }

        if (l > i)
        {
            if (l - i > ans)
            {
                ans = l - i;
                ansl = i + 1, ansr = l;
            }
        }

        //
    }
    if (ans == -1)
        println(-1);
    else
        print(ansl),
            println(ansr);
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