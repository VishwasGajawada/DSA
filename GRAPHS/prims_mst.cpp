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

void min_span(int **G,int v){
    int visit[v+1]={0};
    int dist[v+1];int next[v+1]={0};
    for(int i=0;i<=v;i++)dist[i]=9999;
    int cur=1;
    visit[cur]=1;int ans=0,min;
    for(int j=0;j<6;j++){
        visit[cur]=1;int flag=0;
        for(int i=1;i<=v;i++){
            if(visit[i]==0)continue;
            dist[i]=9999;
            for(int j=1;j<=v;j++){
                if(G[i][j]>0 && visit[j]==0 && j!=i){
                    if(G[i][j]<dist[i]){
                        dist[i]=G[i][j];
                        next[i]=j;
                    }
                    flag=1;
                }
            }
            if(flag==0)dist[i]=-1;
        }
        min=9999;int temp=cur;
        for(int i=1;i<=v;i++){
            if(visit[i]==1 && dist[i]!=-1 && dist[i]<min){
                cur=i;min=dist[i];
            }
        }
        ans+=min;
        cout<<cur<<" "<<next[cur]<<endl;
        cur=next[cur];
    }
    cout<<ans;
}

int main()
{
    int **G;
    int v=7,e=12;
    int x[]={1,1,1,2,2,3,3,4,4,5,5,6};
    int y[]={2,3,4,4,5,4,6,6,7,4,7,7};
    int w[]={2,4,1,2,10,2,5,8,4,7,6,1};
    // // undirected
    input(G,v,e,x,y,w);
    min_span(G,v);
}


