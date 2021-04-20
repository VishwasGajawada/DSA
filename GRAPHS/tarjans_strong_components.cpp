#include<bits/stdc++.h>
using namespace std;

void input(int **&G,int v,int e,int x[],int y[]){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        G[x[i]][y[i]]=1;
    }
}
int min(int a,int b){
    return (a<b)?a:b;
}
void strong_cc(int **G,int v,int cur,int num[],int low[],bool printed[],stack<int> &s){
    static int t=1;
    num[cur]=low[cur]=t++;
    printed[cur]=false;
    s.push(cur);
    for(int i=1;i<=v;i++){
        if(G[cur][i]==0)continue;
        if(num[i]==-1){
            strong_cc(G,v,i,num,low,printed,s);
            low[cur]=min(low[cur],low[i]);
        }else if(printed[i]==false){
            low[cur]=min(low[cur],num[i]);
        }
    }
    if(low[cur]==num[cur]){
        while(!s.empty()){
            int temp = s.top();s.pop();
            cout<<temp<<" ";
            printed[temp]=true;
            if(temp==cur)break;
        }
        cout<<endl;
    }

}
void strong_cc(int **G,int v){
    int num[v+1],low[v+1];
    bool printed[v+1];
    for(int i=0;i<=v;i++){num[i]=-1,printed[i]=true;}
    for(int i=1;i<=v;i++){
        if(num[i]==-1){
            stack<int> s;
            strong_cc(G,v,i,num,low,printed,s);
        }
    }
}

int main()
{
    int **G;
    int v=10,e=15;
    int x[]={1,1,2,2,3,3,3,4,6,7,7,8,8,9,10};
    int y[]={2,4,3,6,1,4,5,5,3,6,8,6,10,8,9};
    // // directed
    input(G,v,e,x,y);
    strong_cc(G,v);
}