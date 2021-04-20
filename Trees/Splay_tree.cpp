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

// void find_splay(bstptr &cur,int k,bstptr &p,bstptr &g)
void search_splay(bstptr &cur,int k)
{
    if(!cur)null;
    if(cur->data==k)return;
    if(k<cur->data){
        search_splay(cur->lc,k);
        right_rotate(cur);
    }else{
        search_splay(cur->rc,k);
        left_rotate(cur);
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
    bstptr t=null;
    int n;  
    cin>>n;
    while(n!=-1){
        insert(t,n);cin>>n;
    }
    level(t);
    search_splay(t,6);
    level(t);
}