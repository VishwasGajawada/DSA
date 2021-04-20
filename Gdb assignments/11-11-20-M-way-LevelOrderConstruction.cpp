#include<iostream>
#include<climits>
using namespace std;
#define null NULL
typedef struct mstnode * mstptr;
struct mstnode{
    int cnt=0;
    int *keys;
    mstptr *cptr;
    int min,max;
};
mstptr create(int m)
{
    mstptr mt=new mstnode;
    mt->keys=new int[m-1];
    mt->cptr = new mstptr[m];
    for(int i=0;i<m;i++)mt->cptr[i]=null;
    return mt;
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

void levelorder(mstptr mt,int m)
{
    queue q;
    q.enq(mt);
    mstptr end = new mstnode;
    end->keys = new int[m-1];
    end->keys[end->cnt++]=-1;
    q.enq(end);
    while(q.f!=q.r)
    {
        mstptr temp = q.deq();
        if(temp->keys[0]==-1)
        {
            cout<<endl;
            q.enq(end);
            continue;
        }
        for(int i=0;i<temp->cnt;i++)cout<<temp->keys[i]<<" ";
        for(int i=0;i<=temp->cnt;i++)
            if(temp->cptr[i])
                q.enq(temp->cptr[i]);
    }
}

void input(mstptr &mt,int m)
{
    int x;
    mt=create(m);
    mt->min=INT_MIN;
    mt->max=INT_MAX;
    queue q;q.enq(mt);
    mstptr temp = q.deq();
    while(true)
    {
        if(temp->cnt>=m-1)temp=q.deq();
        cin>>x;
        if(x==-1)break;
        while(x>temp->max)temp=q.deq();
        temp->keys[temp->cnt++]=x;
        if(temp->cnt==m-1)
        {
            for(int i=0;i<=temp->cnt;i++)
            {
                if(i==0)
                {
                    temp->cptr[i]=create(m);
                    temp->cptr[i]->min=temp->min;
                    temp->cptr[i]->max=temp->keys[i];
                    q.enq(temp->cptr[i]);
                }else if(i==temp->cnt)
                {
                    temp->cptr[i]=create(m);
                    temp->cptr[i]->min=temp->keys[i-1];
                    temp->cptr[i]->max=temp->max;
                    q.enq(temp->cptr[i]);
                }else{
                    temp->cptr[i]=create(m);
                    temp->cptr[i]->min=temp->keys[i-1];
                    temp->cptr[i]->max=temp->keys[i];
                    q.enq(temp->cptr[i]);
                }
            }
        }
    }
}

void deletion(mstptr &mt,int x)
{
    if(!mt)return;
    if(x<mt->keys[0]){deletion(mt->cptr[0],x);return;}
    else if(x > mt->keys[mt->cnt-1]){deletion(mt->cptr[mt->cnt],x);return;}
    
    for(int i=mt->cnt-1;i>=0;i--)
    {
        if(i!=mt->cnt-1 && mt->keys[i]<x && x< mt->keys[i+1])
        {
            deletion(mt->cptr[i+1],x);
            break;
        }
        if(mt->keys[i]==x)
        {
            if(mt->cptr[i+1]->cnt>0){
                mt->keys[i]=mt->cptr[i+1]->keys[0];
                deletion(mt->cptr[i+1],mt->cptr[i+1]->keys[0]);
                if(mt->cptr[i+1]->keys[0]==0)mt->cptr[i+1]=null;
            }else if(mt->cptr[i]->cnt>0){
                mt->keys[i]=mt->cptr[i]->keys[mt->cptr[i]->cnt-1];
                deletion(mt->cptr[i],mt->cptr[i]->keys[mt->cptr[i]->cnt-1]);
                if(mt->cptr[i]->keys[0]==0)mt->cptr[i]=null;
            }else{
                for(int j=i;j<mt->cnt-1;j++)
                {
                    mt->keys[j]=mt->keys[j+1];
                }
                mt->keys[--mt->cnt]=0;
            }
            break;
        }
    }
    
}

int main()
{
    mstptr MT = null;
    int m;cin>>m;
    input(MT,m);//levelorder input
    levelorder(MT,m);cout<<endl;
    int d;cin>>d;
    deletion(MT,d);
    cin>>d;
    deletion(MT,d);
    levelorder(MT,m);

}
//3 
//18 54 6 8 25 45 63 81 1 3 10 12 30 36 72 75 90 -1
// 25 
// 54 