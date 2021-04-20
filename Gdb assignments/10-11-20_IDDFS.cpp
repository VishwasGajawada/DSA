#include<iostream>
using namespace std;
#define null NULL
typedef struct gtnode * gtptr;

struct gtnode{
    int data;
    int count=0;
    gtptr children[10]={null};
};

void input(gtptr &g,int c)
{
    g = new gtnode;
    g->data=c;
    for(int i=0;i<10;i++)
    {
        cin>>c;
        if(c==0){
            g->count=i;return;
        }
        input(g->children[i],c);
    }
}
bool DLS(gtptr src,int target,int limit);
bool IDDFS(gtptr src,int target,int maxdepth)
{
    for(int limit=0;limit<maxdepth;limit++){
        if(DLS(src,target,limit))return true;
    }
    return false;
}

bool DLS(gtptr src,int target,int limit)
{
    if(src->data==target)return true;
    if(limit<=0)return false;
    for(int i=0;i<src->count;i++)
    {
        if(DLS(src->children[i],target,limit-1))
            return true;
    }
    return false;
}

struct queue{
    int size=100,f=-1,r=-1;
    gtptr elements[100];
    void enq(gtptr t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
        }
    }
    gtptr deq()
    {
        if(f==-1)return null;
        else{
            gtptr t;
            t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};

void levelorder(gtptr t)
{
    struct queue q;
    q.enq(t);
    gtptr temp=new(gtnode);
    temp->data = -1;
    q.enq(temp);
    while(q.f!=-1)
    {
        gtptr temp2 = q.deq();
        if(temp2->data==-1){
            if(q.f==-1)break;
            cout<<endl;
            q.enq(temp);
        }
        else{
            cout<<temp2->data<<" ";
            for(int i=0;i<temp2->count;i++)q.enq(temp2->children[i]);
        }
    }
}

int main()
{
    gtptr GT=null;
    int c;cin>>c;
    input(GT,c);
    cin>>c;//extra '.'
    levelorder(GT);cout<<endl;
    int q;cin>>q;
    while(q--)
    {
        int a;cin>>a;
        if(IDDFS(GT,a,5))cout<<"1"<<endl;
        else cout<<"0"<<endl;
    }
}
// 50 49 47 33 0 43 35 0 34 0 0 42 32 0 0 0 0 46 41 31 0 30 0 0 40 29 0 28 0 0 0 48 45 39 27 0 26 0 0 38 25 0 24 0 0 0 44 37 23 0 22 0 0 21 0 36 20 0 0 0 0 0 0 
// 3 
// 21 
// 35 
// 19 




