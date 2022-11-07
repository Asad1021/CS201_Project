#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
int k=1;//global variable k(dimension of the tree)
double min_dis=INFINITY;//used to find the minimum distance
double min_dis_inefficient=INFINITY;

typedef struct Node//a node of the tree
{
    int *point;//integer array that stores the point of the node 
    struct Node *left,*right;//left sub right pointer for the child of a node
}node;//renaming the struct node to node

node *nearest_point=NULL;//used to store the current nearest point.
node * nearest_point_inefficient=NULL;


double dist(int point1[],int point2[])//returns the distance between the points
{
    double distance=0;//variable to store the distance

    for (int i = 0; i < k; i++)//calculating distance squared
    {
        distance +=  (point1[i] - point2[i])*(point1[i] - point2[i]);

    }

    // distance=sqrt(distance);
    return sqrt(distance);   

}

node * allocate(void)//allocate all the memories for the node
{
    node * x = (node*) malloc( sizeof(node) );//allocating memory for the main node

    if(x==NULL)//if memory allocation fails printing the error
    {
        printf("memory Allocation failed!");
        return NULL;
    }

    x->point = (int *) malloc( k * sizeof(int) );//allocating memory for the point in the node
    if(x->point==NULL)//if memory allocation fails printing the error
    {
        printf("memory Allocation failed!");
        return NULL;
    }

    x->left=NULL;//initializing all the pointers to NULL
    x->right=NULL;

    return x;
}

node * insert(node *x,int point[],int depth)//inserts the point in the array
{
    if(x==NULL)//if the node is NULL then inserting the point in thea place
    {
        node * temp=allocate();//allocating memory for the new node

        if(temp==NULL)//if memory allocation fails returning NULL
        {
            return NULL;
        }

        for (int i = 0; i < k; i++)//copying the point into the node
        {
            temp->point[i]=point[i];
        }

        x=temp;//copying the node


        return x;               
        
    }

    if(( point[depth%k] )>( x->point[depth%k] ))//if the node is not NULL and the current dimension value is less than the point then inserting in the right
    {
        x->right=insert(x->right,point,depth+1);
    }

    else//if the node is not NULL and the current dimension value is greater than the point then inserting in the left
    {
        x->left=insert(x->left,point,depth+1);
    }
    return x;
}

void inorder(node *x)//print the inorder traversal of the tree
{
    if(x==NULL)//if the node is NULL returning
    return;

    inorder(x->left);//recursive call for inorder for the left subtree

    {//printing the point of the current node 
        printf("(");

        for (int i = 0; i < k; i++)
        {
            printf("%d%s",x->point[i] , (i<k-1)? "," : "");
        }

        printf(") ");
    }

    inorder(x->right);//recursive call for inorder for the right subtree

    return;
}

node * search(node * x,int arr[],int depth)//searches a point in the tree
{
    if (x==NULL)//returning NULL if point not found
    {
        return NULL;
    }

    if(x->point[depth%k]==arr[depth%k])//if the node is not NULL and the current dimension value is equal to the point then checking the whole point if equal returning that point else searching in the left
    
    {
        int isEqual=1;//it will be zero is the pints are nit same
        for (int i = 0; i < k; i++)
        {
            if(x->point[i]!=arr[i])
            {
                isEqual=0;
                break;
            }
        }

        if(isEqual)//if equal then returning the point
        return x;

        else //otherwise searchin in the left tree
        return search(x->left,arr,depth+1);
    }

    else if(x->point[depth%k]>arr[depth%k])//if the node is not NULL and the current dimension value is greater than the point then searching in the left
    
    {
        return search(x->left,arr,depth+1);

    }
    else //if the node is not NULL and the current dimension value is greater than the point then searching in the right
    {
        return search(x->right,arr,depth+1);
    }
}

void nearsetneighbour(node * x,int source[],int d)//searches the nearest neighour of the given point
{
    if(x==NULL) //checking node is null or not if NULL returning.
        return;
    
    else if(dist(x->point,source) < min_dis)//if the distance of the point in the node is less then the current min distance then updating the mindistance and the nearset neighour
    {
        if(dist(x->point,source)!=0)//if point is same as the source don't update the nearest
        {
            min_dis=dist(x->point,source);//updating the minimum distance
            nearest_point=x;//updating the nearest neighbour
        }
        
        nearsetneighbour(x->left,source,d+1);//recursion in left subtree
        nearsetneighbour(x->right,source,d+1); //recursion in right subtree
    }
    else if (min_dis < fabs(x->point[d%k]-source[d%k]))//if there is other section which is nearer than where the current nearest point' section then checking that section too for the nearest point
    {
        if ((x->point[d%k]-source[d%k])<0)//if d%k th dimension of the source is greater then the that of x.point then searching in the right sub tree
        {
            nearsetneighbour(x->right,source,d+1);
        }
        
        else//if d%k th dimension of the source is less then the that of x.point then searching in the left sub tree
        {
            nearsetneighbour(x->left,source,d+1);
        }     
    }
    
    else//if the distance is same the checking both sub trees
    {
        nearsetneighbour(x->left,source,d+1);
        nearsetneighbour(x->right,source,d+1);
    }
}


void in_efficient_NN(node * x,int source[])//An inefficient way of finding the nearest neighbour (doing a inorder traversal and updating the nearest point)
{
     if(x==NULL)
    return;

    in_efficient_NN(x->left,source);

    if((min_dis_inefficient>dist(x->point,source))&&((dist(x->point,source))!=0))
    {
        min_dis_inefficient = dist(x->point,source);
        nearest_point_inefficient = x;
    }

    in_efficient_NN(x->right,source);
    
    return;

}

int main()
{
    char choice;
    node *root=NULL;
    int count=1;

    loop:
    printf("\n*********************************************");
    printf("\nI: Insert a point\nF: Insert using file\nS: Search\nN: Finding nearest neighbour(Using K-D Tree)\nT: Traversal\nE: Finding Nearest neighbour(Using a naive approach)\nQ: Quit\n");
    fflush(stdin);
    scanf(" %c", &choice);
    
    switch (toupper(choice))
    {
    case 'I':
        {
            if (count)
            {
                 printf("Enter the value of K: ");
                 scanf("%d",&k);
                 count=0;
            }

            printf("Enter the element: ");
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
            printf("Enter the search element : ");
            int s[k];

            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            if((search(root,s,0))!=NULL)
            printf("Found");

            else printf("Not found");
            goto loop;

        }
    break;
    
    case 'N':
        {
            
            printf("Enter the coordinates : ");
            int s[k];
            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            nearsetneighbour(root,s,0);
            
            if (nearest_point==NULL)
            {
                printf("Can't find nearest neighbour!\n");
            }
            else
            {
                printf("{");
                for (int i = 0; i < k; i++)
                {
                    printf("%d%s",nearest_point->point[i] , (i<k-1)? "," : "");
                }
                printf("}\n");
            }
            
            min_dis=INFINITY;
            nearest_point=NULL;
            goto loop;
        }
    break;

    case 'F':
        {
            FILE * file = fopen ("Example.txt","r");//opening the file in read mode

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
                count = 0 ;
            }

            else 
            {
                int temp;
                fscanf(file,"%d",&temp);

                if(temp!=k)
                {
                    printf("Dimension of file is different with the dimension of the tree");
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
            printf("\n");
            goto loop;            
        }
    break;

    case 'Q':
        {
            return 0;         
        }
    break;

    case 'E':
    {
         printf("Enter the coordinates : ");
            int s[k];
            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            in_efficient_NN(root,s);
            
            if (nearest_point_inefficient==NULL)
            {
                printf("Can't find nearest neighbour\n");
            }
            else
            {
                printf("{");
                for (int i = 0; i < k; i++)
                {
                    printf("%d%s",nearest_point_inefficient->point[i] , (i<k-1)? "," : "");
                }
                printf("}\n");
            }
            
            min_dis_inefficient=INFINITY;
            nearest_point_inefficient=NULL;
            goto loop;

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
