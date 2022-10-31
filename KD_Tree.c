#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int k=1;

typedef struct Node{
    int *point;
    struct Node *left,*right;


}node;

double dist(int point1[],int point2[])
{
    double distance=0;
    for (int i = 0; i < k; i++)
    {
        distance +=  (point1[i] - point2[i])*(point1[i] - point2[i]);

    }

    // distance=sqrt(distance);

    return distance;   

}

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

node * nearsetneighbour(node * x,int point[],int d)
{
    if(x==NULL)
    return NULL;
    
    if(point[d%k]>(x->point[d%k]))//right node is the next
    {
        node * temp2;
        node * temp = nearsetneighbour(x->right,point,d+1);

        double distance = dist(point,temp->point);
        double distance2 = x->point[d%k] - point[d%k];

        distance2 = distance2 * distance2;

        if(distance>=distance2)
        {
            temp2 = nearsetneighbour(x->left,point,d+1);
        }

        if(dist(point,temp->point)>dist(point, temp2->point))
        {
            return temp2;
        }
        else 
        {
            return temp;
        }

    }
    else //left node is the next
    {
        node * temp2=NULL;
        node * temp = nearsetneighbour(x->left,point,d+1);
        if(temp==NULL)
        printf("hell");
        double distance = dist(point,temp->point);
        double distance2 = x->point[d%k] - point[d%k];

        distance2 = distance2*distance2;

        if(distance>=distance2)
        {
            temp2 = nearsetneighbour(x->right,point,d+1);
        }

        if(dist(point,temp->point)>dist(point, temp2->point))
        {
            return temp2;
        }
        else 
        {
            return temp;
        }

    }

}

int main()
{
    // k=3;
    // int arr[k];
    // node *root=NULL;

    // for (int i = 0; i < 2 ; i++)
    // {
    //     printf("Enter a point");
    //     for (int j = 0; j < k; j++)
    //     {
    //         scanf("%d",&arr[j]);
    //     }

        // root = insert(root,arr,0);
        
    // }
    
    // node * temp = nearsetneighbour(root,arr,0);

    // if(temp!=NULL){
    //     for (int i = 0; i < k; i++)
    //     {
    //         printf("%d ", temp->point[i]);
    //     }
    // }
    // else printf("NULL");
    // printf("\n");
    // inorder(root);
//     printf("\n");

//  int i=0;
//     while(i++<5)
//    {
    // printf("enter the search element : ");
    // int s[k];
    // for (int i = 0; i < k; i++)
    // {
    //     scanf("%d",&s[i]);
    // }

    // if((search(root,s,0))!=NULL)
    // printf("found");
    // else printf("not found");
//     }
    char choice;
    node *root=NULL;
    int count=1;

    loop:
    printf("\nI for insert a point\nF for insert using file\nS for search\nN for finding nearest neighbour\nT for traversal\nQ for quit\n");
    fflush(stdin);
    scanf(" %c", &choice);
    
    switch (choice)
    {
    case 'I':
        {
            if (count)
            {
                 printf("Enter the value of K: ");
                 scanf("%d",&k);
                 count=0;
            }

            printf("enter the element: ");
            int s[k];
            
            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            root = insert(root,s,0);
            goto loop;
        }
    break;

    case 'S':
        {
            printf("enter the search element : ");
            int s[k];

            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            if((search(root,s,0))!=NULL)
            printf("found");

            else printf("not found");
            goto loop;

        }
    break;
    
    case 'N':
        {
            goto loop;
        }
    break;

    case 'F':
        {
            FILE * file = fopen ("Example.txt","r");

            if(file==NULL)
            {
                printf("File can't be open.");
                goto loop;
            }

            int N;

            fscanf(file,"%d",&N);
            
            if(count)
            {
                fscanf(file,"%d",&k);
            }

            else 
            {
                int temp;
                fscanf(file,"%d",&temp);

                if(temp!=k)
                {
                    printf("Dimension of file is diffrent with the dimension of the tree");
                    goto loop;
                }
            }

            int s[k];

            for (int  i = 0; i < N; i++)
            {
            
                for (int i = 0; i < k; i++)
                {
                    fscanf(file,"%d",&s[i]);
                }

                root = insert(root,s,0);

                
            }

            goto loop;
            
        }
    break;
    
    case 'T':
        {
            inorder(root);
            goto loop;            
        }
    break;

    case 'Q':
        {
            return 0;         
        }
    break;


    default:
    {
        printf("Invalid input");
        goto loop;
    }
        break;
    }





    
    return 0;
}
