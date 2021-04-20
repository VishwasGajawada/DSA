#include<bits/stdc++.h>
using namespace std;

struct node{
    int x=-1,y=-1,z=-1;//parent
    int ind[3]={0};
};

struct node create(int indx,int indy,int indz){
    struct node temp;
    // temp.x=x;temp.y=y;temp.z=z;
    temp.ind[0]=indx;temp.ind[1]=indy;temp.ind[2]=indz;
    return temp;
}
void add(node g[9][6][4],int visit[9][6][4],queue<node>&q,node cur,node child){
    int curx=cur.ind[0],cury=cur.ind[1],curz=cur.ind[2];
    int newx=child.ind[0],newy=child.ind[1],newz=child.ind[2];
    visit[newx][newy][newz]=1;
    g[newx][newy][newz].ind[0]=newx;
    g[newx][newy][newz].ind[1]=newy;
    g[newx][newy][newz].ind[2]=newz;
    g[newx][newy][newz].x=curx;
    g[newx][newy][newz].y=cury;
    g[newx][newy][newz].z=curz;
    q.push(g[newx][newy][newz]);
}
bool check(node g[9][6][4],node cur){
    if(cur.ind[0]!=4 && cur.ind[1]!=4 && cur.ind[2]!=4)return false;
    stack<node> s;
    while(cur.x!=-1 && cur.y!=-1 && cur.z!=-1){
        s.push(cur);
        int parx = g[cur.ind[0]][cur.ind[1]][cur.ind[2]].x;
        int pary = g[cur.ind[0]][cur.ind[1]][cur.ind[2]].y;
        int parz = g[cur.ind[0]][cur.ind[1]][cur.ind[2]].z;
        cur = g[parx][pary][parz];
    }
    cout<<"now answer"<<endl;
    cout<<"8 0 0"<<endl;
    while(!s.empty()){
        cur=s.top();s.pop();
        cout<<cur.ind[0]<<" "<<cur.ind[1]<<" "<<cur.ind[2]<<endl;
    }
    return true;
}

void func(struct node g[9][6][4]){
    queue<node> q;
    q.push(create(8,0,0));
    int visit[9][6][4];
    for(int i=0;i<=8;i++)for(int j=0;j<=5;j++)for(int k=0;k<=3;k++)visit[i][j][k]=0;
    visit[8][0][0]=1;
    while(!q.empty()){
        node cur=q.front();q.pop();
        if(check(g,cur))break;//for only one path
        // if(check(g,cur));//for all paths
        int curx=cur.ind[0],cury=cur.ind[1],curz=cur.ind[2];
        // cout<<curx<<" "<<cury<<" "<<curz<<endl;
        int qty=0;
        if(curx>0){
            int newx,newy,newz;
            //x to y
            qty = curx > (5 - cury) ? 5 - cury : curx;
            newy = cury + qty;
            newx = curx - qty;
            newz = curz;
            if(visit[newx][newy][newz]==0){
                add(g,visit,q,create(curx,cury,curz),create(newx,newy,newz));
            }
            //x to z
            qty = curx > (3 - curz) ? 3 - curz : curx;
            newz = curz + qty;
            newx = curx - qty;
            newy = cury;
            if(visit[newx][newy][newz]==0){
                add(g,visit,q,create(curx,cury,curz),create(newx,newy,newz));
            }
        }
        if(cury>0){
            int newx,newy,newz;
            //y to x
            qty = cury > (8 - curx) ? 8 - curx : cury;
            newx = curx + qty;
            newy = cury - qty;
            newz = curz;
            if(visit[newx][newy][newz]==0){
                add(g,visit,q,create(curx,cury,curz),create(newx,newy,newz));
            }
            //y to z
            qty = cury > (3 - curz) ? 3 - curz : cury;
            newz = curz + qty;
            newy = cury - qty;
            newx = curx;
            if(visit[newx][newy][newz]==0){
                add(g,visit,q,create(curx,cury,curz),create(newx,newy,newz));
            }
        }
        if(curz>0){
            int newx,newy,newz;
            //z to y
            qty = curz > (5 - cury) ? 5 - cury : curz;
            newy = cury + qty;
            newz = curz - qty;
            newx = curx;
            if(visit[newx][newy][newz]==0){
                add(g,visit,q,create(curx,cury,curz),create(newx,newy,newz));
            }
            //z to x
            qty = curz > (8 - curx) ? 8 - curx : curz;
            newx = curx + qty;
            newz = curz - qty;
            newy = cury;
            if(visit[newx][newy][newz]==0){
                add(g,visit,q,create(curx,cury,curz),create(newx,newy,newz));
            }
        }
    }
}
int main(){
    struct node g[9][6][4];
    func(g);
}
