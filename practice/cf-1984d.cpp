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

int pre, suf, minmiddle;

bool works(const string &s, int l, int r)
{
    string t = s.substr(l, r - l + 1) + "#" + s;

    int matchlen = r - l + 1;

    // deb(matchlen);

    // deb(t);
    int n = t.size();
    vi matching(n, 0);

    for (int i = 1; i < n; i++)
    {
        int j = matching[i - 1];

        while (j > 0 and t[i] != t[j])
            j = matching[j - 1];

        matching[i] = j + (t[i] == t[j]);
        // deb(i), deb(matching[i]);
    }

    pre = -1, suf = -1, minmiddle = inf;

    int cnt = 0;
    for (int i = n - 1; i > matchlen;)
    {
        if (t[i] != 'a')
        {
            if (matching[i] != matchlen)
            {
                // deb(i);
                // deb("RETURN");
                return false;
            }
            else
                i -= matchlen;

            if (suf == -1)
                suf = cnt;
            else
                minmiddle = min(minmiddle, cnt);

            cnt = 0;
        }
        else
        {
            i--;
            cnt++;
        }
    }
    pre = cnt;

    return true;
}

void solve()
{
    int n, m, k, inp;
    string s;

    cin >> s;
    n = s.size();

    vi nonapos;
    fo(i, n) if (s[i] != 'a') nonapos.pb(i);

    //
    vi freq(26);
    fo(i, n) freq[s[i] - 'a']++;

    //

    int start = 0;
    while (s[start] == 'a')
        start++;

    //
    if (start == n)
    {
        println(n - 1);
        return;
    }

    vi curfreq(26, 0);

    int ans = 0;

    for (int i = 0; i < nonapos.size(); i++)
    {
        curfreq[s[nonapos[i]] - 'a']++;

        bool doit = true;
        for (int c = 1; c < 26; c++)
        {
            if ((freq[c] != 0) and ((curfreq[c] == 0) or (freq[c] % curfreq[c])))
            {
                doit = false;
                break;
            }
        }

        if (doit)
        {
            // deb(i);
            if (works(s, nonapos[0], nonapos[i]))
            {
                // //
                // deb("WORKS ");
                // deb(i);
                // deb(nonapos[i]);
                // deb(pre), deb(suf), deb(minmiddle);

                pre = min(pre, minmiddle), suf = min(suf, minmiddle);
                // deb(minmiddle);

                // deb(pre), deb(suf);

                for (int p = 0; p <= pre; p++)
                {
                    if (minmiddle == inf)
                        ans += (suf + 1);
                    else
                        ans += min(minmiddle - p, suf) + 1;

                    // deb(p);
                    // deb(ans);
                }
            }
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