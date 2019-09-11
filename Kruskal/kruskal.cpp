#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

struct Aresta{
    int u, v, custo;

    Aresta(int u, int v, int custo){
        this->u = u;
        this->v = v;
        this->custo = custo;
    }
};

int pai[MAXN];

int find(int u){
    if(pai[u] == u) return u;
    return pai[u] = find(pai[u]);
}

void join(int u, int v){
    pai[find(u)] = find(v);
}

vector<Aresta> kruskal(vector<Aresta>& arestas){

    sort(arestas.begin(), arestas.end(), [](Aresta a, Aresta b){
        return a.custo < b.custo;
    });

    vector<Aresta> arvoreGeradora;

    for(auto a: arestas){
        if(find(a.u) != find(a.v)){
            arvoreGeradora.push_back(a);
            join(a.u, a.v);
        }
    }

    return arvoreGeradora;
}

int main()
{
    int n, m, teste = 0;
    while(cin >> n >> m && n){
        if(teste) cout << "\n";
        vector<Aresta> arestas;
        for(int i = 1; i <= n; i++)
            pai[i] = i;
        while(m--){
            int u, v, custo;
            cin >> u >> v >> custo;
            Aresta a(u, v, custo);
            arestas.push_back(a);
        }

        printf("Teste %d\n", ++teste);
        vector<Aresta> arvoreGeradora = kruskal(arestas);
        for(Aresta a: arvoreGeradora){
            int u = min(a.u, a.v);
            int v = max(a.u, a.v);
            printf("%d %d\n", u, v);
        }
    }
    return 0;
}
