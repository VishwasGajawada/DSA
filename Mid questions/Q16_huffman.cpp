#include<iostream>
using namespace std;
#define null NULL
typedef struct hnode * hptr;
struct hnode{
    char c;
    int freq;
    hptr lc,rc;
};

void swap(hptr &a,hptr &b)
{
    hptr t=a;
    a=b;
    b=t;
} 

void heapify(hptr h[],int n,int i=0)
{
    int l=2*i+1,r=2*i+2;
    int small=i;
    if(l<n && h[l] && h[small]->freq>h[l]->freq)small=l;
    if(r<n && h[r] && h[small]->freq>h[r]->freq)small=r;
    if(small!=i){
        swap(h[small],h[i]);
        heapify(h,small);
    }
}

void insert(hptr h[],int s)
{
    int k = s;
    while(h[k]->freq < h[(k-1)/2]->freq){
        swap(h[k],h[(k-1)/2]);
        k = (k-1)/2;
    }
}

hptr create(hptr h[],int n)
{
    while(n>1)
    {
        heapify(h,n);
        hptr r = h[0];
        h[0]=h[n-1];
        h[n-1]=null;
        heapify(h,n);
        hptr l = h[0];
        hptr internal = new(hnode);
        internal->c='#';
        internal->freq = l->freq+r->freq;
        internal->lc=l;
        internal->rc=r;
        h[0]=internal;
        n--;
    }
    return h[0];
}

void inorder(hptr t,string s)
{
    if(!t)return;
    inorder(t->lc,s+"0");
    if(!t->lc && !t->rc)
    cout<<t->c<<" "<<s<<endl;
    inorder(t->rc,s+"1");
}

int main()
{
    hptr t=null;
    int n;cin>>n;
    int freq;
    char c;
    hptr h[n]={null};
    for(int i=0;i<n;i++){
        cin>>c>>freq;
        h[i]=new(hnode);
        h[i]->c=c;
        h[i]->freq=freq;
        h[i]->lc=h[i]->rc=null;
        insert(h,i);
    }
    t=create(h,n);
    string s="";
    inorder(t,s);
}
// 7 a 10 e 15 i 12 s 3 t 4 p 13 n 1



