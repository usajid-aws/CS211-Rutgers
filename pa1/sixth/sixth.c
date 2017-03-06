#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
................................................
................................................
         Sixth Assignment CS211 Rutgers
      Make Acronym with Input from console
................................................
................................................
                                                 */   

int main(int argc, char const *argv[])
{

      if(argc<2)
      {
      	printf("error\n");
      	exit(0);
      }


      int i=1;   // will be the index printed at 
      while(i<argc)
      {
      	
      	printf("%c", argv[i][0]);
      	i++;
      }

      return 0; 

 
	
}
