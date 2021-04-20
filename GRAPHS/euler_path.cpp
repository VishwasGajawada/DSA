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
        G[x[i]][y[i]]=1;G[y[i]][x[i]]=1;
    }
}

int deg(int **G,int v,int cur){
    int ans=0;
    for(int i=1;i<=v;i++)ans+=G[cur][i];
    return ans;
}

//dft method
void euler(int **&G,int v,int cur,int start,queue<int> &q,int &init){
    // cout<<cur<<" ";
    q.push(cur);
    if(init!=0 && cur==start)return;
    init=1;
    for(int i=1;i<=v;i++){
        if(G[cur][i]==1){
            G[cur][i]=0;G[i][cur]=0;
            euler(G,v,i,start,q,init);
            break;
        }
    }
}

//dft method
void euler(int **G,int v,int start=1)
{
    queue<int> path,temp;
    path.push(start);
    while(true){
        int flag=0;
        while(!path.empty()){
            int x=path.front();path.pop();
            if(deg(G,v,x)!=0){
                flag=1;
                int init=0;
                euler(G,v,x,x,temp,init);break;
            }
            temp.push(x);
        }
        while(!path.empty()){temp.push(path.front());path.pop();}
        while(!temp.empty()){path.push(temp.front());temp.pop();}
        if(flag==0)break;
    }
    while(!path.empty()){cout<<path.front()<<" ";path.pop();}
}

int main()
{
    int **G;
    int v=12,e=21;
    int x[]={1,1,2,2,3,3,3,3,4,4,04,04,05,6,7,07,8,9,9,10,10};
    int y[]={3,4,3,8,4,6,7,9,5,7,10,11,10,9,9,10,9,10,12,11,12};
    input(G,v,e,x,y);
    euler(G,v);
    // print_adj(G,v);
}


