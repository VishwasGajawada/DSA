#include<iostream>
using namespace std;
typedef struct btnode * btptr;
#define null NULL

struct btnode{
    btptr lc,rc;
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
    cin>>x;
    if(x!=0)insert(t->lc,x);
    cin>>x;
    if(x!=0)insert(t->rc,x);
}
void mid(btptr t,btptr t1){
    if(!t || !t1)return;
    if(!t1->lc && !t1->rc){
        cout<<t->data<<" ";
        return;
    }
    t1=t1->lc;
    if(t1->lc)t1=t1->lc;
    mid(t->lc,t1);
    mid(t->rc,t1);
}
int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    mid(t,t);
    return 0;
}

// 1 2 4 8 16 0 0 17 0 0 9 18 0 0 19 0 0 5 10 20 0 0 21 0 0 11 22 0 0 23 0 0 3 6 12 
// 24 0 0 25 0 0 13 26 0 0 27 0 0 7 14 28 0 0 29 0 0 15 30 0 0 31 0 0
