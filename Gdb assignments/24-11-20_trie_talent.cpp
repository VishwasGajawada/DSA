#include<iostream>
using namespace std;
#define null NULL
typedef struct tnode * tptr;
typedef struct string_node * sptr;
typedef struct ptrnode * pptr;
struct string_node{
    string word="";
};
struct ptrnode{
    tptr ptr[4]={null};
};
union u{
    sptr s;
    pptr cptr;
    u(){};
    ~u(){};
};
struct tnode{
    int tag=0;
    tnode(){}
    union u data;
};

void insert(tptr &t,string s,int i=0)
{
    if(!t){
        t=new (tnode);
        t->tag=0;
        t->data.s = new (string_node);
        t->data.s->word=s;
        // new(&t->data.s) std::string(s);
        return;
    }
    if(t->tag==1){
        if(i==s.length())insert(t->data.cptr->ptr[3],s,0);
        else insert(t->data.cptr->ptr[(int)(s[i]-'A')],s,i+1);
        return;
    }
    tptr newn = new tnode;newn->tag=1;
    newn->data.cptr = new (ptrnode);
    for(int i=0;i<4;i++)newn->data.cptr->ptr[i]=null;
    
    string olds = t->data.s->word;
    insert(newn->data.cptr->ptr[(int)(olds[i]-'A')],olds,0);
    t=newn;
    if(i==s.length())insert(newn->data.cptr->ptr[3],s,0);
    else insert(newn->data.cptr->ptr[(int)(s[i]-'A')],s,i+1);
}

void print(tptr t)
{
    if(!t)return;
    if(t->tag==0){cout<<t->data.s->word<<" ";return;}
    for(int i=0;i<4;i++)print(t->data.cptr->ptr[i]);
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
}
// AAB CABB BAA ABBBC BCCCAA BC #
// A #
// ABB #