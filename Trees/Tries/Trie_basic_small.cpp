#include<iostream>
using namespace std;
#define null NULL
typedef struct tnode * tptr;

struct tnode{
    bool wrd=false;
    tptr ptr[26]={null};
};

void insert(tptr &t,string s,int i=0)
{
    if(!t)t=new tnode;
    if(i>=s.length()){
        t->wrd=true;
        return;
    }
    char c=s[i];
    insert(t->ptr[(int)(c-'a')],s,i+1);
}

bool find(tptr t,string s,int i=0)
{
    if(!t)return false;
    if(i>=s.length()){
        if(t->wrd)return true;
        else return false;
    }
    char c=s[i];
    return find(t->ptr[(int)(c-'a')],s,i+1);
}

void autocom_util(tptr t,string s)
{
    if(!t)return;
    if(t->wrd)cout<<s<<" ";
    for(int i=0;i<26;i++)
    {
        autocom_util(t->ptr[i],s+(char)(i+(int)'a'));
    }
}
void autocom(tptr t,string s,int i=0)
{
    if(!t){
        cout<<"nothing"<<endl;
        return;
    }
    if(i==s.length())
    {
        autocom_util(t,s);cout<<endl;
        return;
    }
    char c=s[i];
    autocom(t->ptr[(int)(c-'a')],s,i+1);
}
int main()
{
    tptr t=null;
    string s;cin>>s;
    while(s!="#"){
        insert(t,s);
        cin>>s;
    }
    string temp="";
    char c;cin>>c;
    while(c!='#')
    {
        temp=temp+c;
        autocom(t,temp);
        cin>>c;
    }
    // autocom(t,"ab");
}
//abc ab bca bb acb ab abb #