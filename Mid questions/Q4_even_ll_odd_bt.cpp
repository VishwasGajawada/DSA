#include<iostream>
#include<vector>
using namespace std;
#define null NULL
typedef struct node * lptr;
typedef struct btnode * btptr;
struct node{
    int data;
    lptr next;
};

struct btnode{
    int data;
    btptr lc,rc;
};

struct queue{
    int f=-1,r=-1,size=100;
    int elements[100];
    void enq(int x){
        if((r+1)%size==f)return;
        if(f==-1){
            f=r=0;
        }else{
            r=(r+1)%size;
        }
        elements[r]=x;
    }
    int deq()
    {
        if(f==-1)return 0;
        int t=elements[f];
        if(f==r)f=r=-1;
        else f=(f+1)%size;
        return t;
    }
};

struct btq{
    int f=-1,r=-1,size=100;
    btptr elements[100];
    void enq(btptr x){
        if((r+1)%size==f)return;
        if(f==-1){
            f=r=0;
        }else{
            r=(r+1)%size;
        }
        elements[r]=x;
    }
    btptr deq()
    {
        if(f==-1)return null;
        btptr t=elements[f];
        if(f==r)f=r=-1;
        else f=(f+1)%size;
        return t;
    }
};

void addend(lptr &p,char x)
{
    lptr t=new(node);
    t->data = x;
    t->next = null;
    if(p==null){
        p=t;return;
    }
    lptr p1=p;
    while(p1->next!=null){
        p1=p1->next;
    }
    p1->next = t;
}

void create(btptr &t,vector<int> v)
{
    int n=v.size(),i=0;
    btq q;
    t = new(btnode);
    t->data=v[i++];
    t->lc=t->rc=null;
    q.enq(t);

    while(i<n){
        btptr temp=q.deq();
        temp->lc=new (btnode);
        temp->lc->data=v[i++];
        temp->lc->lc=temp->lc->rc=null;
        q.enq(temp->lc);

        if(i>=n)break;
        temp->rc=new (btnode);
        temp->rc->data=v[i++];
        temp->rc->lc=temp->rc->rc=null;
        q.enq(temp->rc);
    }
}

void inorder(btptr t)
{
    if(t==null)return;
    inorder(t->lc);
    cout<<t->data<<" ";
    inorder(t->rc);
}

int main()
{
    queue q;
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        q.enq(x);
    }
    lptr l=null;
    vector<int> b;
    while(q.f>=0){
        int x=q.deq();
        if(x%2==0)addend(l,x);
        else b.push_back(x);
    }
    btptr t=null;
    create(t,b);
    while(l)
    {
        cout<<l->data<<" ";l=l->next;
    }cout<<endl;
    inorder(t);cout<<endl;
}
// 9
// 2 5 8 4 9 1 6 3 7