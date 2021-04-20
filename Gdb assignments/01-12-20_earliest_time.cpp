#include<bits/stdc++.h>
using namespace std;

void print_adj(float **G,int v){
    for(int i=0;i<v;i++)cout<<i<<"_";
    cout<<endl;
    for(int i=0;i<v;i++){
        cout<<i<<"|";
        for(int j=0;j<=v;j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }
}

void input(float **&G,int v,int e,int x[],int y[],float w[]){
    G = new float*[v];
    for(int i=0;i<v+1;i++)G[i]=new float[v];
    for(int i=0;i<v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=-1;
    for(int i=0;i<e;i++){
        G[x[i]][y[i]]=w[x[i]];
    }
}

void longe(float **G,int v,float dist,float &max,int cur,int g){
    if(cur==g){
        if(dist>max)max=dist;return;
    }
    for(int i=0;i<v;i++){
        if(G[cur][i]!=-1){
            longe(G,v,dist+G[cur][i],max,i,g);
        }
    }
}
void longe(float **G,int v){
    int s=0,g=8;
    float dist=0;
    float max=0;
    longe(G,v,dist,max,s,g);
    cout<<max;
}

int main()
{
    int v = 9,e=11;
    float **G;
    int x[]={0,0,1,1,2,3,3,5,4,7,6};
    int y[]={1,2,3,5,5,4,6,6,7,8,7};
    float w[]={0,3.1,2.0,4.6,1.8,0.3,4,3.7,0};
    input(G,v,e,x,y,w);
    // print_adj(G,v);
    longe(G,v);
}