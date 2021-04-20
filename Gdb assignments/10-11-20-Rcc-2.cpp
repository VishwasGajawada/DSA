#include<iostream>
using namespace std;
#define null NULL
typedef struct gtnode * gtptr;

struct gtnode{
    char data;
    int count=0;
    gtptr children[10]={null};
};

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

void input(gtptr &t)
{
    char c;
    int cnt;
    cin>>c>>cnt;
    t=new gtnode;
    t->data=c;
    t->count=cnt;
    struct queue q;
    q.enq(t);
    gtptr temp=new(gtnode);
    temp->data = '#';
    q.enq(temp);
    while(q.f!=q.r)
    {
        gtptr temp2 = q.deq();
        if(temp2->data=='#'){
            q.enq(temp);
        }
        else{
            for(int i=0;i<temp2->count;i++)
            {
                cin>>c>>cnt;
                temp2->children[i] = new gtnode;
                temp2->children[i]->data=c;
                temp2->children[i]->count=cnt;
                q.enq(temp2->children[i]);
            }
        }
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
    input(GT);
    serialize(GT);
    cout<<".";
}
// A 3 B 3 F 2 J 4 C 0 D 0 E 0 G 0 H 0 K 0 L 0 M 2 N 0 P 0 Q 0 