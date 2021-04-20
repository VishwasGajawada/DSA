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

void rev(int **&G,int **O,int v)
{
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            G[i][j]=0;
        }
    }
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            if(O[i][j]>0){
                G[j][i]=O[i][j];
            }
        }
    }
}

void numb(int **G,int v,int cur,int visit[],int &num,int number[]){
    visit[cur]=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]==1 && visit[i]==0){
            numb(G,v,i,visit,num,number);
        }
    }
    number[cur]=num++;
}
void numb(int **G,int v,int number[])
{
    int visit[v+1]={0};
    int num=1;
    int start[3]={2,8,7};int s=0;
    while(true){
        numb(G,v,start[s],visit,num,number);
        s++;
        if(s==3)break;
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
void dft(int **G,int v,int number[])
{
    int visit[v+1]={0};
    int start;
    while(true){
        int max=0;
        bool flag=0;
        int i;
        for(i=1;i<=v;i++){
            if(visit[i]==0 && number[i]>max){
                flag=1;
                start=i;
                max=number[i];
            }
        }
        if(flag==0)break;
        dft(G,v,start,visit);cout<<endl;
    }
}

void strong_comps(int **O,int v){
    int number[v+1]={0};
    numb(O,v,number);
    int **G;
    rev(G,O,v);
    dft(G,v,number);
}

int main()
{
    int **G;
    int v=10,e=15;
    int x[]={1,1,2,2,3,3,3,4,6,7,7,8,8,9,10};
    int y[]={2,4,3,6,1,4,5,5,3,6,8,6,10,8,9};
    // // directed
    input(G,v,e,x,y);
    strong_comps(G,v);
}



