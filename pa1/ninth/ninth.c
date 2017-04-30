#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//void insert(struct node *root, int data);


struct node
{
	int data;
	struct node *left;
	struct node *right;
	
};

/*goes through tree 
 *checks children and get parent of target
 *Helper for delete
 *
 */

int getRep(struct node* root)
{
   int i=10000;
   struct node *temp=root;
   while(temp!=NULL)
  {
    if(temp->data<i)
    {
      i=temp->data;
    }
    temp=temp->left;
  }  
    return i;
}

void selfDestruct(struct node* root)
{
      if(root==NULL)
      return;
      selfDestruct(root->left);
      root->left=NULL;
      selfDestruct(root->right);
      root->right=NULL;
      free(root); 
      root=NULL; return;
}


struct node* getPar(struct node* root, int data)
{
      if(root==NULL)
      {
      	return NULL;
      }

      else if(root->left->data==data||root->right->data==data||root->left==NULL||root->right==NULL)
      {
      	return root;
      }
      else if(root->data < data)
      {
      	getPar(root->right, data);
      }
      else
      {
      	getPar(root->left, data);
      }

      return root;
}

/*
3 Cases:
a) No child, just delete the node and free (leaf node)

b)one child, parents child becomes child's child

c)two children: get smallest node from right subtree, replace value from target, and delete diplicate
*/

struct node *  delete(struct node* root, int data)
{
	if(root==NULL)
	{
		printf("fail\n");
		return NULL;
	}
        
        if(root->data==data)
        {
                if(root->right==NULL&&root->left==NULL)
                {
                   //case one 
                   struct node* del=root;
                   root=root->right;
                   free(del);
                   printf("success\n");
                   return root;
                }
                else if(root->left==NULL)
                {
                      //  struct node *par=getPar(root, data);
                      struct node *del=root;
                      root=(*root).right;
                      free(del);
                      printf("success\n");
                      return root; 
                }  
                else if(root->right==NULL)
                {
                      struct node*del = root;
                      root=root->left;
                      free(del);
                      printf("success\n");
                      return root;
                }
                else
                {
                      //case 3 : two children
                      root->data=getRep(root->right);
                      //remove duplicate
                      root->right=delete(root->right, root->data);
                      return root;
                }
          
         } 
         else if(root->data<data)
         {
                root->right= delete(root->right, data);
         }
         else
         {
                 root->left=delete(root->left, data);
         }
                  
                // printf("fail\n");
                 return root;

} 

void search(struct node* root, int data, int ht)
{
	if(root==NULL)
	{
		printf("absent\n");
		return;
	}
	else if(root->data==data)
	{
		printf("present %d\n", ht + 1);
		return;
	}
	else if(root->data < data)
	{
		search(root->right, data, ht+1);
	}
	else
	{
		search(root->left, data, ht+1);
	}
}




struct node* insert(struct node *root, int data, int ht)
{
	
	if(root==NULL)
	{
		root=(struct node*)malloc(sizeof(struct node));
		(*root).data=data;
		root->left=NULL;
        root->right=NULL;
        ht++;
        printf("inserted %d\n", ht );
        return root;

	}
	else if (root->data == data)
	{
		   printf("”duplicate\n");
           
	}

	else if(root->data < data)
	{
		(*root).right = insert(root->right, data, ht+1 );
	}
	else
	{
		(*root).left = insert(root->left, data, ht+1);
	}

	return root;



}


int main(int argc, char const *argv[])
{
      struct node *root=NULL;
      

	if(argc<2)
	{
		printf("error\n");
		exit(0);
	}
	FILE *fileptr=fopen(argv[1],"r");

	if(fileptr==NULL)
	{
		printf("error\n");
		return 0;
	}
         fseek(fileptr, 0, SEEK_END);
    if(ftell(fileptr)==0)
    {
    	printf("\n");
    	return 0;
    }
    fseek(fileptr, 0, SEEK_SET);
	

	char choice; int input;  
	while(!feof(fileptr))
	{
		fscanf(fileptr, "%c %d\n", &choice, &input);
		if(choice=='i')
		{
			root=insert(root, input, 0);
		}
		else if(choice=='s')
		{
			search(root, input, 0);
		}
		else if(choice=='d')
		{
			if(root->left==NULL&&root->right==NULL)
			{
				if(root->data==input)
				{
					free(root);
                                        root=NULL;
					printf("success\n");
					continue;
				}
				else
					continue;
			}
			else
			root=delete(root, input);
		}
		else 
		{
			printf("error\n");
			exit(0);
		}

	}


    fclose(fileptr);
    selfDestruct(root);
	return 0;
}
