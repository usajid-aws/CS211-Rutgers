#include "hexToBin.h"
#include "cacheRun.h"
#include "cache_init.h"

#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>




int main(int argc, char * argv[])
{

  if(argc!=5)
  {

    printf("reasonable\n");
    return 0;
  }

  int res[4] = {0};
  int res2[4] = {0};
  FILE * file = fopen(argv[4], "r");
 
  if(!isCorrect(argv))
  {
    printf("reasonable\n"); return 0;
  }  

  int assoc=0; 
  if(strcmp(argv[2], "direct")==0)
  { 
    assoc = 1;

  }
  else if(strcmp(argv[2], "assoc")==0)
  {
    assoc = atoi(argv[1]) / atoi( argv[3]) ; 
  }
  else
  {

    assoc = atoi(&argv[2][6]) ;

  }
 
  //amount of sets: cacheSize / (assoc * blockSize)
  int sets = atoi(argv[1])  / (assoc * atoi( argv[3]));
  //hashtable array to store cacheline Blocks 
  struct cacheBlock ** arr= (struct cacheBlock**) malloc(sizeof(struct cacheBlock*) * sets ); 
  struct cacheBlock ** arr2= (struct cacheBlock**) malloc(sizeof(struct cacheBlock*) * sets ); 

  int i = 0;
  for(; i<sets; i++)
  {
    arr[i] =   (struct cacheBlock *)malloc(sizeof(struct cacheBlock));
    arr[i] -> valid =0; 
    arr2[i] = (struct cacheBlock *)malloc(sizeof(struct cacheBlock)); 
    arr2[i] -> valid =0;  //NULL; 
  }



  char lineInput[50]; 
  while(fgets(lineInput, sizeof(lineInput), file))
  {

    if(strstr(lineInput, "#eof") !=NULL)
    {
      break;
    }
  
    char c = getRW(lineInput);
    int s = getAdd(lineInput);
    char * p = &lineInput[s];
   
    struct cacheBlock * blockA = makeCacheA(argv, p, assoc);
    struct cacheBlock * blockB = makeCacheB(argv, p, assoc);
   
    if(c == 'R')
    {

      cacheRead(argv, arr, blockA, res, assoc, 1);
      cacheRead(argv, arr2, blockB, res2, assoc, 2);
    }
    else if (c == 'W')
    {

     cacheWrite(argv, arr, blockA, res,assoc,1);
     cacheWrite(argv, arr2, blockB, res2,assoc,2);
 
    }
    else
    {
      printf("reasonable\n"); return 0;

    }




  }
  printf("cache A\n");
  printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", res[0], res[1],
      res[2], res[3]);
  printf("cache B\n");
  printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", res2[0], res2[1],
      res2[2], res2[3]);


  return 0;
}




