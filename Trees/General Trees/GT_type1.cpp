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
    for(int i=0;i<10;i++)
    {
        cin>>c;
        if(c=='.'){
            g->count=i;return;
        }
        input(g->children[i],c);
    }
}

void printspaces(int i)
{
    for(int j=0;j<i;j++)cout<<" ";
}

void printDir(gtptr g,int s)
{
    if(!g)return;
    printspaces(s);
    cout<<g->data<<endl;
    for(int i=0;i<g->count;i++)
    {
        printDir(g->children[i],s+1);
    }
}

struct queue{
    int size=100,f=-1,r=-1;
    gtptr elements[100];
    void enq(gtptr t)
    {
        if((r+1)%size==f)return;
        else{
            if(f==-1)f=r=0;
            else r=(r+1)%size;
            elements[r]=t;
        }
    }
    gtptr deq()
    {
        if(f==-1)return null;
        else{
            gtptr t;
            t=elements[f];
            if(f==r)f=r=-1;
            else f=(f+1)%size;
            return t;
        }
    }
};


void levelorder(gtptr t)
{
    struct queue q;
    q.enq(t);
    gtptr temp=new(gtnode);
    temp->data = '#';
    q.enq(temp);
    while(q.f!=-1)
    {
        gtptr temp2 = q.deq();
        if(temp2->data=='#'){
            if(q.f==-1)break;
            cout<<endl;
            q.enq(temp);
        }
        else{
            cout<<temp2->data<<" ";
            for(int i=0;i<temp2->count;i++)q.enq(temp2->children[i]);
        }
    }
}

void printbrackets(gtptr g)
{
    if(!g)return;
    cout<<g->data;
    if(g->count>0)
    {
        cout<<"(";
        for(int i=0;i<g->count;i++)printbrackets(g->children[i]);
        cout<<")";
    }
}

int totalnodes(gtptr g)
{
    if(!g)return 0;
    int cur=0;
    for(int i=0;i<g->count;i++){
        cur+=totalnodes(g->children[i]);
    }
    return 1+cur;
}

int main()
{
    gtptr GT=null;
    char c;cin>>c;
    input(GT,c);
    cin>>c;//extra '.'
    // printDir(GT,0);
    // levelorder(GT);cout<<endl;
    // printbrackets(GT);cout<<endl;

}
//ABC.D.E..FG.H..JK.L.MP.Q..N....