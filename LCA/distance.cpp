#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int MAXN = 50010;
const int MAXL = 32;

vector<pair<int, int> > adj[MAXN];
pair<int, int> pai[MAXN];
int anc[MAXN][MAXL], dp[MAXN][MAXL];
int nivel[MAXN];

void dfs(int u){
    for(auto no: adj[u]){
        int v = no.f;
        int c = no.s;

        if(nivel[v] == -1){
            pai[v].f = u;
            pai[v].s = c;
            nivel[v] = nivel[u]+1;
            dfs(v);
        }
    }
}


int LCA(int u, int v){
    if(nivel[u] < nivel[v])
        swap(u, v);
    int custo = 0;
    for(int i = MAXL-1; i >= 0; i--){
        if(nivel[u] - (1 << i) >= nivel[v]){
            custo += dp[u][i];
            u = anc[u][i];

        }
    }

    if(u == v)
        return custo;

    for(int i = MAXL-1; i >= 0; i--){
        if(anc[u][i] != -1 && anc[u][i] != anc[v][i]){
            custo += dp[u][i] + dp[v][i];
            u = anc[u][i];
            v = anc[v][i];

        }
    }
    custo += dp[u][0] + dp[v][0];
    return custo;
}

int main()
{

    int n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for(int i = 0; i < n; i++){
        pai[i].f = -1;
        pai[i].s = -1;
        nivel[i] = -1;
    }

    memset(anc, -1, sizeof anc);
    memset(dp, -1, sizeof dp);

    nivel[0] = 0;
    dfs(0);

    for(int i = 0; i < n; i++){
        anc[i][0] = pai[i].f;
        dp[i][0] = pai[i].s;
    }


    for(int j = 1; j < MAXL; j++){
        for(int i = 0; i < n; i++){
            if(anc[i][j-1] != -1){
                if(dp[anc[i][j-1]][j-1] != -1){
                    dp[i][j] = dp[i][j-1] + dp[anc[i][j-1]][j-1];
                }
                anc[i][j] = anc[anc[i][j-1]][j-1];
            }
        }
    }


    int q;
    cin >> q;

    while(q--){
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }

    return 0;
}
