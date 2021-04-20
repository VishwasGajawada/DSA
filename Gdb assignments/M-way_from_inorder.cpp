#include<bits/stdc++.h>
// #include<math.h>
using namespace std;
#define null NULL
typedef struct mstnode * mstptr;
struct mstnode{
    int cnt=0;
    int *keys;
    mstptr *cptr;
};

void levelorder(mstptr mt,int m)
{
    queue<mstptr>q;
    q.push(mt);
    mstptr end = new mstnode;
    end->keys = new int[m-1];
    end->keys[end->cnt++]=-1;
    q.push(end);
    while(true)
    {
        mstptr temp = q.front();
        q.pop();
        if(temp->keys[0]==-1)
        {
            if(q.empty())break;
            cout<<endl;
            q.push(end);
        }else{
            for(int i=0;i<temp->cnt;i++)cout<<temp->keys[i]<<" ";
            for(int i=0;i<=temp->cnt;i++)
                if(temp->cptr[i])
                    q.push(temp->cptr[i]);
        }
        
    }
}

void create(mstptr &mt,queue<int> &inorder,int m,int levels,int cur_l=1)
{
    mt=new mstnode;
    mt->keys=new int[m-1];
    mt->cptr = new mstptr[m];
    for(int i=0;i<m;i++)mt->cptr[i]=null;
    for(int i=0;i<m-1;i++)
    {
        if(cur_l!=levels)create(mt->cptr[i],inorder,m,levels,cur_l+1);
        mt->keys[mt->cnt++]=inorder.front();
        inorder.pop();
    }
    if(cur_l!=levels)create(mt->cptr[m-1],inorder,m,levels,cur_l+1);
}

int main()
{
    mstptr MT = null;
    int n,m;
    queue<int> inorder;
    cin>>m>>n;
    while(n!=-1)
    {
        inorder.push(n);
        cin>>n;
    }
    int levels = ceil(log(inorder.size()+1)/log(m));
    create(MT,inorder,m,levels);
    levelorder(MT,m);
    
}
//3 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 -1