#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//size of hashtable

#define size 10000

/*
****************************************
****************************************
              / HashTable\
****************************************
****************************************
                                        */

/*still*/


struct node
{
	int data;
	struct node *next;
	
};

struct node * hashtable[size];

void  insert(struct node *head, int data, int key)
{
	 if(head==NULL)
	 {
	 	head=(struct node *)malloc(sizeof(struct node));
	 	head->data=data;
	 	head->next=NULL;
	 	printf("inserted\n");
	 	hashtable[key]=head;
                return;
	 }




	struct node *temp;
	temp=head;

        if(temp->data==data)
       {
             printf("duplicate\n");
             return;
       }


	while(temp->next!=NULL)
	{
		if(temp->data==data)
		{
			printf("duplicate\n");
			return;
		}
			temp=temp->next;
	}
	    struct node *nxt=(struct node *)malloc(sizeof(struct node));
	    nxt->data=data;
	    nxt->next=head;
	    printf("inserted\n");
	    hashtable[key]= nxt;
            return;
	
}


bool search(struct node* head, int data)
{
	struct node* temp;
	temp=head;	
	//printf("%d\n", data);

	if(temp==NULL)
	{
		//printf("absent\n");
		return false;
	}
   
   	while(temp!=NULL)
	{   
		if(temp->data==data)
		{
			//printf("present\n");
			return true;
		}
		//printf("searching %d temp %d\n", data, temp->data );
		temp=temp->next;
	}

	//broke out and didnt find
	//printf("absent\n");
	return false;
}

int main(int argc, char const *argv[])
{
	if(argc<2)
	{
		printf("error\n");
		return 0;
	}

	
	struct node *head=NULL;

	// set all values to NULL
    int i;
	for(i=0; i<size; i++)
	{
		hashtable[i]=NULL;
	}

	FILE *fileptr=fopen(argv[1], "r");
	if(fileptr==NULL)
	{
		printf("error\n");
		return 0;
	}
    //check if file exists but empty
	fseek(fileptr, 0, SEEK_END);
    if(ftell(fileptr)==0)
    {
    	printf("\n");
    	return 0;
    }
    fseek(fileptr, 0, SEEK_SET);
    char input; int num,key; 
    while(!feof(fileptr))
    {
    	while(fscanf(fileptr,"%c %d\n", &input, &num)==2)
    	{  

    		key=num%size;
    		if(num<0)
    		{
                key=key*-1;
    		}

    		if(input=='i')
    		{
               if(hashtable[key]==NULL)
               {
               	  insert(head, num, key);
               	  // hashtable[key]=assign;
               }
               else
               {
               	      struct node *add=hashtable[key];
               	      insert(add, num, key);
               }
    		}
    		else if(input=='s')
    		{
    			if(hashtable[key]==NULL)
    			{
    				printf("absent\n");
    				continue;
    			}
    			else
    			{
    				struct node *s=hashtable[key];
    				//printf("key %d node data%d\n", key, s->data);
    				if(search(s, num))
    				{

      					printf("present\n");
      					continue;
      				}
      				else
      				{
      					printf("absent\n");
      					continue;
      				}
    			}
    		}
    		else
    		{
    			printf("error\n");
    			continue;
    		}

    	}
    }
    free(head);
	return 0;
}
