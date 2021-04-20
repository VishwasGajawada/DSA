#include<iostream>
#include<math.h>
using namespace std;
#define null NULL
typedef struct qminh * qptr;
struct qminh{
    int data;
    int cnt=0;
    qptr cptr[4]={null};
};
void swap(int &a,int &b)
{
    int t=a;
    a=b;b=t;
}

void heapify(qptr &qm)
{
    if(!qm)return;
    int min_in=-1;
    for(int i=0;i<qm->cnt;i++)
    {
        if(qm->data > qm->cptr[i]->data)min_in=i;
    }
    if(min_in==-1)
    {
        for(int i=0;i<qm->cnt;i++)
        {
            heapify(qm->cptr[i]);
        }
        return;
    }
    swap(qm->data,qm->cptr[min_in]->data);
    heapify(qm->cptr[min_in]);
}

int height(qptr qm)
{
    if(!qm)return 0;
    int max=0;
    for(int i=0;i<qm->cnt;i++)
    {
        if(height(qm->cptr[i])>max)max=height(qm->cptr[i]);
    }
    return max+1;
}

int num_nodes(qptr qm)
{
    if(!qm)return 0;
    int x=0;
    for(int i=0;i<qm->cnt;i++)
    {
        x+=num_nodes(qm->cptr[i]);
    }
    return x+1;
}

//check below insert function,not this for queue approach
void insert(qptr &qm,int x,int h)
{
    if(!qm)
    {
        qm=new qminh;
        qm->data=x;
        return;
    }
    if(qm->cnt<4)
    {
        insert(qm->cptr[qm->cnt++],x,h-1);
        if(qm->cptr[qm->cnt-1]->data < qm->data)
          swap(qm->cptr[qm->cnt-1]->data,qm->data);
        return;
    }
    for(int i=0;i<4;i++)
    {
        int temph = h;
        if(num_nodes(qm)<(pow(4,h)-1)/3)temph=h-1;
        temph = (pow(4,temph)-1)/3;
        if(num_nodes(qm->cptr[i])<temph)
        {
            insert(qm->cptr[i],x,h-1);
            if(qm->cptr[i]->data < qm->data )
            swap(qm->cptr[i]->data , qm->data);
            return;
        }
    }

}

struct queue{
    int size=100,f=-1,r=-1;
    qptr elements[100];
    void enq(qptr t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
        }
    }
    qptr deq()
    {
        if(f==-1)return null;
        else{
            qptr t;
            t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};

void levelorder(qptr mt)
{
    queue q;
    q.enq(mt);
    qptr end = new qminh;
    end->data=-1;
    q.enq(end);
    while(q.f!=q.r)
    {
        qptr temp = q.deq();
        if(temp->data==-1)
        {
            cout<<endl;
            q.enq(end);
            continue;
        }
        cout<<temp->data<<" ";
        for(int i=0;i<temp->cnt;i++)
            if(temp->cptr[i])
            q.enq(temp->cptr[i]);
    }
}

void insert(qptr &qm)
{
    int x;cin>>x;
    qm=new qminh;
    qm->data=x;
    queue q;q.enq(qm);
    int flag=1;
    while(true)
    {
        qptr temp = q.deq();
        while(temp->cnt<4)
        {
            cin>>x;
            if(x==-1){
                flag=0;break;
            }
            temp->cptr[temp->cnt]=new qminh;
            temp->cptr[temp->cnt]->data=x;
            q.enq(temp->cptr[temp->cnt++]);
            heapify(qm);
        }
        if(flag==0)break;
    }
}

int main()
{
    qptr qh=null;
    // int n;
    // cin>>n;
    // while(n!=-1)
    // {
    //     insert(qh,n,height(qh));
    //     cin>>n;
    // }
    insert(qh);
    levelorder(qh);
}
// 9 5 12 3 10 6 8 14 11 4 7 1 13 15 2 -1 
