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

int doIt(int n, const vi &vec)
{
    bool goesDown = false, goesUp = false;

    vi upOrDown(n);

    Fo(i, 1, n)
    {
        if (vec[i] > vec[i - 1])
        {
            upOrDown[i] = 1;
        }
        else if (vec[i] < vec[i - 1])
            upOrDown[i] = -1;
        else
            upOrDown[i] = 0;
    }

    int upCount = count(upOrDown.begin(), upOrDown.end(), 1);
    int downCount = count(upOrDown.begin(), upOrDown.end(), -1);

    vi newVec, newVec2;

    int ans = 0, ans2 = 0;
    if (upCount > 1 and downCount > 1)
    {
        return inf;
    }
    if (downCount == 0)
    {
        return 0;
    }
    if (upCount == 1)
    {

        if (downCount == 1)
        {
            int downPos = find(upOrDown.begin(), upOrDown.end(), -1) - upOrDown.begin();
            for (int i = downPos; i < n; i++)
                newVec.pb(vec[i]);

            for (int i = 0; i < downPos; i++)
                newVec.pb(vec[i]);

            ans = n - downPos;

            int upPos = find(upOrDown.begin(), upOrDown.end(), 1) - upOrDown.begin();
            for (int i = upPos; i < n; i++)
                newVec2.pb(vec[i]);

            for (int i = 0; i < upPos; i++)
                newVec2.pb(vec[i]);

            ans2 = n - upPos;

            vi v = vec;
            sortall(v);

            int totAns = inf;
            if (v == newVec)
                totAns = min(totAns, ans);

            if (v == newVec2)
                totAns = min(totAns, ans2);

            reverse(all(newVec2)), reverse(all(newVec));

            if (v == newVec)

                totAns = min(totAns, ans + 1);

            if (v == newVec2)
                totAns = min(totAns, ans2 + 1);

            return totAns;
        }
        else
        {
            int upPos = find(upOrDown.begin(), upOrDown.end(), 1) - upOrDown.begin();
            // deb(upPos);
            for (int i = upPos; i < n; i++)
                newVec.pb(vec[i]);

            for (int i = 0; i < upPos; i++)
                newVec.pb(vec[i]);

            ans = n - upPos;
        }
    }
    else if (downCount == 1)
    {
        if (upCount == 0)
        {
            return 1;
        }
        else
        {
            int downPos = find(upOrDown.begin(), upOrDown.end(), -1) - upOrDown.begin();
            for (int i = downPos; i < n; i++)
                newVec.pb(vec[i]);

            for (int i = 0; i < downPos; i++)
                newVec.pb(vec[i]);

            ans = n - downPos;
        }
    }

    vi cpy = newVec;
    sortall(cpy);
    if (cpy == newVec)
    {
        // ans stays
    }
    else
    {
        reverse(all(cpy));

        if (cpy == newVec)
        {
            ans = ans + 1;
        }
        else
        {
            ans = inf;
        }
    }

    return ans;
}
void solve()
{
    int n, m, k, inp;
    string s;
    in(n);

    vi vec(n);
    fo(i, n) cin >> vec[i];
    vi sortVec = vec;
    sortall(sortVec);

    if (vec == sortVec)
    {
        println(0);
        return;
    }
    reverse(all(sortVec));
    if (vec == sortVec)
    {
        println(1);
        return;
    }

    //
    int finalAns = inf;
    finalAns = min(finalAns, doIt(n, vec));
    reverse(all(vec));
    finalAns = min(finalAns, doIt(n, vec) + 1);

    cout << (finalAns >= inf ? -1 : finalAns) << endl;
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