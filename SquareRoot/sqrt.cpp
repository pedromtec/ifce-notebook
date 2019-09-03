#include <bits/stdc++.h>

using namespace std;

const int MAXN =   1e5 + 10;
const int MAXR =  400;

int n, q, len;

int b[MAXR][MAXN], a[MAXN];

void update(int id, int v){
    int bloco = id / len;
    b[bloco][a[id]]--;
    a[id] = v;
    b[bloco][a[id]]++;
}
/*
query: Quantos valores iguais a w existem no intervalo l-r
*/
int query(int l, int r, int w){
    int sum = 0;
    int b_l = l / len;
    int b_r = r / len;
    if(b_r == b_l){
        for(int i = l; i <= r; i++)
            if(a[i] == w) sum++;
    }else{
        for(int i = l, fim = (b_l+1) * len - 1; i <= fim; i++)
            if(a[i] == w) sum++;
        for(int i = b_l+1; i < b_r; i++)
            sum += b[i][w];
        for(int i = b_r * len; i <= r; i++)
            if(a[i] == w) sum++;
    }
    return sum;
}



int main()
{

    scanf("%d %d", &n, &q);
    len = sqrt(n) + 1;

    for(int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
        ++b[i/len][a[i]];
    }
    while(q--){
        int op, x, y, w;;
        scanf("%d", &op);
        if(op == 1){
            scanf("%d %d", &x, &w);
            update(x-1, w);
        }else{
            scanf("%d %d %d", &x, &y, &w);
            printf("%d\n", (y-x+1) - query(x-1, y-1, w));
        }
    }
    return 0;
}
