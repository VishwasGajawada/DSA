#include <iostream>
#include <bits/stdc++.h>
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

void fun(int *a,int k,int n)
{
    struct minHeap m;
    for(int i=0;i<n;i++)m.insert(a[i]);

    int p = pow(2,k)-1;
    if(p<m.s)m.s=p;

    for(int i=0;i<k-1;i++){
        m.pop();
    }
    cout<<m.pop();
}

int main()
{
    int k,n;
    cin>>k>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    fun(a,k,n);

}
//3 8
//10 50 40 75 60 65 45 80
