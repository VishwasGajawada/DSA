#include<iostream>
using namespace std;
#define null NULL
typedef struct mstnode * mstptr;
struct mstnode{
    int cnt=0;
    int *keys;
    mstptr *cptr;
};

void insert(mstptr &mt,int k,int m)
{
    if(!mt)
    {
        mt=new mstnode;
        mt->keys=new int[m-1];
        mt->cptr = new mstptr[m];
        for(int i=0;i<m;i++)mt->cptr[i]=null;
        mt->keys[mt->cnt++]=k;
        return;
    }
    if(mt->cnt<m-1 && k>mt->keys[mt->cnt-1])
    {
        mt->keys[mt->cnt++]=k;
        return;
    }
    int i;
    for(i=mt->cnt;i>0;i--)
    {
        if(k > mt->keys[i-1]){
            insert(mt->cptr[i],k,m);
            break;
        }
    }
    if(i==0)insert(mt->cptr[i],k,m);
}

struct queue{
    int size=100,f=-1,r=-1;
    mstptr elements[100];
    void enq(mstptr t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
        }
    }
    mstptr deq()
    {
        if(f==-1)return null;
        else{
            mstptr t;
            t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};

struct intqueue{
    int size=100,f=-1,r=-1;
    int elements[100];
    void enq(int t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
        }
    }
    int deq()
    {
        if(f==-1)return 0;
        else{
            int t;
            t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};

void levelorder(mstptr mt,int m,int l_or_r=0)
{
    queue q;q.enq(mt);
    mstptr end = new mstnode;
    end->keys = new int[m-1];
    end->keys[end->cnt++]=-1;
    q.enq(end);
    intqueue elm;
    while(true)
    {
        mstptr temp = q.deq();
        if(temp->keys[0]==-1)
        {
            if(l_or_r==0){
                cout<<elm.deq()<<" ";
                while(elm.f>=0)elm.deq();
            }else{
                while(elm.f!=elm.r)elm.deq();
                cout<<elm.deq()<<" ";
            }
            if(q.f<0)break;
            q.enq(end);
        }else{
            for(int i=0;i<temp->cnt;i++)elm.enq(temp->keys[i]);
            for(int i=0;i<=temp->cnt;i++)
                if(temp->cptr[i])
                    q.enq(temp->cptr[i]);
        }
        
    }
}


int main()
{
    mstptr MT = null;
    int m;cin>>m;
    int n;cin>>n;
    while(n!=0)
    {
        insert(MT,n,4);
        cin>>n;
    }
    levelorder(MT,m,1);

}
// 4 18 36 27 9 54 45 50 63 20 47 72  46 49 48 0