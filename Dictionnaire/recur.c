#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int recur(int n);
typedef struct noeud* arbre;
typedef struct noeud
{  arbre fg,fd,pere;
   int val;
}noeud;
int main()
{ 
    int n;
    scanf("%d",&n);
    printf("%d",recur(n));
}
void suppression(arbre A){
    arbre p=A->pere;
    if (A->val>p->val)
    {p->fd=NULL;
    }else{p->fg=NULL;}
    
}
void Unfils(arbre n){
    arbre p = n->pere;
    if(n->fd==NULL){
        if (n->val > p->val)
        {   p->fg = n->fg;
        }else
        {p->fd = n->fg; }
    }else{ if (n->val<p->val)
    {
       p->fg = n->fd;
    }else
    {
        p->fd = n->fd;
    }
    
    }
}
int recur(int n){
    if(n==0){ return 0;
    }else
    { return((n%2)+10*recur(n/2));   
    }
}


