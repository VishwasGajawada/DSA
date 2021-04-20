#include<iostream>
using namespace std;

int min(int a,int b,int c)
{
    if(a<=b && a<=c)return a;
    if(b<=a && b<=c)return b;
    if(c<=a && c<=b)return c;
    return 0;
}

int dist(string s1,string s2)
{
    int m=s1.length(),n=s2.length();
    int d[m+1][n+1];
    // for(int i=0;i<=m;i++)d[i][0]=i;
    for(int i=0;i<m+1;i++){
        for(int j=0;j<n+1;j++)
        {
            if(i==0)d[i][j]=j;
            else if(j==0)d[i][j]=i;
            else if(s1[i-1]==s2[j-1])d[i][j]=d[i-1][j-1];
            else{
                d[i][j]=min(d[i-1][j-1],d[i][j-1],d[i-1][j])+1;
            }
        }
    }
    return d[m][n];
}
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    while(s1!="#"){
        cout<<dist(s1,s2)<<endl;
        cin>>s1>>s2;
    }
}