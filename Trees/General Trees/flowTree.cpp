#include<iostream>
using namespace std;
#define null NULL
typedef struct gtnode * gtptr;

struct gtnode{
    char data;
    int count=0;
    gtptr children[10]={null};
    int sortedIndex[10]={0,1,2,3,4,5,6,7,8,9};
    int curind=0;
};

void swap(int &a,int &b)
{
    int t=a;
    a=b;b=t;
}

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
    void clear()
    {
        while(f>=0)deq();
    }
};

int totalnodes(gtptr g)
{
    if(!g)return 0;
    int cur=0;
    for(int i=0;i<g->count;i++){
        cur+=totalnodes(g->children[i]);
    }
    return 1+cur;
}

void sort(gtptr g)
{
    for(int i=0;i<g->count;i++)
    {
        for(int j=0;j<g->count-1;j++)
        {
            if(totalnodes(g->children[g->sortedIndex[j]])<totalnodes(g->children[g->sortedIndex[j+1]]))
            swap(g->sortedIndex[j],g->sortedIndex[j+1]);
        }
    }
}

void sortAll(gtptr g)
{
    if(!g)return;
    sort(g);
    for(int i=0;i<g->count;i++)sortAll(g->children[i]);
}

void time(gtptr g)
{
    int t=0;
    queue q;
    q.enq(g);
    gtptr temp=new(gtnode);
    temp->data = '#';
    q.enq(temp);
    queue q2;
    while(q.f!=q.r)
    {
        gtptr temp2=q.deq();
        if(temp2->data=='#'){
            q.enq(temp);
            cout<<"at time "<<++t<<" ";
            while(q2.f>=0)cout<<q2.deq()->data<<" ";
            cout<<endl;
        }
        else{
            if(temp2->curind!=temp2->count)
            {
                q.enq(temp2);
                q.enq(temp2->children[temp2->sortedIndex[temp2->curind]]);
                q2.enq(temp2->children[temp2->sortedIndex[temp2->curind++]]);
            }
        }
    }
    cout<<"total time = "<<t;
}

int main()
{
    gtptr GT=null;
    char c;cin>>c;
    input(GT,c);
    cin>>c;//extra '.'
    sortAll(GT);
    time(GT);
}
//ABC.D.E..FG.H..JK.L.MP.Q..N....
//ABHN.O..I.J..C.D.EKP..LQ...F.G....