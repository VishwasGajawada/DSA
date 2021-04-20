#include<iostream>
using namespace std;
#define null NULL
typedef struct tnode * tptr;

struct tnode{
    bool wrd=false;
    tptr ptr[127]={null};
};

void insert(tptr &t,string s,int i=0)
{
    if(!t)t=new tnode;
    if(i>=s.length()){
        t->wrd=true;
        return;
    }
    char c=s[i];
    insert(t->ptr[(int)(c)],s,i+1);
}

bool find(tptr t,string s,int i=0)
{
    if(!t)return false;
    if(i>=s.length()){
        if(t->wrd)return true;
        else return false;
    }
    char c=s[i];
    if(c>='a')
    return find(t->ptr[(int)(c-'a')+26],s,i+1);
    else return find(t->ptr[(int)(c-'A')],s,i+1);
}

void print(tptr t,string s)
{
    if(!t)return;
    if(t->wrd)cout<<s<<" ";
    for(int i=0;i<127;i++)
    {
        print(t->ptr[i],s+(char)(i));
    }
}
int main()
{
    tptr t=null;
    for(int i=0;i<5;i++)
    {
        string s;cin>>s;
        insert(t,s);
    }
    print(t,"");
}
// abd5c2
// ac8b9
// bd367a
// cdd294a1
// da5b4c63

