#include <bits/stdc++.h>

using i64 = long long;

void solve()
{
    int n, k, x;
    std::cin >> n >> k >> x;

    int xors = 0;
    if (n % 4 == 0)
        xors = n;
    else if (n % 4 == 1)
        xors = 1;
    else if (n % 4 == 2)
        xors = n + 1;
    else
        xors = 0;

    if (xors != 0 && x != xors)
    {
        std::cout << "NO\n";
        return;
    }
    if (xors != 0 && k % 2 == 0)
    {
        std::cout << "NO\n";
        return;
    }
    if (xors == 0 && k % 2 == 1)
    {
        std::cout << "NO\n";
        return;
    }

    std::vector<std::vector<int>> a;
    std::vector<bool> vis(n + 1);

    if (n % 4 == 1)
    {
        for (int i = 0; i < n; i += 2)
        {
            if (i == 0)
            {
                a.push_back({1});
            }
            else
            {
                a.push_back({i, i + 1});
            }
        }
    }
    else if (n % 4 == 0 || n % 4 == 2)
    {
        int l = std::__lg(n);
        for (int i = (1 << l); i <= n; i++)
        {
            if (i == x)
            {
                vis[i] = true;
                a.push_back({i});
            }
            else
            {
                vis[i] = vis[i ^ x] = true;
                a.push_back({i, i ^ x});
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                a[0].push_back(i);
            }
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;
            if ((i ^ x) > n)
                continue;
            if (i == x)
            {
                vis[i] = true;
                a.push_back({i});
            }
            else
            {
                vis[i] = vis[i ^ x] = true;
                a.push_back({i, i ^ x});
            }
        }
        if (a.empty())
        {
            std::cout << "NO\n";
            return;
        }
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                a[0].push_back(i);
            }
        }
    }

    if (k > a.size())
    {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";

    for (int i = k; i < a.size(); i++)
    {
        a[0].insert(a[0].end(), a[i].begin(), a[i].end());
    }
    a.resize(k);

    for (auto v : a)
    {
        std::cout << v.size();
        for (auto x : v)
        {
            std::cout << " " << x;
        }
        std::cout << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}
