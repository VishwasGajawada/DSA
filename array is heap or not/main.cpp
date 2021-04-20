#include <iostream>

using namespace std;

bool isminheap(int h[],int i,int n)
{
    if(i>=n)return true;
    if(2*i+1 < n && h[i]>h[2*i+1])return false;
    if(2*i+2 < n && h[i]>h[2*i+2])return false;
    return isminheap(h,2*i+1,n) && isminheap(h,2*i+2,n);
}
int main()
{
    int n;cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    cout<<isminheap(a,0,n);
    return 0;
}
//9
//1 2 7 3 10 8 6 21 5
