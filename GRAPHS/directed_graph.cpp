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
        int x,y;cin>>x>>y;
        G[x][y]=1;
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
                    cout<<a<<"->"<<i<<endl;
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

void correspond_undir(int **&G,int **O,int v)
{
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            G[i][j]=0;
            if(G[i][j]>0)G[j][i]=G[i][j];
        }
    }
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            if(O[i][j]>0){
                G[j][i]=O[i][j];
                G[i][j]=O[i][j];
            }
        }
    }
    // print_adj(G,v);        
}

void connected_for(int **G,int v,int visit[],int node)
{
    visit[node]=1;
    for(int i=1;i<=v;i++){
        if(G[node][i]>0 && visit[i]==0)connected_for(G,v,visit,i);
    }
}
int undirected_connected(int **G,int v)
{
    int visit[v+1];
    int flag=0;
    for(int i=1;i<=v;i++){
        for(int i=0;i<=v;i++)visit[i]=0;
        connected_for(G,v,visit,i);
        for(int i=1;i<=v;i++){
            if(visit[i]==0){
                flag=1;//not visiting some vertex
                break;
            }
        }
        if(flag==1)break;
    }
    // if(flag==1)cout<<"disconnected "<<endl;
    // else cout<<"connected "<<endl;
    return flag;
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
                flag=1;break;
            }
        }
        if(flag==1)break;
    }
    if(flag==1){
        int **c;
        correspond_undir(c,G,v);
        if(undirected_connected(c,v)==0){
            cout<<"weakly connected"<<endl;
        }else{
            cout<<"neither "<<endl;
        }
    }else{
        cout<<"strongly connected "<<endl;
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
        for(int j=0;j<=v;j++)visit[j]=0;
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

//toplogical sort
void topo_sort(int **G,int v){
    int cnt=1;
    int **C;//copy of G
    copy(C,G,v);
    int visit[v+1]={0};
    while(cnt!=v){
        int ind=0;
        for(int i=1;i<=v;i++){
            if(indegree(C,v,i)==0 && visit[i]==0){
                ind=i;break;
            }
        }
        cout<<ind<<" ";cnt++;
        visit[ind]=1;
        for(int i=1;i<=v;i++)C[ind][i]=0;
    }
}

int main()
{
    int **G;
    int v,e;cin>>v>>e;

    // // directed
    input(G,v,e);
    // topo_sort(G,v);
    // connected(G,v);
    // cout<<hasCycle(G,v);
}
//DAG
// 7 7 1 2 1 3 2 5 3 5 4 6 6 3 5 7 
// directed cyclic
// 5 7 1 2 1 4 2 3 2 5 3 1 3 4 4 5
//directed acyclic
// 5 7 1 2 1 3 1 4 2 3 2 5 3 4 4 5
//disconnected ,cyclic,directed
// 7 8 1 2 1 4 2 3 2 5 3 1 3 4 4 5 6 7
