#include<bits/stdc++.h>
using namespace std;

void input(int **&G,int v,int e,int x[],int y[],int w[]){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        G[x[i]][y[i]]=w[i];G[y[i]][x[i]]=w[i];
    }
}
int find(int s[],int v,int x){
    if(s[x]==-1)return x;
    else return find(s,v,s[x]);
}
void uni(int s[],int v,int x,int y){
    if(s[y]==-1)s[y]=x;
    else if(s[x]==-1)s[x]=y;
    else s[find(s,v,y)]=find(s,v,x);
}
int num_trees(int s[],int v){
    int x=0;
    for(int i=1;i<=v;i++)if(s[i]==-1)x++;
    return x;
}
void sollins(int **G,int v){
    int s[v+1];for(int i=0;i<=v;i++)s[i]=-1;
    int weight=0;
    while(num_trees(s,v)!=1){
        int x[v+1]={0},y[v+1]={0}; //edges selected
        for(int i=1;i<=v;i++){
            int rt1 = find(s,v,i); //root of i
            for(int j=1;j<=v;j++){
                if(G[i][j]==0)continue;
                int rt2=find(s,v,j);//root of j
                if(rt1==rt2)continue;
                if(x[rt1] == 0 || G[x[rt1]][y[rt1]] > G[i][j]){
                    x[rt1]=i;
                    y[rt1]=j;
                }
            }
        }
        for(int i=1;i<=v;i++){
            if(y[i]==0)continue;
            int rt1 = find(s,v,x[i]),rt2 = find(s,v,y[i]);
            if(rt1==rt2)continue;
            uni(s,v,x[i],y[i]);
            cout<<x[i]<<" "<<y[i]<<endl;
            weight+=G[x[i]][y[i]];
        }
    }
    cout<<"weight "<<weight<<endl;

}
int main()
{
    int **G;
    int v=7,e=9;
    int x[]={ 1, 1, 2, 2, 3, 4, 4, 5, 5};
    int y[]={ 2, 6, 3, 7, 4, 5, 7, 6, 7};
    int w[]={28,10,16,14,12,22,18,25,24};
    // // undirected
    input(G,v,e,x,y,w);
    sollins(G,v);
}