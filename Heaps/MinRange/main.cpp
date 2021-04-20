#include<iostream>
#include<climits>
using namespace std;
#define null NULL
typedef struct node * lptr;
struct node{
    int data;
    struct node *next;
};
//hi
void addend(lptr &p,int x){
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

void swap(lptr &a,lptr &b){
    lptr t=a;
    a=b;
    b=t;
}

struct minHeap{
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
    void heapify(int i=0)
    {
        int l=2*i+1,r=2*i+2;
        int small=i;
        if(h[l] && h[small]->data>h[l]->data)small=l;
        if(h[r] && h[small]->data>h[r]->data)small=r;
        if(small!=i){
            swap(h[small],h[i]);
            heapify(small);
        }
    }
    lptr pop()
    {
        lptr ans=h[0];
        h[0]=h[s-1];
        h[s-1]=null;
        s--;
        heapify();
        return ans;
    }
};

void print(struct minHeap m){
    for(int i=0;i<m.s;i++){
        cout<<m.h[i]->data<<" ";
    }
    cout<<endl;
}

void range(lptr l[],int k){
    struct minHeap m;
    int range=INT_MAX,mi=INT_MIN,ma=INT_MAX;
    int curmax=l[0]->data,curmin=0;
    for(int i=0;i<k;i++){
        m.insert(l[i]);
        if(l[i]->data>curmax)curmax=l[i]->data;
    }
    while(true)
    {
        curmin=m.h[0]->data;
        if(curmax-curmin<range-1){
            range=curmax-curmin+1;
            mi=curmin;
            ma=curmax;
        }
        m.h[0]=m.h[0]->next;
        if(!m.h[0])break;
        else{
            if(m.h[0]->data>curmax)curmax=m.h[0]->data;
            m.heapify();
        }
    }
    cout<<mi<<" "<<ma;
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
    range(l,k);
}
// 4
// 3 6 8 10 15 -1
// 1 5 12 -1
// 4 8 15 13 -1
// 2 6 -1