#include<iostream>
#include<cmath>
using namespace std;

int buildseg(int *s,int i,int *a,int l,int r)
{
    if(l==r){
        s[i]=a[l];
        return s[i];
    }
    int mid=(l+r)/2;
    s[i]=buildseg(s,2*i+1,a,l,mid)+buildseg(s,2*i+2,a,mid+1,r);
    return s[i];
}

int getSum(int *s,int i,int sl,int sr,int l,int r)
{
    if(sl<=l && r<=sr)return s[i];
    else if(sr<l || sl>r)return 0;
    int mid=(l+r)/2;
    return getSum(s,2*i+1,sl,sr,l,mid)+getSum(s,2*i+2,sl,sr,mid+1,r);
}

void update(int *s,int i,int l,int r,int diff,int ind)
{
    if(ind<l || ind>r)return;
    s[i]+=diff;
    if(l==r)return;
    int mid = (l+r)/2;
    update(s,2*i+1,l,mid,diff,ind);
    update(s,2*i+2,mid+1,r,diff,ind);

    // if(l>r)return;
    // if(l==r){
    //     s[i]=diff; // this diff is actually new value
    //     return;
    // }
    // int mid=(l+r)/2;
    // if(ind<=mid){
    //     update(s,2*i+1,l,mid,diff,ind);
    // }else
    //     update(s,2*i+2,mid+1,r,diff,ind);
    // s[i]=(s[2*i+1]+s[2*i+2]);
}

int main()
{
    int n;cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    int h = ceil(log(n)/log(2));
    // cout<<h++;
    h++;
    int total = (1<<h);
    cout<<" "<<total<<endl;

    //build
    int s[total]={0};
    buildseg(s,0,a,0,n-1);
    for(int i=0;i<total;i++)cout<<s[i]<<" ";
    cout<<endl;

    //query
    int sl=2,sr=4;
    cout<<getSum(s,0,sl,sr,0,n-1)<<endl;

    //update
    int old=a[3];
    a[3]=14;
    update(s,0,0,n-1,14-old,3);
    for(int i=0;i<total;i++)cout<<s[i]<<" ";
    cout<<endl;

}
//5 5 7 8 4 3

