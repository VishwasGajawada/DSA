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

void input(int **&G,int v,int e){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        int x,y,w;cin>>x>>y>>w;
        G[x][y]=w;
    }
}

int indegree(int **G,int v,int x)
{
    int ans=0;
    for(int i=1;i<=v;i++){
        ans+=G[i][x];
    }
    return ans;
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
        if(G[cur][i]==1 && visit[i]==0){
            dft(G,v,i,visit);
            break;
        }
    }
}
void dft(int **G,int v,int start=1)
{
    int visit[v+1]={0};
    // visit[start]=1;
    while(true){
        dft(G,v,start,visit);
        bool flag=0;
        int i;
        for(i=1;i<=v;i++){
            if(visit[i]==0){
                flag=1;
                start=i;
                break;
            }
        }
        if(flag==0)break;
    }
    
}

bool hasCycle(int **G,int v,int cur,int visit[]){
    visit[cur]=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]>0 && visit[i]==1)return true;
        if(G[cur][i]>0)return hasCycle(G,v,i,visit);
    }
    return false;
}
bool hasCycle(int **G,int v)
{
    int visit[v+1]={0};
    for(int i=1;i<=v;i++){
        for(int i=0;i<=v;i++)visit[i]=0;
        if(hasCycle(G,v,i,visit))return true;
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

void print_path(int s,int g,int prev[],int dist[]){
    int cur=g;
    stack<int>path;path.push(g);
    while(true){
        path.push(prev[cur]);
        cur = prev[cur];
        if(cur==s)break;
    }
    cout<<"path weight "<<dist[g]<<endl;
    while(!path.empty()){
        cout<<path.top()<<" ";
        path.pop();
    }
}

void dijkstra_path(int **G,int v,int s,int g)
{
    int visit[v+1]={0},dist[v+1],prev[v+1]={0};
    // for(int i=0;i<=v;i++)dist[i]=9999;
    for(int i=0;i<=v;i++)dist[i]=INT_MAX;
    visit[s]=1;
    dist[s]=0;prev[s]=s;
    int cur=s;
    while(true)
    {
        visit[cur]=1;
        for(int i=1;i<=v;i++){
            if(G[cur][i]>0 && visit[i]==0){
                if(dist[cur]+G[cur][i] < dist[i]){
                    dist[i] = dist[cur]+G[cur][i];
                    prev[i]=cur;
                }
            }
        }
        int min=INT_MAX;
        for(int i=1;i<=v;i++){
            if(visit[i]==0 && dist[i] < min){
                cur=i;
                min=dist[i];
            }
        }
        if(cur==g){
            print_path(s,g,prev,dist);
            break;
        }
    }
}

int main()
{
    int **G;
    int v,e;cin>>v>>e;
    input(G,v,e);
    dijkstra_path(G,v,1,6);
}
// 7 12 1 2 2 1 4 1 2 4 3 2 5 10 3 1 4 3 6 5 4 3 2 4 5 2 4 6 8 4 7 4 5 7 6 7 6 1

// 7 12
// 1 2 2 1 4 1 2 4 3 2 5 10 3 1 4 3 6 5 4 3 2 4 5 2 4 6 8 4 7 4 5 7 6 7 6 1

