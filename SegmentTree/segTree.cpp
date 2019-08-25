/*
    min query
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 1e9 + 10;

int arr[MAXN];
int t[4*MAXN];

void build(int no, int l, int r){
    if(l == r){
        t[no] = arr[l];
    }else{
        int m = (l+r) / 2;
        build((no << 1), l, m);
        build((no << 1)+1, m+1, r);
        t[no] = min(t[(no << 1)], t[(no << 1)+1]);
    }
}

void update(int no, int l, int r, int p, int x){
    if(l == r){
        t[no] = x;
    }else{
        int m = (l+r)/2;
        if(p <= m) update((no << 1), l, m, p, x);
        else update((no << 1)+1, m+1, r, p, x);
        t[no] = min(t[no << 1], t[(no << 1) + 1]);
    }
}

int query(int no, int l, int r, int ql, int qr){
    if(ql <= l &&  r <= qr ) return t[no];
    if(ql > r || qr < l) return INF;
    else{
        int m = (l+r)/2;
        return min(query(no << 1, l, m, ql, qr),
                   query((no << 1) + 1, m+1, r, ql, qr));
    }
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    build(1, 0, n-1);

    int q;
    cin >> q;

    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            int id, x;
            cin >> id >> x;
            update(1, 0, n-1, id, x);
        }else{
            int ql, qr;
            cin >> ql >> qr;
            printf("query(%d, %d) = %d\n", ql, qr, query(1, 0, n-1, ql, qr));
        }
    }
    return 0;
}
