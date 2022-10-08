//Name Shiva Koshta
//Entry No. 2021CSB1132
#include<stdio.h>
#include<stdlib.h>
int k=1;

typedef struct Node{
    int *point;
    struct Node *left,*right;

}node;

node * allocate(void)
{
    node * x = (node*) malloc( sizeof(node) );

    if(x==NULL)
    {
        printf("Memmory Allocation failed!");
        return NULL;
    }

    x->point = (int *) malloc( k * sizeof(int) );
    if(x->point==NULL)
    {
        printf("Memmory Allocation failed!");
        return NULL;
    }

    x->left=NULL;
    x->right=NULL;

    return x;
}

int deapth(node *x)
{
    if(x==NULL)
    return 0;

    return 1 + ((deapth(x->left)>deapth(x->right)) ? deapth(x->left) : deapth(x->right));

}

node * insert(node *x,int point[],int deapth)
{
    if(x==NULL)
    {
        node * temp=allocate();
        if(temp==NULL)
        {
            return NULL;
        }

        for (int i = 0; i < k; i++)//copying the point into the node
        {
            temp->point[i]=point[i];
        }

        x=temp;//can i do return temp??


        return x;               
        
    }

    if(( point[deapth%k] )>( x->point[deapth%k] ))
    {
        x->right=insert(x->right,point,deapth+1);
    }

    else
    {
        x->left=insert(x->left,point,deapth+1);
    }
    return x;
}

void inorder(node *x)
{
    if(x==NULL)
    return;

    inorder(x->left);

    {
        printf("{");

        for (int i = 0; i < k; i++)
        {
            printf("%d%s",x->point[i] , (i<k-1)? "," : "");
        }

        printf("}");
    }

    inorder(x->right);
}

node * search(node * x,int arr[],int depth)
{
    if (x==NULL)
    {
        return NULL;
    }

    if(x->point[depth%k]==arr[depth%k])
    {
        int isEqual=1;
        for (int i = 0; i < k; i++)
        {
            if(x->point[depth%k]!=arr[depth%k])
            isEqual=0;
        }

        if(isEqual)
        return x;

        else 
        return search(x->left,arr,depth+1);
        

    }
    else if(x->point[depth%k]>arr[depth%k])
    {
        return search(x->left,arr,depth+1);

    }
    else 
    {
        return search(x->right,arr,depth+1);
    }
}

int main()
{
    k=3;
    int arr[k];
    node *root=NULL;

    for (int i = 0; i < 5 ; i++)
    {
        printf("Enter a point");
        for (int j = 0; j < k; j++)
        {
            scanf("%d",&arr[j]);
        }

        root = insert(root,arr,0);
        
    }

    inorder(root);
//     printf("\n");

//  int i=0;
//     while(i++<5)
//    {
//     printf("enter the search element : ");
//     int s[k];
//     for (int i = 0; i < k; i++)
//     {
//         scanf("%d",&s[i]);
//     }

//     if((search(root,s,0))!=NULL)
//     printf("found");
//     else printf("not found");
//     }
    


    
    return 0;
}
