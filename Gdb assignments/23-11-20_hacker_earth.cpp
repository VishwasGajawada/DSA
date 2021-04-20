#include<iostream>
using namespace std;
#define null NULL
typedef struct tnode * tptr;

struct tnode{
    bool wrd=false;
    tptr ptr[8]={null};
    int power=0;
    // 0-6 for a-g, 7 for #
};

int facto(int x)
{
    int i=2,cnt=0;
    while(i<=x)
    {
        if(x%i==0)
        {
            cnt++;
            x=x/i;
        }else i++;
    }
    return cnt;
}

void insert(tptr &t,string s,int p)
{
    if(!t)t=new tnode;
    tptr cur=t;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='#'){
            if(!cur->ptr[7])cur->ptr[7]=new tnode;
            cur=cur->ptr[7];
        }else{
            if(!cur->ptr[(int)(s[i]-'a')])cur->ptr[(int)(s[i]-'a')]=new tnode;
            cur=cur->ptr[(int)(s[i]-'a')];
        }
    }
    cur->power=p;
    cur->wrd=true;
}
void print(tptr t,string s)
{
    if(!t)return;
    if(t->wrd)cout<<s<<" ";
    for(int i=0;i<7;i++)
    {
        print(t->ptr[i],s+(char)(i+(int)'a'));
    }
    print(t->ptr[7],s+(char)((int)'#'));
}

void check(tptr t,int &large,int &fact)
{
    if(!t)return;
    if(t->wrd)
    {
        int tmp=facto(t->power);
        if(large==0){
            large=t->power;fact=tmp;
        }else{
            if(tmp>fact){
                large=t->power;fact=tmp;
            }else if(tmp==fact){
                if(t->power>large)
                large=t->power;fact=tmp;
            }
        }
    }
    for(int i=0;i<8;i++)check(t->ptr[i],large,fact);
}
void check(tptr t,string s){
    tptr cur=t;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='#')cur=cur->ptr[7];
        else cur=cur->ptr[(int)(s[i]-'a')];
    }
    int lar=0,fact=0;
    check(cur,lar,fact);
    cout<<lar<<endl;
}
int main()
{
    tptr T = null;
    int n,t,a,b;
    cin>>n>>t;
    for(int i=0;i<n;i++)
    {
        cin>>a>>b;
        string s="",temp="";
        for(int j=0;j<b;j++){
            cin>>temp;
            s+=temp;
        }
        insert(T,s,a);
    }
    for(int i=0;i<t;i++)
    {
        cin>>a;
        string s="",temp="";
        for(int j=0;j<a;j++){
            cin>>temp;
            s+=temp;
        }
        check(T,s);
    }
}
// 4
// 8 4 b c f g#
// 24 4 b c d f#
// 16 4 b c d# e
// 45 3 a b g#

// 4 2
// 8 4 b c f g#
// 24 4 b c d f#
// 16 4 b c d# e
// 45 3 a b g#
// 2 b c
// 1 a