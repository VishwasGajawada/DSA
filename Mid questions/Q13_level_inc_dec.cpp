#include<iostream>
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
    int size=100,f=-1,r=-1;
    btptr elements[100];
    int cursize=0;
    void enq(btptr t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
            cursize++;
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
            cursize--;
            return t;
        }
    }
    void clear()
    {
        for(int i=0;i<100;i++)elements[i]=null;
        f=r=-1;
        cursize=0;
    }
};

bool check(struct queue q)
{
    if(q.cursize<3)return false;
    //inc 1,dec 0
    int prevtocur,curtonext;
    int a =q.deq()->data,b=q.deq()->data;
    if(a==b)return false;
    else if(a<b)curtonext=1;
    else curtonext=0;
    prevtocur=curtonext;
    a=b;
    while(q.f>=0)
    {
        b=q.deq()->data;
        if(a==b)return false;
        else if(a<b)curtonext=1;
        else curtonext=0;
        if(prevtocur == curtonext || a==b)return false;
        prevtocur=curtonext;
        a=b;
    }
    return true;
}

void print(struct queue q)
{
    while(q.f>=0)cout<<q.deq()->data<<" ";
    cout<<endl;
}

void fun(btptr t)
{
    struct queue q,level;
    q.enq(t);
    btptr temp=new(btnode);
    temp->data = -1;
    temp->lc=temp->rc=null;
    q.enq(temp);
    while(true)
    {
        btptr temp2 = q.deq();
        if(temp2->data==-1){
            bool flag = check(level);
            if(flag) print(level);
            if(q.cursize<=0)break;
            level.clear();
            q.enq(temp);
        }
        else{
            level.enq(temp2);
            if(temp2->lc)q.enq(temp2->lc);
            if(temp2->rc)q.enq(temp2->rc);
        }
    }
}

int main()
{
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    fun(t);
    return 0;
}

