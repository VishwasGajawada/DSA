#include<iostream>
#include<cmath>
#include<climits>
using namespace std;

struct seg{
    int sum=0,min=0,max=0;
};

int min(int a,int b)
{
    return (a<b)?a:b;
}

int max(int a,int b)
{
    return (a>b)?a:b;
}

seg build(seg s[],int *a,int i,int l,int r)
{
    if(l==r)
    {
        s[i].sum = s[i].min = s[i].max = a[l];
        return s[i];
    }
    int mid = (l+r)/2;
    seg s1 = build(s,a,2*i+1,l,mid);
    seg s2 = build(s,a,2*i+2,mid+1,r);
    s[i].sum = s1.sum+s2.sum;
    s[i].min = min(s1.min,s2.min);
    s[i].max = max(s1.max,s2.max);
    return s[i];
}

int getElem(seg s,int tag)
{
    switch (tag){
        case 0:
            return s.sum;
        case 1:
            return s.min;
        case 2:
            return s.max;
    }
    return 0;
}

int get(seg s[],int tag,int i,int sl,int sr,int l,int r)
{
    if(sl<=l && r<=sr) return getElem(s[i],tag);
    else if(sl>r || sr<l)
    {
        if(tag==0)return 0;
        if(tag==1)return INT_MAX;
        if(tag==2)return INT_MIN;
    }
    int mid=(l+r)/2;
    int a =get(s,tag,2*i+1,sl,sr,l,mid);
    int b =get(s,tag,2*i+2,sl,sr,mid+1,r);
    if(tag==0)return a+b;
    if(tag==1)return min(a,b);
    return max(a,b);

}

void update(seg s[],int i,int l,int r,int val,int ind)
{
    if(l>r)return;
    if(l==r)
    {
        s[i].sum = s[i].min = s[i].max = val;return;
    }
    int mid=(l+r)/2;
    if(ind<=mid){
        update(s,2*i+1,l,mid,val,ind);
    }else update(s,2*i+2,mid+1,r,val,ind);
    s[i].sum = s[2*i+1].sum + s[2*i+2].sum;
    s[i].min = min(s[2*i+1].min , s[2*i+2].min);
    s[i].max = max(s[2*i+1].max , s[2*i+2].max);
}

int main()
{
    int n;cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    int h = ceil(log(n)/log(2));
    // cout<<h++;
    h++;
    int total = (1<<h); //2**h
    seg s[total];
    build(s,a,0,0,n-1);
    for(int i=0;i<total;i++)
    {
        cout<<s[i].sum<<" "<<s[i].min<<" "<<s[i].max<<endl;
    }

}
// 5 5 7 8 4 3