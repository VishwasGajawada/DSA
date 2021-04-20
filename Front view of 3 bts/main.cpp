#include<iostream>
using namespace std;
typedef struct btnode * btptr;
#define null NULL

struct btnode{
    btptr lc,rc;
    int data;
};
void insert(btptr &t,int k)
{
    if(t==null){
        t=new(btnode);
        t->data=k;
        t->rc=t->lc=null;
    }
    int x;
//    cout<<"enter lc of "<<k<<endl;
//yes
    cin>>x;
    if(x!=0)insert(t->lc,x);
//    cout<<"enter rc of "<<k<<endl;
    cin>>x;
    if(x!=0)insert(t->rc,x);
}
void frontv(btptr t1,btptr t2,btptr t3)
{
    if(!t1 && !t2 && !t3)return;
    if(t3)cout<<t3->data<<" ";
    else if(t2)cout<<t2->data<<" ";
    else if(t1)cout<<t1->data<<" ";

    btptr tmp1=(t1)?t1->lc:t1;
    btptr tmp2=(t2)?t2->lc:t2;
    btptr tmp3=(t3)?t3->lc:t3;

    frontv(tmp1,tmp2,tmp3);

    tmp1=(t1)?t1->rc:t1;
    tmp2=(t2)?t2->rc:t2;
    tmp3=(t3)?t3->rc:t3;

    frontv(tmp1,tmp2,tmp3);


}
int main()
{
    btptr t1=null,t2=null,t3=null;
    int x;
    cin>>x;
    insert(t1,x);
    cin>>x;
    insert(t2,x);
    cin>>x;
    insert(t3,x);
    frontv(t1,t2,t3);
    return 0;
}

// 5 7 9 0 6 0 0 4 0 0 3 0 0
// 8 6 3 7 0 0 0 5 0 0 2 0 0
// 9 4 2 0 3 0 0 8 0 6 0 0 1 5 0 0 7 18 0 0 0
