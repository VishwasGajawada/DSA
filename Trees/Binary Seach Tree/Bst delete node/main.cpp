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

int* minmaxiter(bstptr t)
{
    static int a[2]={0,0};
    if(t==null){
        a[0]=a[1]=0;
        return a;
    }
    bstptr temp = t;
    while(t->lc!=null)t=t->lc;
    while(temp->rc!=null)temp=temp->rc;
    a[0]=t->data;
    a[1]=temp->data;
    return a;
}

// bstptr find(bstptr t,int x)
// {
//     if(t==null)return null;
//     else
//     {
//         if(t->data==x)return t;
//         if(x<t->data)return find(t->lc,x);
//         else return find(t->rc,x);
//     }
// }

// void deleteLeaf(bstptr root,bstptr t)
// {
//     if(root==null)return;
//     if(root->lc==t)root->lc=null;
//     if(root->rc==t)root->rc=null;
//     deleteLeaf(root->lc,t);
//     deleteLeaf(root->rc,t);
// }
// void deletenode(bstptr &root,bstptr &t,int x)
// {
//     if(x==0){
//         deleteLeaf(root,t);
//         return;
//     }
//     bstptr n=find(root,x);
//     t->data=x;
//     if(n->lc!=null){
//         int lmax = *(minmaxiter(n->lc)+1);
//         deletenode(root,n,lmax);
//     }else{
//         int rmin = *(minmaxiter(n->rc)+0);
//         deletenode(root,n,rmin);
//     }
// }
// void del(bstptr &root,int x)
// {
//     bstptr dele = find(root,x);
//     if(dele->lc!=null){
//         int lmax = *(minmaxiter(dele->lc)+1);
//         deletenode(root,dele,lmax);
//     }else{
//         int rmin = *(minmaxiter(dele->rc)+0);
//         deletenode(root,dele,rmin);
//     }
// }

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
int main()
{
    bstptr t=null;int n;
    cin>>n;
    while(n!=-1)
    {
        insert(t,n);
        cin>>n;
    }
    inorder(t);cout<<endl;
    del(t,10);
    inorder(t);
    return 0;
}
//5 3 7 2 4 6 9 1 8 -1
//8 3 10 1 6 14 4 7 13 -1
