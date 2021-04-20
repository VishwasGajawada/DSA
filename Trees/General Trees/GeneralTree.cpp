#include<iostream>
using namespace std;
typedef struct gtnode * gtptr;
#define null NULL
struct gtnode{
    char data;
    gtptr fc=null,ns=null;
};

void input(gtptr &GT,char c)
{
    if(!GT)
    {
        GT = new gtnode;
        GT->data=c;
        GT->fc=GT->ns=null;
    }
    char x;
    // cout<<"enter first child of "<<c<<endl;
    cin>>x;
    if(x!='.')input(GT->fc,x);
    // cout<<"enter next sibling of "<<c<<endl;
    cin>>x;
    if(x!='.')input(GT->ns,x);
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
    temp->fc=temp->ns=null;
    q.enq(temp);
    while(q.f!=q.r)
    {
        gtptr temp2 = q.deq();
        if(temp2->data=='#'){
            cout<<endl;
            q.enq(temp);
        }
        else{
            cout<<temp2->data<<" ";
            gtptr gt3=temp2->fc;
            while(gt3){
                q.enq(gt3);
                gt3=gt3->ns;
            }
        }
    }
}

void serialize(gtptr t)
{
    if(!t)
    {
        cout<<".";
        return;
    }
    cout<<t->data;
    serialize(t->fc);
    serialize(t->ns);
}

void printbrackets(gtptr gt)
{
    if(!gt)return;
    cout<<gt->data<<" ";
    if(gt->fc)
    {
        cout<<"( ";
        printbrackets(gt->fc);
        cout<<") ";
    }
    printbrackets(gt->ns);
}

void printspaces(int i)
{
    for(int j=0;j<i;j++)cout<<" ";
}

void printDir(gtptr g,int spaces)
{
    if(!g)return;
    printspaces(spaces);
    cout<<g->data<<endl;
    printDir(g->fc,spaces+1);
    printDir(g->ns,spaces);

}


int main()
{
    char c;
    gtptr GT=null;
    cin>>c;
    input(GT,c);
    levelorder(GT);cout<<endl;
    serialize(GT);cout<<endl;
    printbrackets(GT);cout<<endl;
    printDir(GT,0);

}
//ABC.D.E..FG.H..JK.L.MP.Q..N....