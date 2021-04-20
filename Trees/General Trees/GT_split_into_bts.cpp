#include<iostream>
using namespace std;
#define null NULL
typedef struct gtnode * gtptr;

struct gtnode{
    char data;
    int count=0;
    gtptr children[10]={null};
    int done=0;
};

void input(gtptr &g,char c)
{
    g = new gtnode;
    g->data=c;
    for(int i=0;i<10;i++)
    {
        cin>>c;
        if(c=='.'){
            g->count=i;return;
        }
        input(g->children[i],c);
    }
}

void splitPrint(gtptr g,gtptr head)
{
    if(!g){
        cout<<".";return;
    }
    cout<<g->data;
    int i=0,cnt=2;
    while(cnt!=0)
    {
        if(i<g->count && g->children[i]->done==0)
        {
            splitPrint(g->children[i],head);
            cnt--;
        }else if(i>g->count){
            cout<<".";
            cnt--;
        }
        i++;
    }
    g->done=1;
    for(int j=0;j<g->count;j++){
        if(g->children[j]->done==0){
            g->done=0;
            break;
        }
    }
    if(g==head && g->done==0)
    {
        cout<<endl;
        splitPrint(g,g);
    }
}
int main()
{
    gtptr GT=null;
    char c;cin>>c;
    input(GT,c);
    cin>>c;//extra '.'
    splitPrint(GT,GT);
}
// ABFI.J..SK..H.O..C.DLM.N..P.Q..E...
// ABFI.J..SK..H..C.DLM.N..P.Q..E...