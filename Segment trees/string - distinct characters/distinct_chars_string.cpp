#include<iostream>
using namespace std;

string uniq(string a,string b)
{
    string s="";
    int count[26]={0};
    for(int k=0;k<a.length();k++)
    {
        if(count[a[k]-'a']==0) s+=a[k];
        count[a[k]-'a']++;
    }
    for(int k=0;k<b.length();k++)
    {
        if(count[b[k]-'a']==0) s+=b[k];
        count[b[k]-'a']++;
    }
    return s;
}

string build(string seg[],string s,int i,int l,int r)
{
    if(l==r)
    {
        seg[i]+=s[l];
        return seg[i];
    }
    int mid = (l+r)/2;
    string a = build(seg,s,2*i+1,l,mid),b=build(seg,s,2*i+2,mid+1,r);
    seg[i]=uniq(a,b);
    return seg[i];
}

string get(string seg[],int i,int sl,int sr,int l,int r)
{
    if(sl<=l && r<=sr)return seg[i];
    if(sl>r || sr<l)return "";
    int mid = (l+r)/2;
    string a = get(seg,2*i+1,sl,sr,l,mid);
    string b = get(seg,2*i+2,sl,sr,mid+1,r);
    return uniq(a,b);
}

void update(string seg[],int i,int l,int r,int ind,char val)
{
    if(l>r)return;
    if(l==r)
    {
        seg[i]="";
        seg[i]+=val;return;
    }
    int mid = (l+r)/2;
    if(ind<=mid) update(seg,2*i+1,l,mid,ind,val);
    else update(seg,2*i+2,mid+1,r,ind,val);
    seg[i] = uniq(seg[2*i+1],seg[2*i+2]);
}

int main()
{
    string s="";
    char c;cin>>c;
    while(c!='#')
    {
        s+=c;cin>>c;
    }
    int n=s.length();
    string seg[4*n]={""};
    build(seg,s,0,0,n-1);
    // int sl=1;
    // int sr=6;
    update(seg,0,0,n-1,6,'e');
    update(seg,0,0,n-1,4,'b');
    cout<<get(seg,0,6-1,14-1,0,n-1);
}
// dfcbbcfeeedbaea#