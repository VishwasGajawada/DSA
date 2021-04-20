#include<iostream>
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

void time(btptr &t)
{
    static int curtime=0;
    if(t==null)return;
    t->at=curtime++;
    time(t->lc);
    time(t->rc);
    t->dt=curtime++;
}
btptr get_node(btptr t,int x)
{
    if(t==null) return null;
    if(t->data==x)return t;
    if(get_node(t->lc,x))return get_node(t->lc,x);
    else if(get_node(t->rc,x))return get_node(t->rc,x);
    return null;
}
int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    time(t);
    int a,b;
    cin>>a>>b;
    btptr a1=get_node(t,a);
    btptr b1=get_node(t,b);
    if((a1->at > b1->at && a1->dt < b1->dt )|| (a1->at < b1->at && a1->dt > b1->dt ))cout<<"same ";
    else cout<<"not same";
    return 0;
}
// 1 2 4 0 0 5 6 0 0 0 3 7 0 0 8 9 0 0 0
