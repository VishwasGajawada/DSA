#include<iostream>
using namespace std;
#define null NULL
typedef struct node * lptr;
struct node{
    int data;
    struct node *next;
};

void addend(lptr &p,int x)
{
    lptr t,p1;
    t=new(node);
    t->data = x;
    t->next = null;
    if(p==null){
        p=t;
        return;
    }
    p1=p;
    while(p1->next!=null){
        p1=p1->next;
    }
    p1->next = t;
}

void swap(lptr &a,lptr &b)
{
    lptr t=a;
    a=b;
    b=t;
}
struct minHeap
{
    lptr h[50]={null};
    int s=0;
    void insert(lptr x)
    {
        h[s]=x;
        int k = s;
        while(h[k]->data < h[(k-1)/2]->data){
            swap(h[k],h[(k-1)/2]);
            k = (k-1)/2;
        }
        s++;
    }
};
void heapify(struct minHeap &m,int i=0)
{
    int l=2*i+1,r=2*i+2;
    int small=i;
    if(m.h[l] && m.h[small]->data>m.h[l]->data)small=l;
    if(m.h[r] && m.h[small]->data>m.h[r]->data)small=r;
    if(small!=i){
        swap(m.h[small],m.h[i]);
        heapify(m,small);
    }
}
void print(struct minHeap m)
{
    for(int i=0;i<m.s;i++){
        cout<<m.h[i]->data<<" ";
    }
    cout<<endl;
}
lptr mergek(lptr l[],int k)
{
    lptr sorted=null;
    struct minHeap m;
    for(int i=0;i<k;i++){
        m.insert(l[i]);
    }
    while(m.s>0){
        addend(sorted,m.h[0]->data);
        m.h[0]=m.h[0]->next;
        if(!m.h[0]){
            m.h[0]=m.h[m.s-1];
            m.h[m.s-1]=null;
            m.s--;
        }
        heapify(m);
    }
    return sorted;
}
int main()
{
    int k;cin>>k;
    lptr l[k]={null};
    for(int i=0;i<k;i++)
    {
        int x;cin>>x;
        while(x!=-1){
            addend(l[i],x);
            cin>>x;
        }
    }
    lptr sorted=mergek(l,k);
    while(sorted)
    {
        cout<<sorted->data<<" ";
        sorted=sorted->next;
    }

}

// 4
// 1 3 4 -1
// 2 3 7 -1
// 5 6 9 -1
// 8 10 12 -1

