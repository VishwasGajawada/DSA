#include<iostream>
using namespace std;
typedef struct btnode * btptr;
#define null NULL
struct btnode{
    btptr lc,rc;
    int data;
    int hd;
};
void insert(btptr &t,int k)
{
    if(t==null){
        t=new(btnode);
        t->data=k;
        t->rc=t->lc=null;
    }
    int x;cin>>x;
    if(x!=0)insert(t->lc,x);
    cin>>x;
    if(x!=0)insert(t->rc,x);
}
struct queue{
    int size=100,f=-1,r=-1;
    btptr elements[100];
    void enq(btptr t)
    {
        if((r+1)%size==f)return;//full
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
            btptr t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};
void vertSum(btptr t)
{
    struct queue q;q.size=100;q.f=q.r=-1;
    int hd=0;
    t->hd=hd;
    q.enq(t);
    int distelements[100]={0};
    distelements[50]=hd;
    while(q.f>=0)
    {
        btptr temp=q.deq();
        hd=temp->hd;
        distelements[50+hd]+=temp->data;
        if(temp->lc)
        {
            temp->lc->hd=hd-1;
            q.enq(temp->lc);
        }
        if(temp->rc)
        {
            temp->rc->hd=hd+1;
            q.enq(temp->rc);
        }
    }
    for(int i=0;i<100;i++)
    {
        if(distelements[i]!=0)cout<<distelements[i]<<" ";
    }
}
int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    vertSum(t);
    return 0;
}
