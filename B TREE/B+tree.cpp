#include<bits/stdc++.h>
using namespace std;
#define null NULL
typedef struct Bdnode * bdptr;
struct Bdnode
{
   int data,cnt=0;
   int *keys;
   bdptr *cptr;
   bool leaf=true;
};

void split(bdptr &l,bdptr &r,int &mid,int d)
{
    int mid_ind = d/2-1;//left bias,for right bias take d/2
    if(d%2!=0)mid_ind = (d)/2;
    r->leaf=l->leaf;
    if(l->leaf==true){
        r->keys[r->cnt++]=l->keys[mid_ind];//mid element is also included in right of the splitted part 
        r->cptr[d-1]=l->cptr[d-1];
        l->cptr[d-1]=r;//linking the leaves
    }
    for(int i=mid_ind+1;i<d;i++)
    {
        if(!l->leaf)r->cptr[r->cnt]=l->cptr[i];
        r->keys[r->cnt++]=l->keys[i];
        if(!l->leaf)l->cptr[i]=null;
        l->keys[i]=0;
        l->cnt--;
    }
    if(!l->leaf)r->cptr[r->cnt]=l->cptr[d];
    if(!l->leaf)l->cptr[d]=null;
    mid=l->keys[mid_ind];
    l->keys[mid_ind]=0;
    l->cnt--;
}

void insert(bdptr &bd,int x,int d)
{
    int i=bd->cnt-1;
    while(i>=0 && bd->keys[i]>x)
    {
        bd->keys[i+1]=bd->keys[i];
        if(!bd->leaf)bd->cptr[i+2]=bd->cptr[i+1];
        i--;
    }
    bd->keys[i+1]=x;
    if(!bd->leaf)bd->cptr[i+2]=bd->cptr[i+1];
    bd->cnt++;
}

bdptr kothadi(int d)
{
    bdptr bd = new Bdnode;
    bd->keys=new int[d];// one extra
    bd->cptr = new bdptr[d+1];//one extra
    for(int i=0;i<d+1;i++)bd->cptr[i]=null;
    return bd;
}

void create(bdptr &bd,int &x,int d,bdptr parent,bdptr &head,int &upOrdown,bdptr &left,bdptr &right)
{
    if(!bd)
    {
        bd = kothadi(d);
        bd->keys[bd->cnt++]=x;
        return;
    }
    int ind=-1;
    for(int i=bd->cnt;i>=0;i--)
    {
        if(i==0 && x<bd->keys[0])ind=0;
        if(i!=0 && x > bd->keys[i-1]){ind=i;break;}
    }
    if(bd->cptr[ind]) create(bd->cptr[ind],x,d,bd,head,upOrdown,left,right);//go down till leaf
    else insert(bd,x,d);//is leaf
    if(upOrdown==1){ //coming back from recursion and wants to add mid of child's overflow to current
        insert(bd,x,d);
        ind=-1;
        for(int i=0;i<bd->cnt;i++)
        {
            if(bd->keys[i]==x)ind=i;
        }
        bd->cptr[ind]=left;
        bd->cptr[ind+1]=right;
        upOrdown=0;
    }
    if(bd->cnt==d)//overflow
    {
        bdptr r=kothadi(d);
        split(bd,r,x,d);
        left=bd;right=r;
        if(parent==null)
        {
            bdptr par = kothadi(d);
            par->keys[par->cnt++]=x;
            par->cptr[0]=left;
            par->cptr[1]=right;
            par->leaf=false;
            head=par;
        }
        upOrdown=1;
        return;
    }

}

void create(bdptr &bd,int x,int d)
{
    int upordown=0;
    bdptr left=null,right=null;
    create(bd,x,d,null,bd,upordown,left,right);
}

void levelorder(bdptr bd,int d)
{
    queue<bdptr>q;
    bdptr end = kothadi(d);
    end->keys[end->cnt++]=-1;
    q.push(bd);q.push(end);
    while(true)
    {
        bdptr temp = q.front();q.pop();
        if(temp->keys[0]==-1)
        {
            if(q.empty())break;
            cout<<endl;q.push(end);
        }else{
            for(int i=0;i<temp->cnt;i++)cout<<temp->keys[i]<<" ";
            for(int i=0;i<=temp->cnt;i++)
                if(temp->cptr[i] && !temp->leaf)q.push(temp->cptr[i]);
        }
        
    }
}

int main()
{
    bdptr BD=null;
    int d,n;
    cin>>n;
    d=3;
    while(n!=0)
    {
        create(BD,n,d);
        cin>>n;
    }
    levelorder(BD,d);
}
//10 9 8 7 6 5 4 3 2 1 0
// 3 5 3 8 2 1 7 9 4 6 -1
//5 4 7 22 21 35 12 23 39 16 32 29 46 28 43 64 9 49 53 40 42 24 60 -1

