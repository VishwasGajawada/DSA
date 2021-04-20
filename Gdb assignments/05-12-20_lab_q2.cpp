#include<bits/stdc++.h>
using namespace std;

struct edge{
    int v1,v2,weight;
};
void swap(struct edge &a,struct edge &b){
    struct edge temp = a;
    a=b;b=temp;
}
struct maxheap{
    struct edge e[100];
    int s=0;
    void insert(int x,int y,int z){
        e[s].v1=x,e[s].v2=y,e[s].weight=z;
        int k=s;
        while(e[k].weight>e[(k-1)/2].weight){
            swap(e[k],e[(k-1)/2]);
            k = (k-1)/2;
        }
        s++;
    }
    struct edge pop()
    {
        struct edge ans=e[0];
        e[0] = e[--s];
        int i=0;
        int l=2*i+1,r=2*i+2;
        while((l<=s)||(r<=s)){
            int large=i;
            if(l<=s && e[large].weight<e[l].weight)large=l;
            if(r<=s && e[large].weight<e[r].weight)large=r;
            if(large!=i)swap(e[large],e[i]);
            if(large==i)break;
            i=large;
            l=2*i+1,r=2*i+2;
        }
        return ans;
    }
};

void input(int **&G,int v,int e,int x[],int y[],int w[],struct maxheap &m){
    G = new int*[v+1];
    for(int i=0;i<v+1;i++)G[i]=new int[v+1];
    for(int i=0;i<=v;i++)
        for(int j=0;j<=v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        G[x[i]][y[i]]=w[i];G[y[i]][x[i]]=w[i];
        m.insert(x[i],y[i],w[i]);
    }
}

void connected_for(int **G,int v,int visit[],int node)
{
    visit[node]=1;
    for(int i=1;i<=v;i++){
        if(G[node][i]>0 && visit[i]==0)connected_for(G,v,visit,i);
    }
}
bool connected(int **G,int v)
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
    if(flag==1)return false;//cout<<"disconnected "<<endl;
    else return true;//cout<<"connected "<<endl;
}

int sum(int a[],int n){
    int s=0;
    for(int i=1;i<=n;i++)s+=a[i];
    return s;
}
void mst(int **G,int v,struct maxheap m){
    int visit[v+1]={0};
    int s[v+1];for(int i=0;i<=v;i++)s[i]=-1;
    int ans=0;
    while(m.s>0){
        struct edge temp = m.pop();
        int x=temp.v1,y=temp.v2,z=temp.weight;
        int w=G[x][y];
        G[x][y]=G[y][x]=0;
        if(!connected(G,v))G[x][y]=G[y][x]=w;
        else cout<<x<<" "<<y<<endl;
    }
    cout<<ans;
}

int main()
{
    int **G;
    int v=7,e=12;
    int x[]={1,1,1,2,2,3,3,4,4,4,5,6};
    int y[]={2,3,4,4,5,4,6,6,7,5,7,7};
    int w[]={2,4,1,3,10,2,5,8,4,7,6,1};
    struct maxheap m;
    input(G,v,e,x,y,w,m);
    mst(G,v,m);
    
}
