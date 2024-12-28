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
const int inf = 1e16;
const int NN = 2e5 + 5;

//______________________________________________________________________________

// int a[N];

//___________________________SOLUTION_BEGINS_HERE_______________________________

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);

    vi vec(n + 1), pre(n + 1);
    vi sameTillBack(n + 1), sameTillAhead(n + 1);
    fo(i, n)
    {
        cin >> vec[i + 1];
        pre[i + 1] = pre[i] + vec[i + 1];

        if (vec[i] == vec[i + 1])
            sameTillBack[i + 1] = (sameTillBack[i] > 0 ? sameTillBack[i] : 1) + 1;
    }

    Fo(i, n - 1, -1)
    {
        if (vec[i] == vec[i + 1])
            sameTillAhead[i] = (sameTillAhead[i + 1] > 0 ? sameTillAhead[i + 1] : 1) + 1;
    }

    vi ans(n + 1, inf);

    Fo(i, 1, n + 1)
    {
        {
            //
            int cur = vec[i];
            int preVal = pre[i - 1];
            int lookingFor = preVal - cur;

            // less than than looking for
            auto it = lower_bound(pre.begin(), pre.end(), lookingFor);
            if (it != pre.begin())
            {
                it--;
                int ind = it - pre.begin();

                int howFar = (i - 1) - ind;

                if (howFar == 1)
                    ans[i] = 1;
                else
                {
                    if (sameTillBack[i - 1] >= howFar and sameTillBack[i - 1] < i - 1)
                    {
                        ans[i] = min(ans[i], sameTillBack[i - 1] + 1);
                    }
                    else if (sameTillBack[i - 1] < howFar)
                        ans[i] = min(ans[i], howFar);
                }
            }
        }
        {

            int cur = vec[i];
            int preVal = pre[i];
            int lookingFor = preVal + cur;

            auto it = upper_bound(pre.begin(), pre.end(), lookingFor);

            if (it != pre.end())
            {
                int ind = it - pre.begin() - 1;
                int howFar = ind - (i - 1);

                if (howFar == 1)
                    ans[i] = 1;
                else
                {
                    if (sameTillAhead[i + 1] >= howFar and sameTillAhead[i + 1] + i < n)
                    {
                        ans[i] = min(ans[i], sameTillAhead[i + 1] + 1);
                    }
                    else if (sameTillAhead[i + 1] < howFar)
                        ans[i] = min(ans[i], howFar);
                }
            }
        }
    }
    Fo(i, 1, n + 1)
    {
        if (ans[i] == inf)
        {
            print(-1);
        }
        else
            print(ans[i]);
    }
    println("");
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
    while (T--)
    {

        solve();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    // cerr << "Time taken : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;

    return 0;
}