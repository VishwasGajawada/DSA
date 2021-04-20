#include<iostream>
using namespace std;
#define null NULL
typedef struct treapnode * trptr;
struct treapnode{
    char key;
    int priority;
    trptr lc=null,rc=null;
};

void left_rotate(trptr bt,trptr &root)
{
    trptr r = bt->rc;
    bt->rc = r->lc;
    r->lc = bt;
    root=r;
}

void right_rotate(trptr bt,trptr &root)
{
    trptr l=bt->lc;
    bt->lc=l->rc;
    l->rc=bt;
    root = l;
}

void insert(trptr &t,char k,int pri)
{
    if(!t)
    {
        t=new treapnode;
        t->key = k;t->priority=pri;
        return;
    }
    if(t->key > k){
        insert(t->lc,k,pri);
        if(t->lc->priority < t->priority)right_rotate(t,t);
    }
    else if(t->key < k){
        insert(t->rc,k,pri);
        if(t->rc->priority < t->priority)left_rotate(t,t);
    }
}

void del(trptr &t,char k)
{
    if(!t)return;
    if(t->key==k)
    {
        if(!t->rc && !t->lc)t=null;
        else if(t->rc && !t->lc)t=t->rc;
        else if(t->lc && !t->rc)t=t->lc;
        else{
            if(t->lc->priority < t->rc->priority){
                t->key = t->lc->key;
                t->priority = t->lc->priority;
                del(t->lc,t->lc->key);    
            }else{
                t->key = t->rc->key;
                t->priority = t->rc->priority;
                del(t->rc,t->rc->key);
            }
        }
        return;
    }
    if(k < t->key)del(t->lc,k);
    else if( k > t->key)del(t->rc,k);
}

void inorder(trptr t)
{
    if(!t)return;
    inorder(t->lc);
    cout<<t->key<<" "<<t->priority<<" ";
    inorder(t->rc);
}

int main()
{
    trptr tr=null;
    char k;
    int pri;
    while(true)
    {
        cin>>k;
        if(k=='#')break;
        cin>>pri;
        insert(tr,k,pri);
    }
    inorder(tr);
    char c;cin>>c;
    del(tr,c);cin>>c;
    del(tr,c);
    inorder(tr);

}
//p 45 s 63 h 21 m 36 e 27 g 9 # g h