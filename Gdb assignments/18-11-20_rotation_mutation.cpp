#include<bits/stdc++.h>
using namespace std;
#define null NULL
typedef struct bstnode * bstptr;
struct bstnode{
    int data;
    bstptr lc=null,rc=null;
};
void left_rotate(bstptr &bt)
{
    bstptr r = bt->rc;
    bt->rc = r->lc;
    r->lc = bt;
    bt=r;
}

void right_rotate(bstptr &bt)
{
    bstptr l=bt->lc;
    bt->lc=l->rc;
    l->rc=bt;
    bt = l;
}

void insert(bstptr &t,int k)
{
    if(t==null){
        t=new(bstnode);
        t->data=k;
        t->lc=t->rc=null;
        return;
    }
    if(k<t->data)insert(t->lc,k);
    else insert(t->rc,k);
}
void preorder(bstptr t)
{
    if(t!=null)
    {
        cout<<t->data<<" ";
        preorder(t->lc);
        preorder(t->rc);
    }
}

void func(bstptr &t1,int data){
    if(!t1)return;
    if(t1->data==data) return;
    if(data<t1->data){
        func(t1->lc,data);
        right_rotate(t1);
    }else if(data > t1->data){
        func(t1->rc,data);
        left_rotate(t1);
    }
}
void check(bstptr &t1,bstptr t2,int &flag)
{
    if(!t1 || !t2)return;
    if(flag==0 && t1->data !=t2->data){
        flag=1;
        func(t1,t2->data);
        return;
    }
    check(t1->lc,t2->lc,flag);
    check(t1->rc,t2->rc,flag);
}
int main()
{
    bstptr t1=null,t2=null;
    int n;  
    cin>>n;
    while(n!=-1){
        insert(t1,n);cin>>n;
    }
    cin>>n;
    while(n!=-1)
    {
        insert(t2,n);cin>>n;
    }
    int found=0;
    while(true){
        check(t1,t2,found);
        if(found==0)break;
        found=0;
    }
    preorder(t1);
}
// 6 4 2 1 3 5 8 7 9 -1 7 5 4 2 1 3 6 8 9 -1



