#include<iostream>
#include<vector>
using namespace std;
#define null NULL
typedef struct bstnode * bstptr;
struct bstnode{
    int data;
    bstptr lc,rc;
};

void insert(bstptr &t,int k)
{
    if(t==null){
        t=new(bstnode);
        t->data=k;
        t->lc=t->rc=null;
        return;
    }
    if(k<t->data)insert(t->lc,k);
    else insert(t->rc,k);
}

bool compare(bstptr t1,bstptr t2)
{
    if(!t1 && !t2)return true;
    if(!t1 || !t2)return false;
    if(t1->data != t2->data) return false;
    return compare(t1->lc,t2->lc) && compare(t1->rc,t2->rc);
}

bstptr make(vector<int>v)
{
    bstptr t=null;
    for(int i=0;i,i<v.size();i++)
        insert(t,v[i]);
    return t;
}

void permute(vector<vector<int>> &all,vector<int> v,int l,int r)
{
    if (l == r)  
        all.push_back(v);
    else
    {  
        for (int i = l; i <= r; i++)  
        {  
            swap(v[l], v[i]);  
            permute(all,v, l+1, r);  
            swap(v[l], v[i]);  
        }  
    }  
}

void print(vector<int> v)
{
    for(int i=0;i<v.size();i++)cout<<v[i]<<" ";
    cout<<endl;
}

void func(bstptr t,vector<int>v)
{
    vector<vector<int>> all;
    permute(all,v,0,v.size()-1);

    for(int i=0;i<all.size();i++)
    {
        bstptr temp = make(all[i]);
        if(compare(temp,t))print(all[i]);
    }
}

int main()
{
    int n;cin>>n;
    vector<int> v;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        v.push_back(x);
    }
    bstptr t= make(v);
    cout<<"all"<<endl;
    func(t,v);

}
// 5
// 9 5 7 15 12