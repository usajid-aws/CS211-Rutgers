#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
...............................
...............................

Seventh, 
        Get abbreiviations

...............................
...............................
                                */

int main(int argc, char const *argv[]){


	if(argc<2)
	{
		printf("error\n");
		exit(0);
	}

	

	int i=1 , size=0; char ctr;

   	while(i<argc)
	  {   
		
		size=strlen(argv[i]);
		ctr=argv[i][size-1];
		printf("%c", ctr);
		i++;

	  }
    
	
	return 0;
}