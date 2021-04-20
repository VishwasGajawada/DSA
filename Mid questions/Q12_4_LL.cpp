#include<iostream>
#include<vector>
using namespace std;
#define null NULL

typedef struct node * lptr;
struct node{
    int data;
    lptr next;
};
void addend(lptr &p,char x)
{
    lptr t=new(node);
    t->data = x;
    t->next = null;
    if(p==null){
        p=t;return;
    }
    lptr p1=p;
    while(p1->next!=null){
        p1=p1->next;
    }
    p1->next = t;
}

lptr find(lptr l,int x)
{
    while(l)
    {
        if(l->data==x)return l;
        l=l->next;
    }
    return null;
}

lptr getTail(lptr l)
{
    if(!l)return null;
    while(l->next)
    {
        l=l->next;
    }
    return l;
}

struct stack{
    int top=-1,size=50;
    int elements[50];
    void push(int x){
        if(top==size-1)return;
        elements[++top]=x;
    }
    int pop(){
        if(top==-1)return 0;
        return elements[top--];
    }
    int peek(){
        return elements[top];
    }
};

void fun(lptr l[])
{
    stack main,temp1,temp2;
    lptr t = l[0];
    while(t)
    {
        main.push(t->data);
        t=t->next;
    }
    int order[]={1,3,4,2};
    for(int i=3;i>=0;i--)
    {
        temp1=main;
        temp2.top=-1;
        t=l[order[i]-1];
        cout<<order[i]<<" ";
        while(t)
        {
            temp2.push(t->data);
            t=t->next;
        }
        int x;
        while(temp1.peek()==temp2.peek())
        {
            x=temp1.pop();
            temp2.pop();
        }
        for(int j=0;j<i;j++)cout<<order[i]<<" ";
        cout<<x<<endl;

    }
    // for(int i=1;i<4;i++)
    // {
    //     temp1=main;
    //     temp2.top=-1;
    //     t=l[i];
    //     while(t)
    //     {
    //         temp2.push(t->data);
    //         t=t->next;
    //     }
    //     int x;
    //     while(temp1.peek()==temp2.peek())
    //     {
    //         x=temp1.pop();
    //         temp2.pop();
    //     }
    //     cout<<"l"<<i+1<<" meets l1 at "<<x<<endl;
    // }
}
int main()
{
    lptr l[4]={null};
    int n;
    cin>>n;
    while(n!=-1){
        addend(l[0],n);
        cin>>n;
    }
    for(int i=1;i<4;i++)
    {
        cin>>n;
        while(n!=-1)
        {
            lptr temp=find(l[0],n);
            if(temp){
                getTail(l[i])->next=temp;
            }else{
                addend(l[i],n);
            }
            cin>>n;
        }
    }
    fun(l);
}

// 1 2 3 5 8 27 9 36 72 -1
// 15 45 10 36 -1
// 6 18 5 -1
// 4 12 25 27 -1