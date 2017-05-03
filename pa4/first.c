#include "hexToBin.h"
#include "cacheRun.h"
#include "cache_init.h"

#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>


char * t1 = "trace.txt";
char * t2 = "trace2.txt";
char * t3 = "trace3.txt";
char * t4 = "trace4.txt";


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
  //printf("assoc: %d\n", assoc);
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
    //char  rw; 
    char c = getRW(lineInput);
    int s = getAdd(lineInput);
    char * p = &lineInput[s];
    /*if(strcmp(argv[4], "trace1.txt")==0) // || strcmp(argv[4], "trace2.txt")==0)
    {
    p = &lineInput[13];
    rw = lineInput[11];
    }      
    else 
    {
    //printf("lineInput: %s\n\n", lineInput);  
    p = &lineInput[19];
    rw = lineInput[16];
    }*/

    //printf("rw: %c\n", rw); 
    //printf("address: %s", p);
    //char * address = (char *) malloc(sizeof(char)*49);
    //address = hexToBin(p);
    struct cacheBlock * blockA = makeCacheA(argv, p, assoc);
    struct cacheBlock * blockB = makeCacheB(argv, p, assoc);
    //printf("bin: %s\n", address);
    //printf("tag: %s index: %d\n\n\n", blockA->tag, blockA->index);
     //printf("linr input: %s\n", lineInput);
   /* if(arr[0]!=NULL)
    {

      printf("arr[0] tag: %s\n", arr[0] ->tag);
    } */

    //printf("tag bits len: %zd  tag bits:%s\n", strlen(blockA->tag), blockA->tag);
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




