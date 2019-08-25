#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e5+10;
ll tree[4*MAXN], lz[4*MAXN];

void push(int i, int l, int r){

    if(!lz[i]) return;

    tree[i] += (r-l+1) * lz[i];

    if(l != r){
        lz[2*i] += lz[i];
        lz[2*i+1] += lz[i];
    }
    lz[i] = 0;
}

ll query(int i, int l, int r, int ql, int qr){
    push(i, l, r);
    if(r < ql || l > qr) return 0;
    if(ql <= l && r <= qr) return tree[i];
    int m = (l+r)/2;
    return query(2*i, l, m, ql, qr) + query(2*i+1, m+1, r, ql, qr);
}

void update(int i, int l, int r, int ql, int qr, ll v){
    push(i, l, r);
    if(r < ql || l > qr) return;
    if(ql <= l && r <= qr){
        lz[i] += v;
        push(i, l, r);
        return;
    }
    int m = (l+r)/2;
    update(2*i, l, m, ql, qr, v);
    update(2*i+1, m+1, r, ql, qr, v);
    tree[i] = tree[2*i] + tree[2*i+1];
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        int n, c;
        cin >> n >> c;
        memset(tree, 0, sizeof tree);
        memset(lz, 0, sizeof lz);
        while(c--){
            int op, p, q, v;
            scanf("%d %d %d", &op, &p, &q);
            if(op == 1){
                cout << query(1, 1, n, p, q) << "\n";
            }else{
                scanf("%d", &v);
                update(1, 1, n, p, q, v);
            }

        }
    }
    return 0;
}
