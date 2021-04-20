#include<iostream>
using namespace std;
#define null NULL
#define m 5
typedef struct mstnode * mstptr;
struct mstnode{
    int cnt=0;
    int keys[m-1]={-1};
    mstptr cptr[m]={null};
};

void insert(mstptr &mt,int k)
{
    if(!mt)
    {
        mt = new mstnode;
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
            insert(mt->cptr[i],k);
            break;
        }
    }
    if(i==0)insert(mt->cptr[i],k);
}

void inorder(mstptr mt)
{
    if(!mt)return;
    for(int i=0;i<mt->cnt;i++)
    {
        inorder(mt->cptr[i]);
        cout<<mt->keys[i]<<" ";
    }
    inorder(mt->cptr[mt->cnt]);
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

void levelorder(mstptr mt)
{
    queue q;
    q.enq(mt);
    mstptr end = new mstnode;
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
        for(int i=0;i<m;i++)
            if(temp->cptr[i])
                q.enq(temp->cptr[i]);
    }
}

int main()
{
    mstptr MT = null;
    int n;cin>>n;
    while(n!=-1)
    {
        insert(MT,n);
        cin>>n;
    }
    inorder(MT);cout<<endl;
    levelorder(MT);cout<<endl;

}
// 18 36 45 20 25 40 9 22 42 41 90 72 85 80 -1
//18 36 45 20 25 40 9 22 42 41 90 72 85 80 7 8 -1