#include<bits/stdc++.h>
using namespace std;

void input(int **&G,int v,int e,int x[],int y[]){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        // int x,y;cin>>x>>y;
        G[x[i]][y[i]]=1;G[y[i]][x[i]]=1;
    }
}
int sum(int a[],int v){
    int ans=0;
    for(int i=0;i<=v;i++)ans+=a[i];
    return ans;
}
void print(int p[],int v){
    for(int i=0;i<=v;i++)cout<<p[i]<<" ";
    cout<<endl;
}
bool hamil(int **G,int v,int visit[],int path[],int cur,int &once,int ind=1){
    if(once==1 && cur==path[0]){
        if(sum(visit,v)==v){
            path[v]=path[0];
            print(path,v);return true;
        }
        return false;
    }
    once=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]>0 && visit[i]==0){
            path[ind]=i;visit[i]=1;
            if(hamil(G,v,visit,path,i,once,ind+1))return true;
            path[ind]=0;visit[i]=0;
        }
    }
    return false;
}
int main()
{
    int **G;
    int v=20,e=30;
    int x[]={1,1,1,2,02,3,03,4,04,5,6,06,7,07,8, 9, 9,10,11,11,12,13,13,14,15,16,17,18,19,20};
    int y[]={2,8,5,3,10,4,12,5,14,6,7,15,8,17,9,10,18,11,12,19,13,14,20,15,16,17,18,19,20,16};
    input(G,v,e,x,y);
    int path[v+1]={0};
    path[0]=1;
    int visit[v+1]={0};
    int once=0;
    hamil(G,v,visit,path,1,once);
}

// int v=4,e=6;
// int x[]={1,1,1,2,2,3};
// int y[]={2,3,4,3,4,4};