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
		   printf("duplicate\n");
		   return root;
           
	}

	else if(root->data < data)
	{
		(*root).right = insert(root->right, data, ht+1 );
	}
	else
	{
		(*root).left= insert(root->left, data, ht+1);
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
