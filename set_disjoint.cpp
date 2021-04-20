#include<iostream>
using namespace std;

int find(int s[],int v,int x){
    if(s[x]==-1)return x;
    return find(s,v,s[x]);
}
void uni(int s[],int v,int x,int y){
    if(s[y]==-1)s[y]=x;
    else if(s[x]==-1)s[x]=y;
    else s[find(s,v,y)]=find(s,v,x);
}

int main()
{
    int n;
    cin>>n;
    int s[n+1];for(int i=0;i<=n;i++)s[i]=-1;

}