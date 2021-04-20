#include<stdio.h>
#include<iostream>
using namespace std;
#define null NULL
typedef struct bstnode * bstptr;
struct bstnode{
    int data;
    bstptr lc,rc;
    int at,dt;
};

void insert(bstptr &t,int k)
{
    if(t==null){
        t=new(bstnode);
        t->data=k;
        t->lc=t->rc=null;
        t->at=t->dt=0;
        return;
    }
    if(k<t->data)insert(t->lc,k);
    else insert(t->rc,k);
}

void preorder(bstptr t)
{
    if(t!=null)
    {
        printf("( %d %d %d )",t->data,t->at,t->dt);
        preorder(t->lc);
        preorder(t->rc);
    }
}

int curtime=0;
void time(bstptr &t)
{
    if(t==null)return;
    t->at=curtime++;
    time(t->lc);
    time(t->rc);
    t->dt=curtime++;
}
int main()
{
    bstptr t=null;int n;
    cin>>n;
    while(n!=-1)
    {
        insert(t,n);
        cin>>n;
    }
    time(t);
    preorder(t);cout<<endl;
    return 0;
}
