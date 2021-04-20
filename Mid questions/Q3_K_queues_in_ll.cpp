#include<iostream>
using namespace std;
typedef struct node * lptr;
#define null NULL

struct node{
    int data;
    lptr next=null;
};

struct queue{
    int size,f,r;
    int start,end;
    lptr elements;
};

lptr getnode(lptr l,int ind){
    int x=0;
    while(l){
        if(x==ind)return l;
        x++;
        l=l->next;
    }
    return NULL;
}
void enq(struct queue q[],int i,int x){
    if((q[i].f==q[i].start && q[i].r==q[i].end)||(q[i].r+1==q[i].f)){
        cout<<"full"<<endl;return;
    }
    if(q[i].f<q[i].start){
        q[i].f=q[i].r=q[i].start;
        lptr temp = getnode(q[i].elements,q[i].f);
        temp->data=x;
    }else
    {
        if(q[i].r==q[i].end)q[i].r=q[i].start;
        else q[i].r++;
        lptr temp=getnode(q[i].elements,q[i].r);
        temp->data=x;
    }
}

int  deq(struct queue q[],int i)
{
    if(q[i].f<q[i].start)return 0;
    int t;
    if(q[i].f==q[i].r){
        lptr temp=getnode(q[i].elements,q[i].f);
        t=temp->data;
        temp->data=0;
        q[i].f=q[i].r=q[i].start-1;
    }
    else{
        lptr temp=getnode(q[i].elements,q[i].f);
        t=temp->data;
        temp->data=0;
        if(q[i].f==q[i].end)q[i].f=q[i].start;
        else q[i].f++;
    }
    return t;
}

int main()
{
    int k,n=100;
    cin>>k;
    int size=n/(k);
    lptr l=new(node);
    lptr temp=l;
    for(int i=0;i<n;i++){
        temp->data=0;
        if(i!=n-1)temp->next=new(node);
        else temp->next=null;
        temp=temp->next;
    }
    struct queue q[k];
    for(int i=0;i<k;i++){
        q[i].size=size;
        q[i].start=i*q[i].size;
        q[i].end = q[i].start+i*q[i].size-1;
        q[i].f=q[i].r=q[i].start-1;
        q[i].elements=l;
    }
    int a=10,b=0;
    while(a!=0){
        cin>>a;
        if(a==0)break;
        if(a<0)deq(q,0-a-1);
        else
        {
            cin>>b;
            enq(q,a-1,b);
        }
    }
    temp=l;
    int i=0;
    while(temp){
        if(i%size==0)cout<<endl;
        if(temp->data!=0)
            cout<<temp->data<<" ";
        temp=temp->next;
        i++;
    }
    return 0;
}
// 4
// 1 1
// 3 2
// 2 5
// 3 5
// 1 8
// 2 14
// 1 11
// 4 12
// 3 7
// 3 16
// 4 4
// 2 18
// 4 99
// -2
// -3  0