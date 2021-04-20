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
struct stack{
    int top=-1,size=50;
    lptr elements[50];
    void push(lptr x){
        if(top==size-1)return;
        elements[++top]=x;
    }
    lptr pop(){
        if(top==-1)return null;
        return elements[top--];
    }
};

int main(){
    stack s;
    while(true){
        lptr l=null;
        char c;cin>>c;
        if(c=='*')break;
        while(c!='#'){
            addend(l,c);cin>>c;
        }
        s.push(l);
    }
    while(s.top>=0){
        lptr l=s.pop();
        while(l){
            cout<<l->data<<" ";
            l=l->next;
        }
        cout<<endl;
    }
}