#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*******************
 *     Second      *
 *   Linked List   *
 *                 *
 *******************/

typedef struct node
{
	int data; 
	struct node *next;

}Node;

struct node* insert(struct node **head, int i);
struct node*delete(struct node **head, int i);

/*
Globals: 

*/

struct node* head;
int val[50];
int q=0;


struct node* insert(struct node **head, int i){

	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=i;
    int count=0;
    int s;
	//printf(" value %d\n",  (*head)->data);
    for(s=0; s<q; s++)
    {
    	if(val[s]==i)
    	{   //printf("asdsad\n");	
    		count++;
    	}
    }
    if(count>1)
    {
    	return *head;
    }
	if((*head)->data>i)
	{
            	//printf("herer\n");
		(*temp).next=*head;
		*head=temp;
		return *head;

	}

	if((*head)->data==i)
	{
		return *head;
	}

	else
	{   
		struct node* ptr=*head;
		while((*ptr).next!=NULL)
		{

			if((*ptr).data==i)
			{  
				return *head;
			}



			if(ptr->next!=NULL&&ptr->next->data > i)
			{ 
			    
			     (*temp).next=(*ptr).next;
				 (*ptr).next=temp;
				 return *head;
			    
			}
			ptr=(*ptr).next;
		}
		(*ptr).next=temp;
	    
		return *head;
	}




            //free(temp);
            //return *head;;


}





struct node * delete(struct node** head, int i ){
    
   // printf("delete %d\n", i );
	int t;
	int count=0;
	for(t=0; t<q; t++)
	{
		if(val[t]==i)
		{
			count++;
		}
	}
	if(count==0)
	{
		//printf("11111111111error\n");
		return *head;
	}
       // printf("%d count", count);	
	struct node *ptr=*head;
	if(ptr==NULL)
	{
		return NULL;
	}
   

	if(ptr->data==i)
	{
		*head=(*head)->next;
		free(ptr);
		return *head;
	}
	else
	{  
		while(ptr!=NULL && (ptr->next!=NULL)  && (ptr->next->data!=i) )
		{ 
			ptr=ptr->next;
		}
		if(ptr==NULL)
		{
			return *head;
		}
		else
		{ 
		    if(ptr->next!=NULL)
		    { 
			struct node* erase=ptr->next;
			ptr->next=(*erase).next;
			//printf("din sdasd %d\n", erase->next->data  );
			free(erase);
		    }
			return *head;
		}

		

	}
	//printf("error\n");
}
	
	

		
	




int main(int argc, char **argv)
{
          
	if(argc<2 )
	{
		printf("error\n");
		exit(0);
	} 
	
    //printf("%s\n", argv[1] );
    
    //printf("%s\n", input );
	FILE *fileptr=fopen(argv[1] ,"r");

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
	
   // fseek(fileptr, 0 , SEEK_CUR);
   
    //fseek(fileptr, 0 , SEEK_SET);
	//char word[500]; 
	//char *check;
	head=NULL;
	//int add;

	int input;
	char ch;

	while(!feof(fileptr))
	{
		fscanf(fileptr, "%c\t%d\n", &ch, &input);
		
		
			if(ch=='i')
		{
				if(head==NULL)
			 {   
				Node *temp=(Node *)malloc(sizeof(Node));
				temp->data=input;
				head=temp;
				//printf("heads data new, %d\n", head->data );
                                val[q]=input;
                                q++;
				continue;
			 }
			 else
			 {
                                val[q]=input;
                                q++;
			 	head=insert(&head, input);
			    //printf("heads data after , %d\n", head->data );
			     continue;
			 }
		}
			 else if(ch=='d')
		 {
			 	if(head==NULL)
			   {
				//printf("error\n");
				continue;
			   }
                           else
                           {
			     head=delete(&head, input);
			     continue;
                           }
		 }
			 else
		 {
			 	printf("error\n");
			 	exit(0);
		 }
			
		
	}
	
	/*while((fgets(word, 500, fileptr))!=NULL)
	{
		check=strtok(word, "\t");
		int ret1=strcmp(check,"i");
		int ret2=strcmp(check,"d");

			printf("error\n");
			
			return 0;
		}
		check=strtok(NULL, "\t");
		
		if(!isdigit(*check))
		{
			printf("error\n");
			return 0;
		}
		add=atoi(check);
		val[q]=add;
        q++;
		
		
		if(ret1==0) 
		{   
			if(head==NULL)
			{   
				Node *temp=(Node *)malloc(sizeof(Node));
				temp->data=add;
				head=temp;
				//printf("heads data new, %d\n", head->data );

				continue;

			}
			//printf("calling f head: %d adding: %d\n", head->data , add);
			head=insert(&head, add);
			//printf("heads data after , %d\n", head->data );
			continue;
		}
		if (ret2==0)
		{
			if(head==NULL)
			{
				//printf("error\n");
				continue;
			}
			head=delete(&head, add);
			continue;
		}
		
         

	}*/
	        if(head==NULL)
	        {
	        	printf("\n");
	        	return 0;
	        }
	struct node* ptr=head;
        //printf("\n");
	while(ptr->next!=NULL)
	{
		printf("%i\t", ptr->data );
		ptr=(*ptr).next;
	}
        printf("%i", ptr->data );
        free(ptr);
	

        fclose(fileptr);
	return 0;


}

