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
    int size;
    int f,r;
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
    return (height(t->lc)>height(t->rc))?1+height(t->lc):1+height(t->rc);
}
//not required explicitly
bool isCompletebt(btptr t)
{
    struct queue q;q.size=100;q.f=q.r=-1;
    q.enq(t);
    btptr temp=new(btnode);
    temp->data = -1;temp->lc=temp->rc=null;
    q.enq(temp);
    int level=1,lastflag=1,h = height(t);
    while((q.f-q.r)!=0)
    {
        btptr temp2 = q.deq();
        if(temp2->data==-1){
            q.enq(temp);
            level++;
        }
        else{
            if(level<h-1){
                if(!temp2->lc || !temp2->rc)return false;
            }
            if(level==h-1){
                if(lastflag==0 && (temp2->lc || temp2->rc))return false;
                if(!temp2->lc)lastflag=0;
                if(lastflag==0 && temp2->rc)return false;
                if(!temp2->rc)lastflag=0;
            }
            if(temp2->lc)q.enq(temp2->lc);
            if(temp2->rc)q.enq(temp2->rc);
        }
    }
    return true;
}
int nodes(btptr t)
{
    if(t == null)return 0;
    return 1+nodes(t->lc)+nodes(t->rc);
}
bool isHeap(btptr t,int i,int n)
{
    if(t==null)return true;
    if(i>=n)return false;
    if((t->lc && t->data > t->lc->data)||(t->rc && t->data > t->rc->data))return false;
    return isHeap(t->lc,2*i+1,n) && isHeap(t->rc,2*i+2,n);
}
int main()
{
    cout<<"good";
    btptr t=null;
    int x;
    cin>>x;
    insert(t,x);
    cout<<isHeap(t,0,nodes(t))<<endl;\
    return 0;
}
//1 2 3 21 0 0 5 0 0 10 0 0 7 8 0 0 18 0 0
//1 2 3 21 0 0 5 0 0 10 0 7 0 0 7 8 0 0 18 0 0
