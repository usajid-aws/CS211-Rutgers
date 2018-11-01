#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char const *argv[])
{


	if(argc<2)
	{
		printf("error\n");
		return 0;
  }
  int range = atoi(argv[1]);
  int i; 
  int upper = 100;
  int lower = -100;
  int total = 0;
  srand(time(0));
  for (i = 0; i < range; i++) 
  { 
    int num = (rand() % (upper - lower + 1)) + lower; 
    printf("%d \n", num);
    total += num;
  } 
   printf("total: %d ", total);
   return 0;
}
