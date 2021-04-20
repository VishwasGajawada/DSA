#include<iostream>
#include<climits>
using namespace std;
#define null NULL
typedef struct bstnode * bstptr;
typedef struct dlnode * dlptr;

struct dlnode{
    int data;
    dlptr right;
    dlptr left;
};
dlptr getDtail(dlptr d){
    while(d->right!=null)d=d->right;
    return d;
}
void prinddl(dlptr d){
    while(d!=null){
        cout<<d->data<<" ";
        d=d->right;
    }
    cout<<endl;
}
void addend(dlptr &D,int x){
    dlptr temp=null,iter=null;
    temp = new(dlnode);
    temp->data=x;
    temp->right=null;
    temp->left=null;
    if(D==null){
        D=temp;
        return;
    }
    iter = getDtail(D);
    iter->right = temp;
    temp->left = iter;
}

struct bstnode{
    int data;
    bstptr lchild,rchild;
};
void insert(bstptr &t,int k)
{
    if(t==null){
        t=new(bstnode);
        t->data=k;
        t->lchild=t->rchild=null;
        return;
    }
    if(k<t->data)insert(t->lchild,k);
    else insert(t->rchild,k);
}
void printPairs(dlptr d,int x,dlptr cur){
    dlptr l = d;
    dlptr h = getDtail(d);
    while(l!=h->right){
        if(l->data+h->data==x){
            if(l==cur || h==cur){
                l=l->right;
            }else{
                if(cur->data < l->data && l->data<h->data)
                    cout<<cur->data<<" "<<l->data<<" "<<h->data<<endl;
                l=l->right;
            }
        }else if(l->data+h->data>x){
            h=h->left;
        }else if(l->data+h->data<x)l=l->right;
    }
}
void findTriplets(dlptr d,int s){
    dlptr cur  = d;
    while(cur->right!=null){
        printPairs(d,s-(cur->data),cur);
        cur=cur->right;
    }
}
void dll(bstptr t,dlptr &d)
{
    if(t==null)return;
    dll(t->lchild,d);
    addend(d,t->data);
    dll(t->rchild,d);
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
    int s;
    cin>>s;
    dlptr d=null;
    dll(t,d);
    findTriplets(d,s);
    return 0;
}

// 5 3 9 1 4 7 10 6 2 -1
// 13
