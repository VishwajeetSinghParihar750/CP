// Author__ VISHWAJEET_SINGH_PARIHAR __
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

#define ll long long
// #define int ll

#define println(n) cout << n << endl
#define print(n) cout << n << " "
#define in(n) cin >> n
#define pb push_back

#define fo(i, n) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

const int NN = 2e5 + 5;

vector<vpii> adj(NN);
priority_queue<ll> dist[NN];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> s;

void solve()
{
    int n, m, k, inp;
    cin >> n >> m >> k;

    fo(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].emplace_back(b, c);
    }

    s.push({0, 1});

    dist[1].push(0);

    while (!s.empty())
    {
        //
        auto beg = s.top();

        int cur = beg.second;
        ll discur = beg.first;

        s.pop();

        if (discur > dist[cur].top())
            continue;

        for (auto &p : adj[cur])
        {
            ll newdis = discur + p.second;

            if (dist[p.first].size() < k)
            {
                s.push({newdis, p.first});
                dist[p.first].push(newdis);
            }
            else if (newdis < dist[p.first].top())
            {
                dist[p.first].pop();
                dist[p.first].push(newdis);

                s.push({newdis, p.first});
            }
        }
    }
    //

    vector<ll> ans;
    while (!dist[n].empty())
    {
        ans.push_back(dist[n].top());
        dist[n].pop();
    }
    reverse(ans.begin(), ans.end());
    for (auto a : ans)
        cout << a << " ";
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