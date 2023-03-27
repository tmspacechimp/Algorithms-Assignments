// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1878
#include <bits/stdc++.h>
using namespace std;
char ch[69][69];
int fix[69][69];
queue<pair<int, int>> q;
int n, m, i, j, x, y, k, z, t, alo, ans, xx[69], yy[69], dp[6969][69], a[4] = {-1, 1, 0, 0}, b[4] = {0, 0, -1, 1}, c[8] = {1, 1, 1, -1, -1, -1, 0, 0}, d[8] = {0, 1, -1, 0, -1, 1, 1, -1};
inline bool ok(int i, int j)
{
    if (!(i >= 1 && i <= n && j >= 1 && j <= m && ch[i][j] != '#' && ch[i][j] != '*' && ch[i][j] != '~'))
        return 0;
    for (z = 0; z <= 7; z++)
        if (i + c[z] >= 1 && i + c[z] <= n && j + d[z] >= 1 && j + d[z] <= m)
            if (ch[i + c[z]][j + d[z]] == '*')
                return 0;
    return 1;
}
int go(int x1, int y1, int x2, int y2)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            fix[i][j] = 69696969;
    fix[x1][y1] = 0;
    q.push({x1, y1});
    while (q.size())
    {
        x1 = q.front().first;
        y1 = q.front().second;
        for (i = 0; i <= 3; i++)
            if (ok(x1 + a[i], y1 + b[i]) && fix[x1 + a[i]][y1 + b[i]] == 69696969)
            {
                fix[x1 + a[i]][y1 + b[i]] = fix[x1][y1] + 1;
                q.push({x1 + a[i], y1 + b[i]});
            }
        q.pop();
    }
    return fix[x2][y2];
}
main()
{
    while (cin >> n >> m)
    {
        if (n * m == 0)
            break;
        t = 0;
        ans = 69696969;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                cin >> ch[i][j];
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (ch[i][j] == '@')
                    x = i, y = j;
        if (!ok(x, y))
        {
            printf("-1\n");
            continue;
        }
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (ch[i][j] == '!' && !ok(i, j))
                    x = 69;
        if (x == 69)
        {
            printf("-1\n");
            continue;
        }
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (ch[i][j] == '!')
                    t++, xx[t] = i, yy[t] = j;
        if (t == 0)
        {
            printf("0\n");
            continue;
        }
        for (i = 1; i < (1 << t); i++)
            for (j = 0; j < t; j++)
                if (i & (1 << j))
                {
                    dp[i][j] = 69696969;
                    alo = i ^ (1 << j);
                    if (alo == 0)
                        dp[i][j] = go(x, y, xx[j + 1], yy[j + 1]);
                    else
                        for (k = 0; k < t; k++)
                            if (alo & (1 << k))
                                dp[i][j] = min(dp[i][j], dp[alo][k] + go(xx[j + 1], yy[j + 1], xx[k + 1], yy[k + 1]));
                }
        if (dp[(1 << t) - 1][0] >= 69696969)
        {
            printf("-1\n");
            continue;
        }
        for (i = 0; i < t; i++)
            ans = min(ans, dp[(1 << t) - 1][i] + go(x, y, xx[i + 1], yy[i + 1]));
        printf("%d\n", ans);
    }
}
