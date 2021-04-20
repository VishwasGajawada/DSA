#include<iostream>
using namespace std;
#define null NULL
typedef struct node * lptr;

struct node{
    char data;
    lptr next;
};
void addend(lptr &p,char x)
{
    lptr t=new(node);
    t->data = x;
    t->next = null;
    if(p==null){
        p=t;return;
    }
    lptr p1=p;
    while(p1->next!=null){
        p1=p1->next;
    }
    p1->next = t;
}

struct queue{
    int f=-1,r=-1,size=50;
    lptr elements[50];
    void enq(lptr x){
        if((r+1)%size==f)return;
        if(f==-1)f=r=0;
        else r=(r+1)%size;
        elements[r]=x;
    }
    lptr deq(){
        if(f==-1)return null;
        lptr t=elements[f];
        if(r==f)f=r=-1;
        else f=(f+1)%size;
        return t;
    }
};

int main(){
    queue q;
    while(true){
        lptr l=null;
        char c;cin>>c;
        if(c=='*')break;
        while(c!='#'){
            addend(l,c);cin>>c;
        }
        q.enq(l);
    }
    while(q.f>=0){
        lptr l=q.deq();
        while(l){
            cout<<l->data<<" ";
            l=l->next;
        }
        cout<<endl;
    }
}