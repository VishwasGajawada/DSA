#include<iostream>
#include<cmath>
#include<climits>
using namespace std;

int min(int a,int b)
{
    return (a<b)?a:b;
}

int buildmin(int *s,int i,int *a,int l,int r)
{
    if(l==r){
        s[i]=a[l];
        return s[i];
    }
    int mid=(l+r)/2;
    s[i]=min(buildmin(s,2*i+1,a,l,mid),buildmin(s,2*i+2,a,mid+1,r));
    return s[i];
}

int getMin(int *s,int i,int sl,int sr,int l,int r)
{
    if(sl<=l && r<=sr)return s[i];
    else if(sr<l || sl>r)return INT_MAX;
    int mid=(l+r)/2;
    return min(getMin(s,2*i+1,sl,sr,l,mid),getMin(s,2*i+2,sl,sr,mid+1,r));
}

void update(int *s,int i,int l,int r,int val,int ind)
{
    if(l>r)return;
    if(l==r){
        s[i]=val;
        return;
    }
    int mid=(l+r)/2;
    if(ind<=mid){
        update(s,2*i+1,l,mid,val,ind);
    }else update(s,2*i+2,mid+1,r,val,ind);
    s[i]=min(s[2*i+1],s[2*i+2]);
}

int main()
{
    int n;cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    int h = ceil(log(n)/log(2));
    cout<<h++;
    int total = (1<<h);
    cout<<" "<<total<<endl;

    //build
    int s[total]={0};
    buildmin(s,0,a,0,n-1);
    for(int i=0;i<total;i++)cout<<s[i]<<" ";
    cout<<endl;

    //query
    int sl=1,sr=3;
    cout<<getMin(s,0,sl,sr,0,n-1)<<endl;

    //update
    a[2]=2;
    update(s,0,0,n-1,2,2);
    for(int i=0;i<total;i++)cout<<s[i]<<" ";
    cout<<endl;

}


