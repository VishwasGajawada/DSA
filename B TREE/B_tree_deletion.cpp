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
   int min;
};

void split(bdptr &l,bdptr &r,int &mid,int d)
{
    int mid_ind = d/2-1;//left bias,for right bias take d/2
    if(d%2!=0)mid_ind = (d)/2;
    r->leaf=l->leaf;
    l->min=r->min=(d-1)/2;
    for(int i=mid_ind+1;i<d;i++)
    {
        r->cptr[r->cnt]=l->cptr[i];
        r->keys[r->cnt++]=l->keys[i];
        l->cptr[i]=null;l->keys[i]=0;
        l->cnt--;
    }
    r->cptr[r->cnt]=l->cptr[d];
    l->cptr[d]=null;
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
        bd->cptr[i+2]=bd->cptr[i+1];
        i--;
    }
    bd->keys[i+1]=x;
    bd->cptr[i+2]=bd->cptr[i+1];
    bd->cnt++;
}

void leftshift(bdptr &bd,int x=0)
{
    for(int i=x;i<bd->cnt-1;i++)
    {
        bd->cptr[i]=bd->cptr[i+1];
        bd->keys[i]=bd->keys[i+1];
    }
    bd->cptr[bd->cnt-1]=bd->cptr[bd->cnt];
    bd->keys[bd->cnt-1]=0;bd->cptr[bd->cnt]=null;
    bd->cnt--;
}

bdptr kothadi(int d)
{
    bdptr bd = new Bdnode;
    bd->keys=new int[d];// one extra
    bd->cptr = new bdptr[d+1];//one extra
    for(int i=0;i<d+1;i++)bd->cptr[i]=null;
    bd->min=(d-1)/2;
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
            par->leaf=false;par->min=1;
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

int getind(bdptr par,bdptr child)
{
    if(!par)return -1;
    for(int i=0;i<=par->cnt;i++){
        if(par->cptr[i]==child)return i;
    }
    return 0;
}

bool borrow(bdptr &parent,bdptr &bd,int d){
    int curind=getind(parent,bd);
    if(curind>0 && parent->cptr[curind-1] && parent->cptr[curind-1]->cnt>=parent->cptr[curind-1]->min+1)
    {
        insert(bd,parent->keys[curind-1],d);
        parent->keys[curind-1]=parent->cptr[curind-1]->keys[parent->cptr[curind-1]->cnt-1];
        bd->cptr[0]=parent->cptr[curind-1]->cptr[parent->cptr[curind-1]->cnt];
        parent->cptr[curind-1]->cptr[parent->cptr[curind-1]->cnt]=null;
        parent->cptr[curind-1]->cnt--;
        return true;
    }
    if(curind!=-1 && curind<=d-1 && parent->cptr[curind+1] && parent->cptr[curind+1]->cnt>=parent->cptr[curind+1]->min+1)
    {
        insert(bd,parent->keys[curind],d);
        parent->keys[curind]=parent->cptr[curind+1]->keys[0];
        bd->cptr[bd->cnt]=parent->cptr[curind+1]->cptr[0];
        leftshift(parent->cptr[curind+1]);
        return true;
    }
    return false;
}

void merge(bdptr &par,bdptr &bd,int d)
{
    int curind=getind(par,bd),ind,num;
    bdptr left,right;
    if(curind>0 && par->cptr[curind-1])
    {
        ind=curind;
        left = par->cptr[curind-1];
        right=bd;
    }
    else if(curind<d && par->cptr[curind+1]){
        ind=curind+1;
        left=bd;
        right=par->cptr[curind+1];
    }
    num=par->keys[ind-1];
    insert(left,num,d);
    for(int i=0;i<right->cnt;i++)
    {
        left->cptr[left->cnt]=right->cptr[i];
        left->keys[left->cnt++]=right->keys[i];
    }
    left->cptr[left->cnt]=right->cptr[right->cnt];
    leftshift(par,ind-1);
    par->cptr[ind-1]=left;
    return;
}

void del(bdptr &bd,int &x,int d,bdptr parent,bdptr &head);
bool replace(bdptr &bd,int d,int ind,bdptr &head)
{
    int lmax,rmin;
    int flag1=1,flag2=1;
    if(bd->cptr[ind] && bd->cptr[ind]->cnt >= bd->cptr[ind]->min){
        bdptr cur=bd->cptr[ind];
        while(!cur->leaf){
            cur=cur->cptr[cur->cnt];
        }
        // if(cur->cnt-1>=cur->min){
            lmax=cur->keys[cur->cnt-1];
            bd->keys[ind]=lmax;
            del(bd->cptr[ind],lmax,d,bd,head);
            return true;    
        // }flag1=0;
        
    }
    if(bd->cptr[ind+1] && bd->cptr[ind+1]->cnt >= bd->cptr[ind+1]->min){
        bdptr cur=bd->cptr[ind+1];
        while(!cur->leaf)cur=cur->cptr[0];
        // if(cur->cnt-1>=cur->min){
            rmin=cur->keys[0];
            bd->keys[ind]=rmin;
            del(bd->cptr[ind+1],rmin,d,bd,head);
            return true;
        // }
        // flag2=0;
    }
    return false;
}

void levelorder(bdptr bd,int d);
void del(bdptr &bd,int &x,int d,bdptr parent,bdptr &head)
{
    if(!bd)return;
    int ind=0;
    while(ind<bd->cnt && bd->keys[ind]<x)ind++;
    if(bd->keys[ind]==x){
        if(bd->leaf && bd->cnt>=bd->min+1)leftshift(bd,ind);
        else if(bd->leaf && bd->cnt<bd->min+1){
            leftshift(bd,ind);
            bool b=borrow(parent,bd,d);
            if(!b) merge(parent,bd,d);
        }
        else if(!bd->leaf)
        {
            bool r = replace(bd,d,ind,head);
            if(!r){
                merge(bd,bd->cptr[ind+1],d);
                del(bd->cptr[ind],x,d,bd,head);

            }
        }
    }else{
        del(bd->cptr[ind],x,d,bd,head);
    
        for(int i=0;i<=bd->cnt;i++)
        {
            if(bd->cptr[i] && bd->cptr[i]->cnt<bd->cptr[i]->min)
            {
                bool b=borrow(bd,bd->cptr[i],d);
                if(!b) merge(bd,bd->cptr[i],d);
                return;
            }
        }
    }
}

void del(bdptr &bd,int x,int d)
{
    del(bd,x,d,null,bd);
    if(bd->cnt<1)
     bd = bd->cptr[0];
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
            cout<<endl;
            if(q.empty())break;q.push(end);
        }else{
            for(int i=0;i<temp->cnt;i++)cout<<temp->keys[i]<<",";
            cout<<" ";
            for(int i=0;i<=temp->cnt;i++)
                if(temp->cptr[i])q.push(temp->cptr[i]);
        }
        
    }
}

int main()
{
    bdptr BD=null;
    int d,n;
    cin>>d>>n;
    while(n!=0)
    {
        create(BD,n,d);
        cin>>n;
    }
    levelorder(BD,d);
    cin>>n;
    while(n!=0)
    {
        del(BD,n,d);
        levelorder(BD,d);
        cin>>n;
    }
    levelorder(BD,d);
}

// 3 5 3 8 2 1 7 9 4 6 10 -1
// 3 5 10 15 20 30 25 31 40 50 45 55 33 35 60 65 28 32 -1
// 3  5 10 15 20 30 35 70 -1
// 5  4 5 6 14 15 16 17 18 19 20 21 90 99 100 101 82 89 80 52 59 13 85 44 32 27 0
