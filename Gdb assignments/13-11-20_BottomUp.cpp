#include<iostream>
using namespace std;
#define null NULL
// #define m 5
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

struct stack{
    int top=-1,size=50;
    int elements[50];
    void push(int x){
        if(top==size-1)return;
        elements[++top]=x;
    }
    int pop(){
        if(top==-1)return 0;
        return elements[top--];
    }
};

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
    queue q;q.enq(mt);
    mstptr end = new mstnode;
    end->keys = new int[m-1];
    end->keys[end->cnt++]=-1;
    q.enq(end);
    int lrflag=0;
    stack s1,s2;
    while(true)
    {
        mstptr temp = q.deq();
        if(temp->keys[0]==-1)
        {
            if(lrflag==0)lrflag=1;
            else {
                while(s2.top>=0)s1.push(s2.pop());
                lrflag=0;
            }
            if(q.f<0)break;
            q.enq(end);
        }else{
            if(lrflag==0)
                for(int i=0;i<temp->cnt;i++)s1.push(temp->keys[i]);
            else
                for(int i=0;i<temp->cnt;i++)s2.push(temp->keys[i]);
        
            for(int i=0;i<=temp->cnt;i++)
            if(temp->cptr[i])
                q.enq(temp->cptr[i]);
        }
    }
        
    while(s1.top>=0)cout<<s1.pop()<<" ";
}

int main()
{
    mstptr MT = null;
    int m;cin>>m;
    int n;cin>>n;
    while(n!=0)
    {
        insert(MT,n,m);
        cin>>n;
    }
    levelorder(MT,m);
}

// 4 18 36 27 9 54 45 50 63 20 47 72 46 49 48 0




