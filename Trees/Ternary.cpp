#include<iostream>
using namespace std;
#define null NULL
typedef struct tnode * tptr;

struct tnode{
    int flag=0;
    char data;
    tptr lc=null,eq=null,rc=null;
};

void insert(tptr &t,string s,int ind)
{
    if(ind>=s.length())return;
    char cur=s[ind];
    if(!t)
    {
        t=new tnode;
        t->data = cur;
        if(ind == s.length() - 1){t->flag=1;return;}
    }
    if(t->data == cur)insert(t->eq,s,ind+1);
    else if(t->data < cur)insert(t->rc,s,ind+1);
    else if(t->data > cur)insert(t->lc,s,ind+1);
}

bool find(tptr t,string s,int ind)
{
    if(!t)return false;
    if(ind>=s.length())return false;
    char cur=s[ind];
    if(t->data == cur && ind == s.length()-1)
    {
        if(t->flag==0)return false;
        if(t->flag==1)return true;
    }
    if(ind==s.length()-1)return false;
    if(t->data==cur)return find(t->eq,s,ind+1);
    else if ( cur < t->data)return find(t->lc,s,ind+1);
    else if ( cur > t->data)return find(t->rc,s,ind+1);
    return false;
}

int main()
{
    tptr T = null;
    // string s = "god";
    insert(T,"god",0);
    insert(T,"good",0);
    insert(T,"best",0);
    insert(T,"better",0);
    string y="god";
    cout<<find(T,y,0);
}
