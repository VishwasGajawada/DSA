#include<iostream>
using namespace std;

void input(int **&G,int v,int e,int x[],int y[]){
    G = new int*[v];
    for(int i=0;i<v;i++)G[i]=new int[v];
    for(int i=0;i<v;i++)
        for(int j=0;j<v;j++)
            G[i][j]=0;
    for(int i=0;i<e;i++){
        G[x[i]][y[i]]=1;
    }
}

int indegree(int **G,int v,int x)
{
    int ans=0;
    for(int i=0;i<v;i++){
        ans+=G[i][x];
    }
    return ans;
}

void topo_sort(int **G,int v){
    int cnt=1;
    int **C;//copy of G
    copy(C,G,v);
    int visit[v]={0};
    while(cnt!=v){
        int ind=0;
        for(int i=0;i<v;i++){
            if(indegree(C,v,i)==0 && visit[i]==0){
                ind=i;break;
            }
        }
        cout<<ind<<" ";cnt++;
        visit[ind]=1;
        for(int i=0;i<v;i++)C[ind][i]=0;
    }
}

int main()
{
    int N;cin>>N;
    string s[N];
    for(int i=0;i<N;i++)cin>>s[i];
    int v=26,e=0;
    int x[100]={0},y[100]={0};
    for(int i=0;i<N-1;i++){
        string s1 = s[i],s2=s[i+1];
        int min = s1.length()<s2.length()?s1.length():s2.length();
        for(int j=0;j<min;j++){
            if(s1[j]!=s2[j]){
                x[e] = s1[j]-'a';
                y[e++] = s2[j]-'a';
                break;
            }
        }
    }
    int **G;
    input(G,v,e,x,y);

}