#include<iostream>
using namespace std;
#define null NULL
typedef struct gtnode * gtptr;

struct gtnode{
    char data;
    int count=0;
    gtptr children[10]={null};
};

void input(gtptr &g,char c)
{
    g = new gtnode;
    g->data=c;
    int cnt;cin>>cnt;
    g->count=cnt;
    for(int i=0;i<cnt;i++)
    {
        cin>>c;
        input(g->children[i],c);
    }
}

void serialize(gtptr g)
{
    if(!g)return;
    cout<<g->data;
    if(g->count==0){
        cout<<".";return;}
    for(int i=0;i<g->count;i++)
    {
        serialize(g->children[i]);
    }
    cout<<".";
    
}

int main()
{
    gtptr GT=null;
    char c;cin>>c;
    
    input(GT,c);
    serialize(GT);
    cout<<".";
}
// A 3 B 3 C 0 D 0 E 0 F 2 G 0 H 0 J 4 K 0 L 0 M 2 P 0 Q 0 N 0 