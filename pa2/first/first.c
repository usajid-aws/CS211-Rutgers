#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


struct node 
{
	int occ,  super;  bool endOfWord;  
	struct node * ch[26]; char * word; 
};


//Globals 
struct node *root; int lscount=0;

struct node * structIt()
{
	struct node *node=(struct node *)malloc(sizeof(struct node));
	int i;
	for(i=0; i<26; i++)
	{
		node->ch[i]=NULL;
	}
	node->endOfWord=false; node->word=NULL; 
	node->occ=0; node->super=0; return node; 
}
// This function gets the index at which the letter will go in the children array

int getHash(char c)
{
	switch(c)
	{
		case 'a':return 0; case 'b':return 1; case 'c':return 2; case 'd':return 3; case 'e':return 4;
		case 'f':return 5; case 'g':return 6; case 'h':return 7; case 'i':return 8; case 'j':return 9;
		case 'k':return 10; case 'l':return 11; case 'm':return 12; case 'n':return 13; case 'o':return 14;
		case 'p':return 15; case 'q':return 16; case 'r':return 17; case 's':return 18; case 't':return 19;
		case 'u':return 20; case 'v':return 21; case 'w':return 22; case 'x':return 23; case 'y':return 24;
		case 'z':return 25;

	}
	return 0;
}
// this function will return a char given an int
// for getting char by char when traversing tree
char  reverseHash(int i)
{
	switch(i)
	{
		case 0:return 'a'; case 1:return 'b';  case 2:return 'c'; case 3:return 'd'; case 4:return 'e';
		case 5:return 'f'; case 6:return 'g'; case 7:return 'h'; case 8:return 'i'; case 9:return 'j';
		case 10:return 'k'; case 11:return 'l'; case 12:return 'm'; case 13:return 'n'; case 14:return 'o';
		case 15:return 'p'; case 16:return 'q'; case 17:return 'r'; case 18:return 's'; case 19:return 't';
		case 20:return 'u'; case 21:return 'v'; case 22:return 'w'; case 23:return 'x'; case 24:return 'y';
		case 25:return 'z';

	}
	return 0;
}

void printMe(struct node * root, FILE * outfile)
{

	if(root==NULL) return;
	if(root->endOfWord)
	{
		char s[strlen(root->word)+1];
		int i;
		for(i=0; i<strlen(root->word); i++)
		{
			if(isalpha(root->word[i]))
			{
				s[i]=root->word[i];
			} else break;
		}
		s[i]='\0';

		fprintf(outfile,"%s %d %d\n", s, root->occ, root->super);
	}

	int i;
	for(i=0; i<26; i++)
	{
		printMe(root->ch[i],outfile); 

	}

}

void printResult()
{

	FILE * outfile; char out[90];
	sprintf(out, "out%d.txt", lscount);
	outfile=fopen(out, "w");
	printMe(root, outfile);
	fclose(outfile); 
}

//will add to trie
//will traverse trie till end of word and add char by char in 
//appropraite locations

void addToTrie(char * word)
{	int i; if(root==NULL)return;  
	word[strlen(word)]='\0'; 
	struct node *temp=root; 
	for(i=0; i<strlen(word); i++)
	{
		int hashPoint=getHash(word[i]);
		if(temp->ch[hashPoint]==NULL)// Empty spot in in childern array
		{      
			struct node* add=structIt();
			temp->ch[hashPoint]=add;
			temp=add; continue;
		}
		else //char for that point already exists, so move temp down
		{
			temp=temp->ch[hashPoint]; continue;
		}
	}
	temp->endOfWord=true; int s=strlen(word);
	temp->word=(char *)malloc(sizeof(char)*(s)+1);// memcpy(temp->word, word, strlen(word));
	strcpy(temp->word, word);
	//strncpy(temp->word, word, sizeof(word)+1);
}
//will traverse trie, 
//will hit end of word
//if the word is a complete word, occ++, else super++

void matchStr( struct node * root, char * word)
{

	struct node * p=root;
	int i; 
	for(i=0; i<strlen(word);i++)
	{
		int hash=getHash(word[i]);
		if(p->ch[hash]==NULL)break;
		if(p->word)
		{
			if(strncmp(p->word, word, strlen(p->word))==0)
			{
				p->super++;
				p=p->ch[hash];
			} 
			else if(p->endOfWord)
			{
				p->occ++;
				p=p->ch[hash];
			}
		}
		else
		{
			p=p->ch[hash];
		}
	}
	if(p->word&&word[i]=='\0')
	{      p->occ++;
	}
	else if(p->word)
	{       
		p->super+=1; 
	} 
}
void readData(FILE * data)
{

	int twcount=0; char c; char this_word[1000];
	while(!feof(data))
	{
		fscanf(data, "%c", &c);
		if(c==EOF){break;} //c>='a'&&c<='z')||(c>='A'&&c<='Z')
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
		{       
			this_word[twcount]=tolower(c);
			twcount++;// temp->wrdlen++;
		}
		else
		{
			if(twcount==0)
			{
				continue; //first char was a not alpha
			}
			else
			{
				//we  have a complete word, add it to trie

				// char * update=(char *)malloc(sizeof(char)*twcount);
				// strncpy(update,this_word, sizeof(this_word)+1);//get rid of junk values at end 
				matchStr(root,this_word); twcount=0;// printf("%s\n", update);
				memset(this_word, 0, strlen(this_word)); // free(update);
				twcount=0;

			}
		}
	}
}
void readDict(FILE * dict)
{
	int twcount=0; char c; char this_word[1000];
	while(!feof(dict))
	{
		fscanf(dict, "%c", &c);
		if(c==EOF){break;}
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
		{       
			this_word[twcount]=tolower(c);
			twcount++;// temp->wrdlen++;
		}
		else
		{
			if(twcount==0)
			{
				continue; //first char was a not alpha
			}
			else
			{
				//we have a complete word, add it to trie
				//printf("before %s\n", this_word) ;
				this_word[twcount+1]='\0'; 
				//printf("aft:  %s\n", this_word) ;
				addToTrie(this_word); twcount=0;// free(add);
				memset(this_word, 0, strlen(this_word));

			}
		}
	}
}
//function to tell if file exists, but is empty
bool isEmpty(FILE * file)
{
	fseek(file, 0, SEEK_END);
	if(ftell(file)==0)
	{
		return true;
	}
	else
	{
		fseek(file, 0 , SEEK_SET);
		return false;
	}
}


void killIt(struct node * root)
{
	int i; 
	if(root==NULL)return;
	for(i=0; i<26; i++)
	{
		killIt(root->ch[i]);
	}
	if(root->endOfWord) free(root->word);
	free(root);
}

int  main(int argc, char** argv)
{
	if(argc<2)
	{
		printf("invalid input\n");
		exit(0);
	}

	FILE *map, *dict, *data;
	char d1[1000], d2[1000];
	map=fopen(argv[1], "r");
	if(map==NULL)
	{
		printf("invalid input\n"); exit(0);
	}

	while(!feof(map))
	{
		fscanf(map, "%s %s \n", d1, d2);
		dict=fopen(d1, "r"); data=fopen(d2, "r");
		root=NULL;
		if(dict==NULL||isEmpty(dict))
		{
			printf("invalid input\n"); exit(0);
		}
		else
		{
			if(root==NULL)
			{
				root=structIt();
				readDict(dict);
			}
			else readDict(dict);
		}//endelsefordict
		if(data==NULL) 
		{
			printf("invalid input\n"); exit(0);

		}
		else if(isEmpty(data))
		{
			lscount++; printResult(); continue;
		}

		else
		{
			readData(data); lscount++; 
			printResult();
			killIt(root);    
		}

	} 
	return 0;
}
