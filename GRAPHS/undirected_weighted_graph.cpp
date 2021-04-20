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

void bft(int **G,int v,int start=1){
    int visit[v+1]={0};
    queue<int> q;q.push(start);
    visit[start]=1;
    while(true){
        while(!q.empty()){
            int a=q.front();q.pop();
            for(int i=1;i<=v;i++){
                if(G[a][i]==1 && visit[i]==0){
                    cout<<a<<" "<<i<<endl;
                    q.push(i);visit[i]=1;
                }
            }
        }
        int flag=0;
        for(int i=1;i<=v;i++){
            if(visit[i]==0){
                q.push(i);flag=1;break;
            }
        }
        if(flag==0)break;
    }
}

void dft(int **G,int v,int cur,int visit[]){
    cout<<cur<<" ";visit[cur]=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]>0 && visit[i]==0){
            dft(G,v,i,visit);
            break;
        }
    }
}
void dft(int **G,int v,int start=1)
{
    int visit[v+1]={0};
    while(true){
        dft(G,v,start,visit);
        bool flag=0;
        for(int i=1;i<=v;i++){
            if(visit[i]==0){
                flag=1;
                start=i;
                break;
            }
        }
        if(flag==0)break;
    }
    
}

bool hasCycle(int **G,int v,int cur,int par,int visit[]){
    visit[cur]=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]>0 && visit[i]==1 && i!=par)return true;
        if(G[cur][i]>0 && i!=par)return hasCycle(G,v,i,cur,visit);
    }
    return false;
}
bool hasCycle(int **G,int v)
{
    int visit[v+1]={0};
    for(int i=1;i<=v;i++){
        for(int i=0;i<=v;i++)visit[i]=0;
        if(hasCycle(G,v,i,-1,visit))return true;
    }
    return false;
}

void copy(int **&G,int **O,int v){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=O[i][j];
}

void connected_for(int **G,int v,int visit[],int node)
{
    visit[node]=1;
    for(int i=1;i<=v;i++){
        if(G[node][i]>0 && visit[i]==0)connected_for(G,v,visit,i);
    }
}
void connected(int **G,int v)
{
    int visit[v+1];
    int flag=0;
    for(int i=1;i<=v;i++){
        for(int i=0;i<=v;i++)visit[i]=0;
        connected_for(G,v,visit,i);
        for(int i=1;i<=v;i++){
            if(visit[i]==0){
                flag=1;
                break;
            }
        }
        if(flag==1)break;
    }
    if(flag==1)cout<<"disconnected "<<endl;
    else cout<<"connected "<<endl;
}

void min_span(int **G,int v){
    int visit[v+1]={0};
    int dist[v+1];int next[v+1]={0};
    for(int i=0;i<=v;i++)dist[i]=9999;
    int cur=1;
    visit[cur]=1;int ans=0,min;
    for(int j=0;j<6;j++){
        visit[cur]=1;int flag=0;
        for(int z=1;z<=v;z++){
            if(visit[z]==0)continue;
            dist[z]=9999;
            for(int i=1;i<=v;i++){
                if(G[z][i]>0 && visit[i]==0 && i!=z){
                    if(G[z][i]<dist[z]){
                        dist[z]=G[z][i];
                        next[z]=i;
                    }
                    flag=1;
                }
            }
            if(flag==0)dist[z]=-1;
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


