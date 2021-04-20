#include <iostream>
using namespace std;
#define null NULL
typedef struct node * lptr;
typedef struct gnode * gptr;
union U
{
    int in;
    char ch;
};
struct node
{
    U data;
    int tag;
    node *next;
};
struct gnode
{
    gptr next;
    lptr link;
};

void insert(lptr &l, int tag)
{
    int n;
    char ch;
    lptr t = new node;
    if (tag == 0)
    {
        cin >> ch;
        t->data.ch = ch;
    }
    else
    {
        cin >> n;
        t->data.in = n;
    }
    t->tag = tag;
    t->next = null;
    if (!l)
    {
        l = t;return;
    }
    lptr tail = l;
    while (tail->next)
    {
        tail = tail->next;
    }
    tail->next = t;
    
}

void insert1(gptr &G,lptr L){
	gptr T,P;
	T = new gnode;
	T->link = L;
	T->next = NULL;
	if(G == null){
		G = T;
	}
	else{
		P = G;
		while(P->next){
			P = P->next;
		}
		P->next = T;
	}
}
void create_N_C(lptr L, gptr &N, gptr &C)
{ 
	if(L->tag == 1){
		insert1(N,L);
	}
	else{
		insert1(C,L);
	}
	L = L->next;
	lptr T = L;
    while (T)
    {
        if (T->next && T->tag == 1 && T->next->tag == 0)
        {
           insert1(C,T->next);
        }
        if (T->next && T->tag == 0 && T->next->tag == 1)
        {
            insert1(N,T->next);
        }
        T = T->next;
    }
}
void print_N(gptr N)
{
    if (!N) return;
    lptr L = N->link;
    while (L && L->tag==1)
    {
	    cout << L->data.in << " ";
        L = L->next;
    }
    print_N(N->next);
}
void print_C(gptr C)
{
    if (!C)return;
    lptr L = C->link;
    while (L && L->tag==0)
    {
	    cout << L->data.ch << " ";
        L = L->next;
    }
    print_C(C->next);
}
int main()
{
    int t;
    lptr L = NULL;
    cin >> t;
    while (t != -1)
    {
        insert(L, t);
        cin >> t;
    }
    gptr N = null, C = null;
    create_N_C(L, N, C);
    print_N(N);
    cout << endl;
    print_C(C);
}

// 1 5 1 7 1 2 0 C 0 S 0 E 0 A 1 8 1 6 0 N 0 W 0 T 1 9 0 B 1 4 1 5 -1
