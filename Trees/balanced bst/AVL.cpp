#include<bits/stdc++.h>
using namespace std;
#define null NULL
typedef struct bstnode * bstptr;
struct bstnode{
    int data;
    bstptr lc=null,rc=null;
};
void left_rotate(bstptr bt,bstptr &root)
{
    bstptr r = bt->rc;
    bt->rc = r->lc;
    r->lc = bt;
    root=r;
}

void right_rotate(bstptr bt,bstptr &root)
{
    bstptr l=bt->lc;
    bt->lc=l->rc;
    l->rc=bt;
    root = l;
}

int height(bstptr bt)
{
    if(!bt)return 0;
    return (height(bt->lc) > height(bt->rc))?height(bt->lc)+1:height(bt->rc)+1;
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
    int lh = height(t->lc),rh = height(t->rc);
    if( lh-rh >= 2 ){
        if(t->lc && k<t->lc->data)return right_rotate(t,t);
        if(t->lc && k>t->lc->data){
            left_rotate(t->lc,t->lc);
            right_rotate(t,t);
        }
    }else if ( rh-lh >=2)
    {
        if(t->rc && k>t->rc->data)return left_rotate(t,t);
        if(t->rc && k<t->rc->data){
            right_rotate(t->rc,t->rc);
            left_rotate(t,t);
        }
    }
}

void insert2(bstptr &t,int k ,bstptr &k3,bstptr &k1,bstptr &k2)
{
    if(t==null){
        t=new(bstnode);
        t->data=k;
        t->lc=t->rc=null;
        // return;
    }
    if(k<t->data)insert2(t->lc,k,k3,k1,k2);
    else if(k>t->data) insert2(t->rc,k,k3,k1,k2);
    k3=t;
    int lh = height(t->lc),rh = height(t->rc);
    if(k1 && k2 && k3)
    {
        if(rh-lh>=2){
            if(k3->rc==k1 && k1->rc==k2)left_rotate(t,t);
            else if(k3->rc==k1 && k1->lc==k2){
                right_rotate(t->rc,t->rc);
                left_rotate(t,t);
            }
        }
        if(lh-rh>=2){
            if(k3->lc == k1 && k1->lc==k2) right_rotate(t,t);
            else if(k3->lc == k1 && k1->rc==k2){
                left_rotate(t->lc,t->lc);
                right_rotate(t,t);
            }
        }
    }
    k2=k1;
    k1=k3;
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

void level(bstptr t)
{
    queue<bstptr>q;
    bstptr end = new bstnode;
    end->data==-1;
    q.push(t);q.push(end);
    while(true)
    {
        bstptr temp=q.front();q.pop();
        if(temp->data==end->data){
            cout<<endl;
            if(q.empty())break;
            q.push(end);
        }else{
            cout<<temp->data<<" ";
            if(temp->lc)q.push(temp->lc);
            if(temp->rc)q.push(temp->rc);
        }
    }
}

int main()
{
    bstptr t=null;int n;
    cin>>n;
    while(n!=-1)
    {
        // bstptr k1=null,k2=null,k3=null;
        insert(t,n);
        // insert2(t,n,k3,k1,k2);//using parent and grandparent
        level(t);
        cin>>n;
    }
    preorder(t);
    return 0;
}
