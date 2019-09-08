#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXL = 30;

int nivel[MAXN], pai[MAXN];
int ancestral[MAXN][MAXL];
vector<int> adj[MAXN];

void dfs(int u){
    for(int v: adj[u]){
        if(nivel[v] == -1){
            nivel[v] = nivel[u]+1;
            pai[v] = u;
            dfs(v);
        }
    }
}

void build(int n){

    for(int i = 1; i <= n; i++){
        nivel[i] = pai[i] = -1;
    }

    memset(ancestral, -1, sizeof ancestral);

    nivel[1] = 0;
    dfs(1);

    for(int i = 1; i <= n; i++){
        ancestral[i][0] = pai[i];
    }


    for(int j = 1; j < MAXL; j++){
        for(int i = 1; i <= n; i++){
            if(ancestral[i][j-1] == -1)
                continue;
            ancestral[i][j] = ancestral[ancestral[i][j-1]][j-1];
        }
    }
}

int LCA(int u, int v){
    if(nivel[u] < nivel[v])
        swap(u, v);



    // vamos agora fazer nivel[u] ser
    // igual nivel[v], subindo pelos
    // ancestrais de u
    for(int i = MAXL-1; i >= 0; i--){
        if(nivel[u] - (1 << i) >= nivel[v]){
            u = ancestral[u][i];
        }
    }



    if(u == v)
        return u;

    // subimos o máximo possível de forma
    // que os dois NÃO passem a ser iguais

    for(int i = MAXL-1;i >= 0;i--)
        if(ancestral[u][i] != -1 && ancestral[u][i] != ancestral[v][i]){
            u = ancestral[u][i];
            v = ancestral[v][i];
        }

    // como subimos o máximo possível
    // sabemos que u != v e que pai[u] == pai[v]
    // logo, LCA(u, v) == pai[u] == pai[v]

    return ancestral[u][0];
}

int main(){

    int n;
    cin >> n;
    vector<int> pares[n];
    for(int i = 1; i <= n; i++){
        int ci;
        cin >> ci;
        pares[ci].push_back(i);
    }

    for(int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    build(n);
    int sum = 0;
    for(int i = 1; i <= n/2; i++){
        int a = pares[i][0];
        int b = pares[i][1];
        int lca = LCA(a, b);
        //cout << lca << "\n";
        sum += (nivel[a] + nivel[b] - 2*nivel[lca]);
        //cout << sum << "\n";
    }

    cout << sum << "\n";

    return 0;
}
