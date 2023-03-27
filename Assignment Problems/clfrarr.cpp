// https://www.spoj.com/problems/CLFLARR/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b;
    cin >> a >> b;
    struct triple
    {
        int b, c, d;
    };
    int c, d;
    vector<triple> v;
    while (cin >> b >> c >> d)
    {
        triple t;
        t.b = b;
        t.c = c;
        t.d = d;
        v.push_back(t);
    }
    for (c = 1; c <= a; c++)
    {
        d = 0;
        for (b = v.size() - 1; b >= 0; b--)
            if (v[b].b <= c && c <= v[b].c)
            {
                d = v[b].d;
                break;
            }
        cout << d << endl;
    }
}
