#include <iostream>
#include <algorithm>
#include <vector>

#define fi first
#define se second

using namespace std;

const int maxN = 1e6;

int n;
int a[maxN+5], b[maxN+5];
pair<int, int> tmp[maxN+5];
int val1[maxN+5], val2[maxN+5];
int trace[maxN+5];
int dp[maxN+5];
int T[maxN*4+5];

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return (a.fi == b.fi ? a.se > b.se : a.fi < b.fi);
}

void mapping(int a[], int val[])
{
    vector<int> v;
    for(int i = 1; i <= n; ++i) v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for(int i = 1; i <= n; ++i)
    {
        int id = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        val[id] = a[i];
        a[i] = id;
    }
}

void update(int node, int l, int r, int u, int v, int id)
{
    if(l > v || r < u) return;
    if(u <= l && r <= v)
    {
        if(dp[T[node]] < dp[id]) T[node] = id;
        return;
    }
    int mid = (l + r) / 2;
    update(node * 2, l, mid, u, v, id);
    update(node * 2 + 1, mid + 1, r, u, v, id);
    if(dp[T[node]] < dp[T[node*2]]) T[node] = T[node*2];
    if(dp[T[node]] < dp[T[node*2+1]]) T[node] = T[node*2+1];
}

int getMax(int node, int l, int r, int u, int v)
{
    if(l > v || r < u) return 0;
    if(u <= l && r <= v) return T[node];
    int mid = (l + r) / 2;
    int Left = getMax(node * 2, l, mid, u, v);
    int Right = getMax(node * 2 + 1, mid + 1, r, u, v);
    if(dp[Left] > dp[Right]) return Left;
    return Right;
}

void tracing()
{
    vector<pair<int, int>> res;
    int id = 0;
    dp[id] = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(dp[id] < dp[i]) id = i;
    }
    while(id > 0)
    {
        res.push_back({val1[a[id]], val2[b[id]]});
        id = trace[id];
    }
    reverse(res.begin(), res.end());
    cout << res.size() << '\n';
    for(pair<int, int> p : res)
    {
        cout << p.fi << ' ' << p.se << '\n';
    }
}

int main()
{
    freopen(".inp", "r", stdin);
    freopen(".out", "w", stdout);

    cin >> n;
    int d = 0;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i] >> b[i];
        tmp[i] = make_pair(a[i], b[i]);
        trace[i] = n + 1;
    }

    sort(tmp + 1, tmp + n + 1, cmp);
    for(int i = 1; i <= n; ++i)
    {
        a[i] = tmp[i].fi;
        b[i] = tmp[i].se;
    }

    mapping(a, val1);
    mapping(b, val2);

    a[0] = 0; b[0] = 0;
    for(int i = 1; i <= n; ++i)
    {
        int id = getMax(1, 1, n, 1, b[i] - 1);
        dp[i] = dp[id] + 1;
        trace[i] = id;
        update(1, 1, n, b[i], b[i], i);
    }

    tracing();

    return 0;
}
