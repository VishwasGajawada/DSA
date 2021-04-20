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
    cout<<"enter lc of "<<k<<endl;
    cin>>x;
    if(x!=0)insert(t->lc,x);
    cout<<"enter rc of "<<k<<endl;
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
            btptr t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};

// void serialize(btptr t,string &s)
// {
//     if(t==null){
//         s=s+".";
//         return;
//     }
//     s=s + "" + t->data;
//     serialize(t->lc,s);
//     serialize(t->rc,s);
// }

int findIndex(string ldr,char c)
{
    for(int i=0;i<9;i++){
        if(ldr[i]==c)return i;
    }
    return 0;
}
int nodes(btptr t)
{
    if(t==null)return 0;
    return 1+nodes(t->lc)+nodes(t->rc);
}
int leafnodes(btptr t)
{
    if(t==null)return 0;
    if(t->lc==null && t->rc==null)return 1;
    return leafnodes(t->lc)+leafnodes(t->rc);
}
void preorder(btptr t)
{
    if(t==null)return;
    cout<<t->data;
    preorder(t->lc);
    preorder(t->rc);
}
void levelorder(btptr t)
{
    struct queue q;
    q.size=100;
    q.f=q.r=-1;
    q.enq(t);
    btptr temp=new(btnode);
    temp->data = -1;
    temp->lc=temp->rc=null;
    q.enq(temp);
    while((q.f-q.r)!=0)
    {
        btptr temp2 = q.deq();
        if(temp2->data==-1){
            cout<<endl;
            q.enq(temp);
        }
        else{
            cout<<temp2->data<<" ";
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
    levelorder(t);
    // string s="";
    // // serialize(t,s);
    // cout<<s<<endl;
}
