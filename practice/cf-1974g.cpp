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

const int MOD1 = 1000000007;
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

struct segData
{
    // returns max rn
    int val = 0;
    int mini = inf;

    //
    int change = 0;
    int maxiChange = inf;
    segData() = default;
    segData(int val_, int mini_) : val(val_), mini(mini_) {}

    void push(segData &child1, segData &child2)
    {
        if (change)
        {
            child1.change += change, child2.change += change;
            child1.val += change, child2.val += change;
            child1.mini += change, child2.mini += change;
            change = 0;
        }
        if (maxiChange != inf)
        {
            child1.maxiChange = min(maxiChange, child1.maxiChange), child2.maxiChange = min(maxiChange, child2.maxiChange);
            child1.val = min(maxiChange, child1.val), child2.val = min(maxiChange, child2.val);

            child1.mini = min(maxiChange, child1.mini), child2.mini = min(maxiChange, child2.mini);
            maxiChange = inf;
        }
    }

    segData operator+(const segData &toAdd)
    {
        segData toret;
        toret.val = max(val, toAdd.val);
        toret.mini = min(mini, toAdd.mini);
        return toret;
    }
};
vector<segData> t; // keep N = n, n is size of array

void build(const vi &a, int v, int tl, int tr)
{ // v = 1, tl = 0, tr = n-1
    if (tl == tr)
    {
        t[v] = {a[tl], a[tl]};
    }
    else
    {
        int mid = tl + (tr - tl) / 2;

        build(a, 2 * v, tl, mid);
        build(a, 2 * v + 1, mid + 1, tr);

        t[v] = t[2 * v] + t[2 * v + 1]; //
    }
}

segData findResult(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return segData(-inf, inf);

    if ((l == tl) && (r == tr))
    {
        return t[v];
    }
    else
    {

        t[v].push(t[2 * v], t[2 * v + 1]);

        int mid = tl + (tr - tl) / 2;

        return findResult(2 * v, tl, mid, l, min(mid, r)) +
               findResult(2 * v + 1, mid + 1, tr, max(l, mid + 1), r);
    }
}

void update(int v, int tl, int tr, int l, int r, int moreChange) //
{
    if (l > r)
        return;

    if (tl == l and tr == r)
    {

        t[v].change += moreChange;
        t[v].val += moreChange;

        t[v].mini += moreChange;
    }
    else
    {

        t[v].push(t[2 * v], t[2 * v + 1]);

        int mid = tl + (tr - tl) / 2;

        update(2 * v, tl, mid, l, min(mid, r), moreChange);
        update(2 * v + 1, mid + 1, tr, max(l, mid + 1), r, moreChange);

        t[v] = t[2 * v] + t[2 * v + 1];
    }
}
void updateMax(int v, int tl, int tr, int l, int r, int newMax) //
{
    if (l > r)
        return;

    if (tl == l and tr == r)
    {
        t[v].maxiChange = min(t[v].maxiChange, newMax); //
        t[v].val = min(t[v].val, newMax);

        t[v].mini = min(t[v].mini, newMax);
    }
    else
    {

        t[v].push(t[2 * v], t[2 * v + 1]);

        int mid = tl + (tr - tl) / 2;

        updateMax(2 * v, tl, mid, l, min(mid, r), newMax);
        updateMax(2 * v + 1, mid + 1, tr, max(l, mid + 1), r, newMax);

        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    int x;
    cin >> m >> x;

    //
    vpii cost(m);
    fo(i, m)
    {
        cin >> cost[i].first;
        cost[i].second = i;
    }

    sortall(cost);
    //

    vi money(m);
    fo(i, m) money[i] = i * x;

    //
    t.assign(4 * m + 5, {});
    build(money, 1, 0, m - 1);

    //

    int ans = 0;
    fo(i, m)
    {
        int ind = cost[i].second;
        int price = cost[i].first;

        int moneyavai = findResult(1, 0, m - 1, ind, m - 1).mini;
        // deb(moneyavai);

        if (moneyavai >= price)
        {
            ans++;

            update(1, 0, m - 1, ind, m - 1, -price);

            updateMax(1, 0, m - 1, 0, ind - 1, moneyavai - price);
        }
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