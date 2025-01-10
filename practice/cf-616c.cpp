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

int sz[1001][1001];
pii parent[1001][1001];

void makeSet(int i, int j)
{
    parent[i][j] = {i, j};
    sz[i][j] = 1;
}

pii findSet(int i, int j)
{
    if (parent[i][j] == mp(i, j))
        return {i, j};

    return parent[i][j] = findSet(parent[i][j].first, parent[i][j].second);
}

void unionSet(pii a, pii b)
{
    a = findSet(a.first, a.second);
    b = findSet(b.first, b.second);
    if (a != b)
    {
        if (sz[a.first][a.second] < sz[b.first][b.second])
        {
            swap(a, b);
        }
        parent[b.first][b.second] = a;
        sz[a.first][a.second] += sz[b.first][b.second];
    }
}

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);
    cin >> m;

    vector<vector<char>> lab(n, vector<char>(m));
    fo(i, n)
    {
        fo(j, m)
        {
            cin >> lab[i][j];

            if (lab[i][j] == '.')
            {
                //
                makeSet(i, j);

                if (i != 0 and lab[i - 1][j] == '.')
                    unionSet({i, j}, {i - 1, j});
                if (j != 0 and lab[i][j - 1] == '.')
                    unionSet({i, j}, {i, j - 1});
            }
        }
    }

    vector<string> ans(n);

    fo(i, n)
    {
        string thisstr = "";
        fo(j, m)
        {

            if (lab[i][j] == '*')
            {
                //

                // deb(i), deb(j);
                set<pii> st;

                vpii dir = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

                for (auto d : dir)
                {
                    pii tocheck = {i + d.first, j + d.second};
                    if (tocheck.first < 0 or tocheck.first >= n or tocheck.second < 0 or tocheck.second >= m or lab[tocheck.first][tocheck.second] == '*')
                        continue;

                    st.insert(findSet(tocheck.first, tocheck.second));
                }

                int answer = 1;
                for (auto item : st)
                {
                    // deb(item.first), deb(item.second);

                    answer += sz[item.first][item.second];
                }

                answer %= 10;

                thisstr += to_string(answer);
            }
            else
                thisstr += '.';

            // deb(i), deb(j), deb(thisstr);
        }
        println(thisstr);
    }

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
    // in(T);
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