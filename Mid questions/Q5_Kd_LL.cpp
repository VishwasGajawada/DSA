#include<iostream>
using namespace std;
typedef struct knode * kptr;
typedef struct node * lptr;
#define null NULL

struct node{
    int data;
    lptr next=null;
};
struct knode{
    lptr keys;
    kptr lc,rc;
};

int getData(lptr l,int i){
    int x=0;
    while(l){
        if(x==i)return l->data;
        l=l->next;
        x++;
    }
    return 0;
}

void insert(kptr &t,lptr l,int d,int i=0){
    if(t==null){
        t=new(knode);t->keys = new(node);t->lc=t->rc=null;
        
        lptr temp=t->keys;
        while(l){
            temp->data=l->data;
            if(l->next)temp->next=new(node);
            else temp->next=null;
            temp=temp->next;
            l=l->next;
        }
        return;
    }
    if(getData(t->keys,i)>getData(l,i))insert(t->lc,l,d,(i+1)%d);
    else insert(t->rc,l,d,(i+1)%d);
}
void inorder(kptr t)
{
    if(t==null)return;
    inorder(t->lc);
    lptr temp=t->keys;
    while(temp){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
    inorder(t->rc);
}
int main(){
    int d;
    cin>>d;
    kptr t=null;
    int a;
    while(true){
        cin>>a;
        if(a==-1)break;
        lptr temp1=new(node);
        temp1->data=a;
        temp1->next=null;
        lptr temp2=temp1;
        for(int i=1;i<d;i++){
            cin>>a;
            lptr temp3=new(node);
            temp3->data=a;
            temp3->next=null;
            temp2->next=temp3;
            temp2=temp2->next;
        }
        insert(t,temp1,d);
    }
    inorder(t);
}
// 5
// 5 2 3 4 11
// 9 8 12 43 2
// 4 3 5 1 32
// 1 4 2 42 12
// 3 5 4 6 14
// 14 15 32 4 9
// 32 43 12 56 16
// -1