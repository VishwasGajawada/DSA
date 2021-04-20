// https://leetcode.com/problems/delete-node-in-a-bst/discuss/926566/most-easy-to-understand-code-or-or-c%2B%2B
#include<iostream>
#include<climits>
using namespace std;
#define null NULL
typedef struct bstnode * bstptr;
struct bstnode{
    int data;
    bstptr lc,rc;
};

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

void inorder(bstptr t)
{
    if(t!=null)
    {
        inorder(t->lc);
        cout<<t->data<<" ";
        inorder(t->rc);
    }
}

bstptr del(bstptr t,int x)
{
    if(!t)return null;
    if(x<t->data)t->lc=del(t->lc,x);
    else if(x>t->data)t->rc=del(t->rc,x);
    else{
        if(!t->lc){
            bstptr temp=t->rc;
            delete(t);
            return temp;
        }else if(!t->rc){
            bstptr temp=t->lc;
            delete(t);
            return temp;
        }else{
            bstptr lmax = t->lc;
            while(lmax->rc)lmax=lmax->rc;
            t->data=lmax->data;
            t->lc=del(t->lc,lmax->data);
        }
    }
    return t;
}

bstptr merge(bstptr t[],int n)
{
    bstptr merged=null;
    insert(merged,t[0]->data);
    del(t[0],t[0]->data);
    for(int i=0;i<n;i++)
    {
        while(t[i])
        {
            insert(merged,t[i]->data);
            t[i]=del(t[i],t[i]->data);
        }
    }
    return merged;
}

int main()
{
    int n;
    cin>>n;
    bstptr t[n]={null};
    for(int i=0;i<n;i++){
        int x;cin>>x;
        while(x!=-1)
        {
            insert(t[i],x);
            cin>>x;
        }
    }
    bstptr ans = merge(t,n);
    inorder(ans);
    return 0;
}
// 3
// 5 3 9 4 7 10 -1
// 6 1 2 11 8 -1
// 13 12 19 14  20 15 -1

