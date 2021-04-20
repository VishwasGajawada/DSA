#include <iostream>
using namespace std;
void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}

struct minHeap
{
    int h[50];
    int s=0;
    void insert(int x)
    {
        h[s]=x;
        int k = s;
        while(h[k] < h[(k-1)/2]){
            swap(h[k],h[(k-1)/2]);
            k = (k-1)/2;
        }
        s++;
    }
    int pop()
    {
        if(s<=0)return 0;
        int ans=h[0];
        h[0] = h[--s];
        int i=0;
        int l=2*i+1,r=2*i+2;
        while((l<=s && h[i] > h[l])||(r<=s && h[i] > h[r])){
            if(h[i]>h[l] && h[i]>h[r]){
                if(h[l]<h[r]){
                    swap(h[l],h[i]);i=2*i+1;
                }
                else {
                    swap(h[2*i+2],h[i]);i=2*i+2;
                }
            }
            else if(h[i]>h[l]){swap(h[2*i+1],h[i]);i=2*i+1;}
            else{swap(h[2*i+2],h[i]);i=2*i+2;}
            l=2*i+1,r=2*i+2;
        }
        return ans;
    }
    int peek()
    {
        return h[0];
    }
};

struct maxHeap
{
    int h[50];
    int s=0;
    void insert(int x)
    {
        h[s]=x;
        int k = s;
        while(h[k] > h[(k-1)/2]){
            swap(h[k],h[(k-1)/2]);
            k = (k-1)/2;
        }
        s++;
    }
    int pop()
    {
        if(s<=0)return 0;
        int ans=h[0];
        h[0] = h[--s];
        int i=0;
        int l=2*i+1,r=2*i+2;
        while((l<=s && h[i] < h[l])||(r<=s && h[i] < h[r])){
            if(h[i]<h[l] && h[i]<h[r]){
                if(h[l]>h[r]){
                    swap(h[l],h[i]);i=2*i+1;
                }
                else {
                    swap(h[2*i+2],h[i]);i=2*i+2;
                }
            }
            else if(h[i]<h[l]){swap(h[2*i+1],h[i]);i=2*i+1;}
            else{swap(h[2*i+2],h[i]);i=2*i+2;}
            l=2*i+1,r=2*i+2;
        }
        return ans;
    }
    int peek()
    {
        return h[0];
    }
};

double median(struct minHeap &minh,struct maxHeap &maxh,int x)
{
    maxh.insert(x);
    minh.insert(maxh.pop());
    if(maxh.s<minh.s){
        maxh.insert(minh.pop());
    }
    if(maxh.s==minh.s){
        return( (double)maxh.peek()+minh.peek())*0.5;
    }else return maxh.peek();
}

int main()
{
    int n;
    cin>>n;
    int a[n];
    struct minHeap m1;
    struct maxHeap m2;
    for(int i=0;i<n;i++){
        cin>>a[i];
        cout<<"median "<<median(m1,m2,a[i])<<" ";
    }
}
//7
//5 3 6 1 2 9 8
//6
//41 35 62 5 97 108
