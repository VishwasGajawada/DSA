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
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        // int x,y;cin>>x>>y;
        G[x[i]][y[i]]=1;
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

void copy(int **&G,int **O,int v){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=O[i][j];
}

//toplogical sort
int min_steps(int **G,int v){
     int cnt=0,time=0;
    int **C;//copy of G
    copy(C,G,v);
    int visit[v+1]={0};
    while(cnt!=v){time++;
        int ind=0;
        queue<int> temp;
        for(int i=1;i<=v;i++)
            if(indegree(C,v,i)==0 && visit[i]==0)temp.push(i);
        while(!temp.empty()){
            ind = temp.front();temp.pop();cnt++;
            visit[ind]=1;
            for(int i=1;i<=v;i++)C[ind][i]=0;
        }
    }
    // cout<<time<<endl;
    return time;
}

void print(queue<int>q,char out[]){
    while(!q.empty()){
        cout<<out[q.front()]<<" ";q.pop();
    }cout<<endl;
}

void func(int **G,int v,char out[],int visit[],queue<int>q,int curt,int t){
    queue<int> temp;
    for(int i=1;i<=v;i++){
        if(indegree(G,v,i)==0 && visit[i]==0){
            temp.push(i);
        }
    }int ind;
    if(temp.size()==0){
        if(curt==t)print(q,out);
        return;
    }else if(temp.size()==1){
        ind = temp.front();temp.pop();
        q.push(ind);
        visit[ind]=1;
        for(int i=1;i<=v;i++)G[ind][i]=0;
        func(G,v,out,visit,q,curt+1,t);
    }else if(temp.size()==2){
        int a=temp.front();temp.pop();
        int b=temp.front();temp.pop();
        q.push(a);
        visit[a]=1;
        for(int i=1;i<=v;i++)G[a][i]=0;
        func(G,v,out,visit,q,curt+1,t);q.pop();
        q.push(b);
        visit[b]=1;
        for(int i=1;i<=v;i++)G[b][i]=0;
        func(G,v,out,visit,q,curt+1,t);q.pop();
        q.push(a);q.push(b);
        visit[a]=1;visit[b]=1;
        for(int i=1;i<=v;i++){G[a][i]=0;G[b][i]=0;}
        func(G,v,out,visit,q,curt+1,t);
    }
}

void topo_sort(int **G,int v){
    int cnt=0;
    int **C;//copy of G
    copy(C,G,v);
    char out[v+1]={'.','A','B','C','D','E','F','H','I'};
    int visit[v+1]={0};
    while(cnt!=v){
        int ind=0;
        queue<int> temp;
        for(int i=1;i<=v;i++){
            if(indegree(C,v,i)==0 && visit[i]==0){
                temp.push(i);
            }
        }
        while(!temp.empty()){
            ind = temp.front();temp.pop();
            cout<<out[ind]<<" ";cnt++;
            visit[ind]=1;
            for(int i=1;i<=v;i++)C[ind][i]=0;
        }cout<<endl;
    }
}

int main()
{
    int **G;
    int v=8,e=7;
    int x[]={1,2,3,4,6,7,8};
    int y[]={2,3,4,5,7,8,3};
    input(G,v,e,x,y);
    // topo_sort(G,v);
    char out[v+1]={'.','A','B','C','D','E','F','H','I'};
    int t= min_steps(G,v);
    int visit[v+1]={0};
    queue<int>q;
    func(G,v,out,visit,q,0,t);

}
//DAG
// 7 7 1 2 1 3 2 5 3 5 4 6 6 3 5 7 
// directed cyclic
// 5 7 1 2 1 4 2 3 2 5 3 1 3 4 4 5
//directed acyclic
// 5 7 1 2 1 3 1 4 2 3 2 5 3 4 4 5
//disconnected ,cyclic,directed
// 7 8 1 2 1 4 2 3 2 5 3 1 3 4 4 5 6 7
