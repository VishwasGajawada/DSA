#include<iostream>
using namespace std;
#define null NULL
typedef struct tnode * tptr;
struct tnode{
    string s="";
    int tag=0;
    tptr ptr[4]={null};
};

void insert(tptr &t,string s,int i=0)
{
    if(!t){
        t=new tnode;
        t->s=s;
        return;
    }
    if(t->tag==1){
        if(i==s.length())insert(t->ptr[3],s,0);
        else insert(t->ptr[(int)(s[i]-'A')],s,i+1);
        return;
    }
    tptr newn = new tnode;newn->tag=1;
    string olds = t->s;
    insert(newn->ptr[(int)(olds[i]-'A')],olds,0);
    t=newn;
    if(i==s.length())insert(newn->ptr[3],s,0);
    else insert(newn->ptr[(int)(s[i]-'A')],s,i+1);
}

void print(tptr t)
{
    if(!t)return;
    if(t->tag==0)cout<<t->s<<" ";
    for(int i=0;i<4;i++)print(t->ptr[i]);
}

int main()
{
    tptr t = null;
    string s="";
    for(int i=0;i<3;i++)
    {
        cin>>s;
        while(s!="#"){
            insert(t,s);
            cin>>s;
        }
        
        print(t);cout<<endl;
    }
    // print(t);
}
// AAB CABB BAA ABBBC BCCCAA BC #
// A #
// ABB #