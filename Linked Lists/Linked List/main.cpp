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

void print(lptr p){
    while(p!=null)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

int main()
{
    int n;
    lptr l;
    cin>>n;
    while(n!=-1)
    {
        addend(l,n);
        cin>>n;
    }
    print(l);
    return 0;
}
