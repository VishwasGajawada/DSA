#include<bits/stdc++.h>
using namespace std;

void print_adj(int **G,int v){
    for(int i=0;i<=v;i++)cout<<i<<"_";
    cout<<endl;
    for(int i=1;i<=v;i++){
        cout<<i<<"|";
        for(int j=1;j<=v;j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }
}

void input(int **&G,int v,int e,int x[],int y[]){
    G = new int*[v];
    for(int i=0;i<v;i++)G[i]=new int[v];
    for(int i=0;i<v;i++)
        for(int j=0;j<v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        // int x,y;cin>>x>>y;
        G[x[i]][y[i]]=1;G[y[i]][x[i]]=1;
    }
}

int min(int a,int b){
    return a>b?b:a;
}
int min(int a,int b,int c){
    if(a<=b && a<=c)return a;
    if(b<=a && b<=c)return b;
    if(c<=a && c<=b)return c;
    return -1;
}
void cut(int**G,int v,int cur,int par,int num[],int low[]){
    static int t=0;
    num[cur]=low[cur]=t++; 
    int dfsc=0; //dfs children
    for(int i=0;i<v;i++){
        if(G[cur][i]==0)continue;
        if(num[i]==-1){//not visited :- tree edge
            cut(G,v,i,cur,num,low);
            low[cur] = min(num[cur],low[i],low[cur]);
            dfsc++;
        }else if(i!=par){//visited :- back edge
            low[cur] = min(num[cur],num[i],low[cur]);
        }
    }
    // cout<<num[cur]<<" "<<low[cur]<<endl;
    for(int i=0;i<v;i++){
        if(G[cur][i]>0){
            if(par==-1 && dfsc>1)cout<<cur<<" ";//root condition
            if(par!=-1 && num[cur]<=low[i]){//for cutvertex
            // if(num[cur]<low[i]){//for bridge
                cout<<cur<<" ";break;//for cut vertex
                // cout<<cur<<" "<<i<<endl;//for bridge
            }
        }
    }
}
void cut(int **G,int v){
    int num[v],low[v];
    for(int i=0;i<v;i++)num[i]=-1;
    cut(G,v,0,-1,num,low);
}
int main()
{
    int **G;
    int v=9,e=10;
    int x[]={0,0,1,2,2,3,5,6,7,8};
    int y[]={1,2,2,3,5,4,6,7,8,5};
    // // undirected
    input(G,v,e,x,y);
    cut(G,v);

}
// int v=5,e=5;
// int x[]={0,0,0,1,3};
// int y[]={1,2,3,2,4};