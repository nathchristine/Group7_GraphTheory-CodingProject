#include <bits/stdc++.h>
using namespace std;

#define N 16
#define int long long
int INF = 1e18;
int n, m;
int deg[N];
int a[N][N], d[N][N];
vector<bool> mark;
vector<int> mem(1 << 15);
map<pair<int, int>, vector<pair<int, int>>> edgeMap;
vector<int> edgeSequence; 

void dfs(int v) {
    if (mark[v]) return;
    mark[v] = true;
    for (int i = 0; i < n; i++) {
        if (a[v][i] < INF)
            dfs(i);
    }
}

int rec(int mask) {
    int &res = mem[mask];
    if (res != -1) return res;
    if (mask == 0) return res = 0;
    res = INF;
    int i1;
    for (i1 = 0; (mask & (1 << i1)) == 0; i1++);
    for (int i2 = i1 + 1; i2 < n; i2++) {
        if (mask & (1 << i2)) {
            int newCost = d[i1][i2] + rec(mask ^ (1 << i1) ^ (1 << i2));
            if (newCost < res) {
                res = newCost;
            }
        }
    }
    return res;
}

void reconstructPath(int u, int v) {
    if (d[u][v] == a[u][v]) {
        for (auto &[cost, edgeId] : edgeMap[{min(u, v), max(u, v)}]) {
            if (cost == a[u][v]) {
                edgeSequence.push_back(edgeId);
                break;
            }
        }
    } else {
        for (int k = 0; k < n; k++) {
            if (d[u][v] == d[u][k] + d[k][v]) {
                reconstructPath(u, k);
                reconstructPath(k, v);
                return;
            }
        }
    }
}

int32_t main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) a[i][j] = INF;
    }
    int sum = 0;
    for (int i = 0; i < m; i++) {
        int edgeId, x, y, c;
        cin >> edgeId >> x >> y >> c;
        x--; y--;
        a[x][y] = min(a[x][y], c);
        a[y][x] = min(a[y][x], c);
        sum += c;
        deg[x]++, deg[y]++;
        edgeMap[{min(x, y), max(x, y)}].push_back({c, edgeId});
    }

    mark.assign(N, false);
    dfs(0);
    bool bad = false;
    for (int i = 0; i < n; i++) {
        if (!mark[i] && deg[i] > 0)
            bad = true;
    }
    if (bad) {
        cout << -1 << "\n";
        return 0;
    }

    memcpy(d, a, sizeof a);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    mem.assign(1 << 15, -1);
    int mask = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1)
            mask |= 1 << i;
    }

    int res = sum + rec(mask);
    cout << res << "\n";
                 
    edgeSequence.clear();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((deg[i] % 2 == 1) && (deg[j] % 2 == 1)) {
                reconstructPath(i, j);
            }
        }
    }

    cout << "Edges: ";
    for (int edge : edgeSequence) {
        cout << edge << " ";
    }
    cout << "\n";

    return 0;
}
