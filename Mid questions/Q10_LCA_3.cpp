#include<bits/stdc++.h>
using namespace std;
typedef struct btnode * btptr;
#define null NULL

struct btnode{
    btptr lc,rc;
    int at=0,dt=0;
    int data;
};
void insert(btptr &t,int k)
{
    if(t==null){
        t=new(btnode);
        t->data=k;
        t->rc=t->lc=null;
    }
    int x;
    // cout<<"enter lc of "<<k<<endl;
    cin>>x;
    if(x!=0)insert(t->lc,x);
    // cout<<"enter rc of "<<k<<endl;
    cin>>x;
    if(x!=0)insert(t->rc,x);
}

bool path(stack<int> &s,btptr t,int x)
{
    if(t==null)return false;
    if(t->data==x)
    {
        s.push(t->data);
        return true;
    }
    if(path(s,t->lc,x) || path(s,t->rc,x))
    {
        s.push(t->data);
        return true;
    }
    return false;
}
void lca(btptr t,int a,int b,int c)
{
    stack<int> s1,s2,s3;
    path(s1,t,a);
    path(s2,t,b);
    path(s3,t,c);

    while(s1.top()==s2.top() && s2.top()==s3.top())
    {
        int t1=s1.top(),t2=s2.top(),t3=s3.top();
        s1.pop();
        s2.pop();
        s3.pop();
        if(s1.top()!=s2.top() || s2.top()!=s3.top()|| s3.top()!=s1.top()){
            cout<<t1<<endl;
            break;
        }
        // cout<<t1<<" ";
    }
    
}
int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    int a,b,c;
    cin>>a>>b>>c;
    lca(t,a,b,c);
    
}
// 1 2 4 0 0 5 6 0 0 0 3 7 0 0 8 9 0 0 0
