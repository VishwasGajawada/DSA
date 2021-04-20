#include<iostream>
using namespace std;
#define null NULL
typedef struct itnode  * iptr;
struct itnode{
    int low,high,max;
    itnode *lc=null,*rc=null;
};


void insert(iptr &t,int l,int h,int max)
{
    if(!t)
    {
        t = new itnode;
        t->low = l;t->high=h;t->max=max;
        t->lc=t->rc=null;
        return;
    }
    if(t->max<max)t->max=max;
    if(l<t->low)insert(t->lc,l,h,max);
    else insert(t->rc,l,h,max);

}
void inorder(iptr t)
{
    if(!t)return;
    inorder(t->lc);
    cout<<t->low<<" "<<t->high<<" "<<t->max<<endl;
    inorder(t->rc);
}
void interval(iptr t,int x,int y){
    if(t==null)return;
    if(t->low<=x && y<=t->high){
        cout<<t->low<<" "<<t->high<<endl;
    }
    interval(t->lc,x,y);
    interval(t->rc,x,y);
}
int main(){
    iptr t=null;
    // int n;cin>>n;
    int q=8;
    while(q--){
        int a;cin>>a;
        if(a==1){
            int l,h,m;
            cin>>l>>h>>m;
            insert(t,l,h,m);
        }else{
            int x,y;
            cin>>x>>y;
            interval(t,x,y);
        }
    }
    // inorder(t);
}
// 1 15 20 20
// 1 10 30 30
// 1 12 15 15
// 1 5 20 20
// 1 17 19 40
// 1 30 40 40
// 2 6 7
// 2 32 35