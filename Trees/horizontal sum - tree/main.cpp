#include<iostream>
using namespace std;
typedef struct btnode * btptr;
#define null NULL
struct btnode{
    btptr lc=null,rc=null;
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
struct queue{
    int size=100,f=-1,r=-1;
    btptr elements[100];
    void enq(btptr t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
        }
    }
    btptr deq()
    {
        if(f==-1)return null;
        else{
            btptr t;
            t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};
int height(btptr t)
{
    if(t==null)return 0;
    int hl = height(t->lc),hr = height(t->rc);
    return (hl>hr)?1+hl:1+hr;
}
void horiSum(btptr t)
{
    struct queue q;
    q.enq(t);
    btptr temp=new(btnode);
    temp->data = -1;
    q.enq(temp);
    int h = height(t),level=0;
    int a[h]={0};
    while((q.f-q.r)!=0)
    {
        btptr temp2 = q.deq();
        if(temp2->data==-1){
            q.enq(temp);
            level++;
        }
        else{
            a[level]+=temp2->data;
            if(temp2->lc)q.enq(temp2->lc);
            if(temp2->rc)q.enq(temp2->rc);
        }
    }
    for(int i=0;i<h;i++)cout<<a[i]<<" ";
}
int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    horiSum(t);
    return 0;
}
