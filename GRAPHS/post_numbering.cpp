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
        G[x[i]][y[i]]=1;
    }
}

void dft(int **G,int v,int cur,int visit[],int &num,int number[]){
    visit[cur]=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]==1 && visit[i]==0){
            dft(G,v,i,visit,num,number);
        }
    }
    number[cur]=num++;
}
void dft(int **G,int v)
{
    int visit[v+1]={0};
    int number[v+1]={0};
    int num=1;
    int start[3]={2,8,7};int s=0;
    while(true){
        dft(G,v,start[s],visit,num,number);
        s++;
        if(s==3)break;
    }
    for(int i=1;i<=v;i++)cout<<i<<" "<<number[i]<<endl;
}

int main()
{
    int **G;
    int v=10,e=15;
    int x[]={1,1,2,2,3,3,3,4,6,7,7,8,8,9,10};
    int y[]={2,4,3,6,1,4,5,5,3,6,8,6,10,8,9};
    // // directed
    input(G,v,e,x,y);
    dft(G,v);
}



