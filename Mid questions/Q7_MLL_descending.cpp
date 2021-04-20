#include<iostream>
using namespace std;
#define null NULL
typedef struct mlnode * mlptr;

struct mlnode{
    int data;
    mlptr down;
    mlptr next;
};
mlptr getmlTail(mlptr m)
{
    while(m->next!=null)m=m->next;
    return m;
}
void addml(mlptr &ml,int x)
{
    mlptr temp = new(mlnode);
    temp->data = x;
    temp->down = temp->next=null;
    if(ml==null){
        ml = temp;
        return;
    }
    mlptr tail = getmlTail(ml);
    tail->next = temp;
    
}
void printml(mlptr ml){
    while(ml!=null){
        cout<<ml->data<<" ";
        if(ml->down!=null){
            cout<<"(";
            printml(ml->down);
            cout<<") ";
        }
        ml=ml->next;
    }
}

struct queue{
    int f=-1,r=-1,size=100;
    mlptr elements[100];
    void enq(mlptr x){
        if((r+1)%size==f)return;
        if(f==-1){
            f=r=0;
        }else{
            r=(r+1)%size;
        }
        elements[r]=x;
    }
    mlptr deq()
    {
        if(f==-1)return null;
        mlptr t=elements[f];
        if(f==r)f=r=-1;
        else f=(f+1)%size;
        return t;
    }
    mlptr peek(){
        if(f==-1)return null;
        return elements[f];
    }
};
struct stack{
    int size=100,top=-1,elements[100];
    void push(int x){
        if(top==size-1)return;
        elements[++top]=x;
    }
    int pop(){
        if(top==-1)return 0;
        return elements[top--];
    }
};
void printsort(mlptr m){
    struct queue side,down;
    struct stack s;
    s.push(m->data);
    side.enq(m->next);
    down.enq(m->down);
    while(side.f>=0 || down.f>=0){
        mlptr temp=null,tempn=side.peek(),tempd=down.peek();
        if(tempn && tempd){
            if(tempn->data<tempd->data){
                temp=side.deq();
            }else{
                temp=down.deq();
            }
        }else if(tempd) temp=down.deq();
        else if(tempn) temp=side.deq();
        s.push(temp->data);
        if(temp->next)side.enq(temp->next);
        if(temp->down)down.enq(temp->down);
    }
    while(s.top>=0)cout<<s.pop()<<" ";
}
int main()
{
    int m,n;
    mlptr ml=null;
    cin>>m;
    while(m!=-1){
        addml(ml,m);
        cin>>n;
        mlptr temp = null;
        while(n!=0){
            addml(temp,n);
            cin>>n;
        }
        mlptr p = getmlTail(ml);
        p->down = temp;
        cin>>m;
    }
    printsort(ml);
}

// 3 8 15 0 7 12 45 0 10 18 72 0 36 0 -1
