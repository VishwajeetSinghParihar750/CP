#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define N 200010
ld t[N];
ll s[N], a[N], n, T, l, r;
ld cl(int l, int r)
{
    return t[r] / t[l - 1] - (s[r] - s[l - 1]);
}
int main()
{
    cin >> T;
    t[0] = 1;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            s[i] = s[i - 1] + a[i];
            t[i] = t[i - 1] * a[i];
        }
        l = r = 1;
        vector<int> p;
        for (int i = 1; i <= n; i++)
            if (a[i] >= 2)
                p.push_back(i);
        if (p.size() > 60)
        {
            printf("%d %d\n", p[0], p.back());
            continue;
        }
        for (int i : p)
            for (int j : p)
                if (i <= j && cl(i, j) > cl(l, r))
                    l = i, r = j;
        cout << l << " " << r << "\n";
    }
    return 0;
}