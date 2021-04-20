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
    int h[50]={0};
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
        h[0] = h[s-1];
        s--;
        int i=0;
        int l=2*i+1,r=2*i+2;
        while((l<=s)||(r<=s)){
            int small=i;
            if(l<=s && h[small]>h[l])small=l;
            if(r<=s && h[small]>h[r])small=r;
            if(small!=i)swap(h[small],h[i]);
            if(small==i)break;
            i=small;
            l=2*i+1,r=2*i+2;
        }
        return ans;
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
        while((l<=s)||(r<=s)){
            int large=i;
            if(l<=s && h[large]<h[l])large=l;
            if(r<=s && h[large]<h[r])large=r;
            if(large!=i)swap(h[large],h[i]);
            if(large==i)break;
            i=large;
            l=2*i+1,r=2*i+2;
        }
        return ans;
    }
};

int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    struct minHeap m1;
    for(int i=0;i<n;i++){
        m1.insert(a[i]);
    }
    int h1sort[n];
    for(int i=0;i<n;i++)
    {
        h1sort[i]= m1.pop();
    }
    for(int i=0;i<n;i++)cout<<h1sort[i]<<" ";

}
//9
//1 2 7 3 10 8 18 21 5
//9
//5 9 3 6 2 4 8 1 7
