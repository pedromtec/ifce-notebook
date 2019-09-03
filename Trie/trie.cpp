#include <bits/stdc++.h>

using namespace std;
/*
    Trie para strings que possum simbolos 0-9
    Lembre-se de mudar o vetor children e as operações
    de conversão de caractere 
*/
struct Trie{

    struct Node{
        Node* children[10];
        bool isEnd;
        Node(){
            isEnd = false;
            for(int i = 0; i < 10; i++)
                children[i] = NULL;
        }
    };

    Node* root;

    Trie(){
        root = new Node();
    }

    void insert(string &s){
        Node* curr = root;
        for(char c: s){
            int simb = c-48;
            if(!curr->children[simb]){
                curr->children[simb] = new Node();
            }
            curr = curr->children[simb];
        }

        curr->isEnd = true;

    }
    //Verifica se s é prefixo de alguma string que esteja na Trie
    bool search(string &s){
        Node* curr = root;
        for(char c: s){
            int simb = c-48;
            if(!curr->children[simb])
                return false;
            curr = curr->children[simb];
        }
        return true;
    }
};

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        Trie *trie = new Trie();
        vector<string> list(n);
        for(string &s: list)
            cin >> s;
        sort(list.begin(), list.end(), [](string &a, string &b){
            return a.size() > b.size();
        });
        bool consistent = true;
        for(string &s: list){
            if(trie->search(s)){
                consistent = false;
                break;
            }
            trie->insert(s);
        }

        if(consistent) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
