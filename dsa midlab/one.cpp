#include<iostream>
#include<vector>
using namespace std;
typedef struct btnode * btptr;
#define null NULL

struct btnode{
    btptr lc,rc;
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
    int size=100;
    int f=-1,r=-1;
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
int bends(struct queue q)
{
    //r to l 0,l to r 1
    int bends=0;
    int partocur,curtochild;
    btptr a,b;
    if(q.f>=0)a=q.deq();
    if(q.f>=0)b=q.deq();
    if(b==a->rc)curtochild=1;
    else curtochild = 0;
    partocur=curtochild;
    a=b;
    while(q.f>=0)
    {
        b=q.deq();
        if(b==a->rc)curtochild=1;
        else curtochild = 0;
        if(partocur!=curtochild)bends++;
        partocur=curtochild;
        a=b;
    }
    return bends;
}
void func(btptr t,struct queue cur,struct queue &maxbends,int &bend)
{
    if(t==null)return;
    if(t->lc==null && t->rc==null)
    {
        cur.enq(t);
        if(bends(cur)>=bends(maxbends))
        {
            bend=bends(cur);
            maxbends=cur;
        }
        return;
    }
    cur.enq(t);
    func(t->lc,cur,maxbends,bend);
    func(t->rc,cur,maxbends,bend);
}
int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    struct queue maxbends,temp;
    int bend=0;
    func(t,temp,maxbends,bend);
    temp = maxbends;
    int length=-1;
    while(temp.f>=0){
        length++;temp.deq();
    }
    cout<<"path length "<<length<<endl;
    temp=maxbends;
    cout<<"path is ";
    while(temp.f!=temp.r)cout<<temp.deq()->data<<"->";
    cout<<temp.deq()->data<<endl;
    cout<<"the maximum number of bends is "<<bend;
    return 0;
}
//4 2 1 0 0 3 0 0 6 5 0 0 7 9 12 0 0 10 0 11 45 0 0 13 0 14 0 0 0