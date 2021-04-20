#include<bits/stdc++.h>
using namespace std;
#define null NULL
typedef struct bknode * bkptr;
struct bknode{
    int max_chil=10;
    string s="";
    bkptr cptr[10]={null};
};

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

void insert(bkptr &t,string s)
{
    if(!t){
        t=new bknode;
        t->s=s;
        return;
    }
    insert(t->cptr[dist(t->s,s)],s);
}

void print(bkptr t){
    if(!t)return;
    cout<<t->s<<" ";
    for(int i=0;i<t->max_chil;i++)print(t->cptr[i]);
}

// void similar(bkptr t,string k,queue<bkptr>&final,queue<bkptr>&temp,int N=2){
//     if(!t)return;
//     bkptr cur = temp.front();temp.pop();
//     int d = dist(cur->s,k);
//     for(int i=0;i<cur->max_chil;i++){
//         if(!cur->cptr[i])continue;
//         int cd = dist(cur->cptr[i]->s,k);
//         if(d-N <= cd && cd <= d+N){
//             final.push(cur->cptr[i]);temp.push(cur->cptr[i]);
//             similar(cur->cptr[i],k,final,temp,N);
//         }
//     }
// }

void similar(bkptr t,string k,queue<bkptr>&final,int N=2){
    if(!t)return;
    if(dist(t->s,k)<=N) final.push(t);
    int i = dist(t->s,k)-N;
    if(i<=0)i=1;
    for(i;i<=dist(t->s,k)+N;i++){
        similar(t->cptr[i],k,final,2);
    }
}

int main()
{
    bkptr t=null;
    string s="";cin>>s;
    while(s!="#"){
        insert(t,s);cin>>s;
    }
    int N;cin>>s>>N;
    queue<bkptr> final,temp;
    // final.push(t);temp.push(t); //comment for correct code 
    similar(t,s,final,N);
    while(!final.empty()){
        cout<<dist(final.front()->s,s)<<" "<<final.front()->s<<" ";
        final.pop();
    }
    return 0;
}
// some soft same mole soda salmon cse nitw sport  # sort 2
// hell help shel smell fell felt oops pop oouch halt # ops 2
