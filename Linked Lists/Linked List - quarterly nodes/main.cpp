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

void func(lptr l)
{
    lptr quarter1=l,quarter3=l,mid=l;
    int i=1;
    for(lptr temp=l;temp!=null;temp=temp->next,i++)
    {
        if(i%4==0)quarter1=quarter1->next;
        if(i%2==0)mid=mid->next;
    }
    i=1;quarter3=mid;
    for(lptr temp=mid;temp!=null;temp=temp->next,i++)
    {
        if(i%2==0)quarter3=quarter3->next;
    }
    cout<<quarter1->data<<" "<<mid->data<<" "<<quarter3->data;
}
int main()
{
    int n;
    lptr l=null;
    cin>>n;
    while(n!=-1)
    {
        addend(l,n);
        cin>>n;
    }
    print(l);
    func(l);
    return 0;
}
