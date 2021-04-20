#include<iostream>
using namespace std;
#define null NULL
// #define m 5
typedef struct mstnode * mstptr;
struct mstnode{
    int cnt=0;
    // int keys[m-1]={-1};
    // mstptr cptr[m]={null};
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
    if(mt->cnt<m-1)
    {
        int j = mt->cnt-1;
        while(j>=0 && mt->keys[j]>k)
        {
            mt->keys[j+1]=mt->keys[j];
            j--;
        }
        mt->keys[j+1]=k;
        mt->cnt++;
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
        }else{
            for(int i=0;i<temp->cnt;i++)cout<<temp->keys[i]<<" ";
            for(int i=0;i<=temp->cnt;i++)
                if(temp->cptr[i])
                    q.enq(temp->cptr[i]);
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
        if(mt->keys[i]==x)
        {
            if(mt->cptr[i+1]){
                mt->keys[i]=mt->cptr[i+1]->keys[0];
                deletion(mt->cptr[i+1],mt->cptr[i+1]->keys[0]);
                if(mt->cptr[i+1]->keys[0]==0)mt->cptr[i+1]=null;
            }else if(mt->cptr[i]){
                mt->keys[i]=mt->cptr[i]->keys[mt->cptr[i]->cnt-1];
                deletion(mt->cptr[i],mt->cptr[i]->keys[mt->cptr[i]->cnt-1]);
                if(mt->cptr[i]->keys[0]==0)mt->cptr[i+1]=null;
            }else{
                for(int j=i;j<mt->cnt-1;j++)
                {
                    mt->keys[j]=mt->keys[j+1];
                }
                mt->keys[mt->cnt-1]=0;
            }
        }
    }
}

int main()
{
    mstptr MT = null;
    int n;cin>>n;
    while(n!=-1)
    {
        insert(MT,n,4);
        cin>>n;
    }
    // inorder(MT);cout<<endl;
    levelorder(MT,4);cout<<endl;
}
// 18 36 45 20 25 40 9 22 42 41 90 72 85 80 7 8 -1
// 18 36 27 9 54 45 50 63 20 47 72  46 49 48 -1