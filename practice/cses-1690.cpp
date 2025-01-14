// Author__ VISHWAJEET_SINGH_PARIHAR __
#include <bits/stdc++.h>

using namespace std;

#define fo(i, n) for (int i = 0; i < n; i++)

#define println(n) cout << n << endl
#define print(n) cout << n << " "
#define in(n) cin >> n
#define pb push_back
typedef vector<int> vi;
typedef vector<vi> vvi;
const int MOD1 = 1000000007;

void solve()
{
    int n, m, k, inp;
    string s;
    in(n);
    cin >> m;

    vvi leadtome(n);
    fo(i, m)
    {
        int a, b;
        cin >> a >> b;

        a--, b--;

        leadtome[b].pb(a);
    }

    vvi dp(1 << n, vi(n));
    dp[1][0] = 1;

    for (int i = 2; i < (1 << n); i++)
    {
        if ((i & (1 << (n - 1)) and i != ((1 << n)) - 1))
            continue; //  this just ended up halving the time

        fo(v, n)
        {
            //
            if (i & (1 << v))
            {
                // this is the final one
                for (auto u : leadtome[v])
                {
                    //
                    (dp[i][v] += dp[i - (1 << v)][u]) %= MOD1;
                }
            }
        }
    }

    println(dp[(1 << n) - 1][n - 1]);
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

    solve();

    return 0;
}