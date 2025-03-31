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

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

int n;
struct segData
{
    bool hasPalindrome = false;

    int leftfirst = -1, leftsecond = -2, rightfirst = -3, rightsecond = -4;

    int toPush = 0;

    segData() = default;
    segData(int val_) : leftfirst(val_), rightsecond(val_) {}

    void push(segData &child1, segData &child2)
    {
        if (toPush)
        {
            //
            (child1.leftfirst += toPush) %= 26;
            (child2.leftfirst += toPush) %= 26;

            if (child1.leftsecond != -2)
            {
                (child1.leftsecond += toPush) %= 26;
            }
            if (child2.leftsecond != -2)
            {
                (child2.leftsecond += toPush) %= 26;
            }

            if (child1.rightfirst != -3)

                (child1.rightfirst += toPush) %= 26;
            if (child2.rightfirst != -3)
                (child2.rightfirst += toPush) %= 26;

            (child1.rightsecond += toPush) %= 26;
            (child2.rightsecond += toPush) %= 26;

            (child1.toPush += toPush) %= 26, (child2.toPush += toPush) %= 26;
            toPush = 0;
        }
    }

    segData operator+(const segData &toAdd)
    {
        segData toret;
        //

        toret.hasPalindrome = hasPalindrome || toAdd.hasPalindrome || (rightfirst == toAdd.leftfirst) ||
                              (rightsecond == toAdd.leftfirst) || (rightsecond == toAdd.leftsecond);

        toret.leftfirst = leftfirst, toret.leftsecond = leftsecond,
        toret.rightfirst = toAdd.rightfirst, toret.rightsecond = toAdd.rightsecond;

        if (toret.rightfirst == -3 && toret.leftsecond == -2)
        {
            //
            toret.rightfirst = toret.leftfirst;
            toret.leftsecond = toret.rightsecond;
        }
        else if (toret.rightfirst == -3)
            toret.rightfirst = toret.leftsecond;
        else if (toret.leftsecond == -2)
            toret.leftsecond = toret.rightfirst;

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
    if ((l == tl) && (r == tr))
    {
        return t[v];
    }
    else
    {
        t[v].push(t[2 * v], t[2 * v + 1]);

        int mid = tl + (tr - tl) / 2;

        if (l > min(mid, r))
            return findResult(2 * v + 1, mid + 1, tr, max(l, mid + 1), r);
        else if (max(l, mid + 1) > r)
            return findResult(2 * v, tl, mid, l, min(mid, r));

        return findResult(2 * v, tl, mid, l, min(mid, r)) + findResult(2 * v + 1, mid + 1, tr, max(l, mid + 1), r);
    }
}

void update(int v, int tl, int tr, int l, int r, int change) // this is change
{
    if (l > r)
        return;

    if (tl == l and tr == r)
    {
        (t[v].leftfirst += change) %= 26;

        if (t[v].leftsecond != -2)
            (t[v].leftsecond += change) %= 26;

        if (t[v].rightfirst != -3)
            (t[v].rightfirst += change) %= 26;

        (t[v].rightsecond += change) %= 26;

        (t[v].toPush += change) %= 26;
    }
    else
    {

        t[v].push(t[2 * v], t[2 * v + 1]);

        int mid = tl + (tr - tl) / 2;

        update(2 * v, tl, mid, l, min(mid, r), change);
        update(2 * v + 1, mid + 1, tr, max(l, mid + 1), r, change);

        t[v] = t[2 * v] + t[2 * v + 1];

        //
    }
}

void solve()
{
    int m, k, inp;
    string s; // n is above

    cin >> n >> m;

    //
    cin >> s;

    //
    vi vec(n);
    fo(i, n) vec[i] = s[i] - 'a';

    t.assign(4 * n + 1, 0);
    build(vec, 1, 0, n - 1);
    //

    fo(q, m)
    {
        //
        int ty;
        cin >> ty;

        //
        if (ty == 1)
        {
            int l, r, x;
            cin >> l >> r >> x;

            //
            update(1, 0, n - 1, l - 1, r - 1, x);
        }
        else
        {
            int l, r;
            cin >> l >> r;

            if (findResult(1, 0, n - 1, l - 1, r - 1).hasPalindrome)
                println("NO");
            else
                println("YES");
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