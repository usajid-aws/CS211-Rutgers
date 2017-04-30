#ifndef cache_init_H_
#define cache_init_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hexToBin.h"

bool isPowerofTwo(int i);


/*
 * this will create a cacheNode struct
 * header file will have all error checks from the input
 * cache blocks compnents:
 * tag
 * index
 * valid bit 0 or 1, repersented by int
 * bool to check if the block was the first one in
 */




struct cacheBlock
{ 
  int valid; 
  char * tag;
  bool first;  
  //int  index;
  uint32_t tag1;
  uint32_t index;
  int linkcount; 
  //short offset; --> not really needed cause not really accessing mem
  struct cacheBlock *next; // --> will be used if set asso. cache as LL 
};

/*
 * initialize new block
 * set blockoffset byte
 * BlockOffset = 2^n = blocksize = log2(block size) 
 * set index byte 
 * index = 2^n = (amount of sets) = log(2)(amount of sets)
 * amount of sets = cacheSize / (assoc. * blockSize)
 * remaining bits for the tag 
 * 48-bit address 
 * tag = 48 - (index + blockoffset)
 */

struct cacheBlock * makeCacheA(char *argv[], char *add, int assoc)
{ 
  int blockSize = atoi(argv[3]);
  int blockOffset = log2(blockSize); 
  int cacheSize =atoi(argv[1]);
  int totalSets = cacheSize / (blockSize*assoc);
  int index = log2(totalSets); 
  int tag  = 32 - index - blockOffset;
  int tagMask = (1 << tag) - 1;
  int tagShift = index + blockOffset;
  // use variable to make cacheBlock
  //here check for type of assoc: 
  char *mapType = argv[2];
  struct cacheBlock *b = (struct cacheBlock*)malloc(sizeof(struct cacheBlock));
  uint32_t add1 = strtol(add, NULL, 16);
  // we have a direct mapped cache 
  // in this case, set offset and tag, return cache block
  if(strcmp(mapType, "direct")==0)
  { 

    b->valid = 1;
    b->tag1 = (add1 >> tagShift) & tagMask;
    b->index =( add1 >> blockOffset) & ((1 << index) - 1); 
    //char * newTag = (char *) malloc(sizeof(char)*(tag+1));
    //strncpy(newTag, add, tag);
    //newTag[tag] = '\0';
    //b->tag = newTag;
    //char *  newIndex = (char *) malloc (sizeof(char) * (index+1)); 
    //strncpy(newIndex, add+tag+1, index);
    //newIndex[index] = '\0'; 
    //int ind = indexToInt(newIndex); 
    //b->index = ind;
    //( atoi(add) >> blockOffset) & ((1 << index) - 1);
    b->next = NULL; 

    return b; 
  }
  // if its an assoc. cache, there are no sets, just one big one, so just
  // add tag and return. 

  else if(strcmp(mapType, "assoc")==0)
  {
    b->valid = 0;
    b->index = 0;
    b->tag1 = add1 >> blockOffset; 
    b->next=NULL;
    b->linkcount=0;
    return b; 
  } 
  // now check for n-way assoc
  // will be treated like a LL, so only thing different will be a next 
  else
  {
    b->valid = 0;
    //char newTag [tag+1];
    b->tag1 = (add1 >> tagShift) & tagMask;
    b->index =( add1 >> blockOffset) & ((1 << index) - 1); 
   // strncpy(newTag, add, tag); 
   // newTag[tag] = '\0';
   // b->tag = newTag;
   // char newIndex[index+1];
   // strncpy(newIndex, add+tag, index);
   // newIndex[index] = '\0';
   // int ind = indexToInt(newIndex);
   // b->index = ind ;  
    b->next=NULL;
    b -> linkcount = 0;
    return b; 

  }

}

struct cacheBlock * makeCacheB(char *argv[], char *add, int assoc)
{
  int blockSize = atoi(argv[3]);
  int blockOffset = log2(blockSize); 
  int cacheSize =atoi(argv[1]);
  int totalSets = cacheSize / (blockSize*assoc);
  int index = log2(totalSets);  
 unsigned long int tag  = 48 - index - blockOffset; 
  // use variable to make cacheBlock
  //here check for type of assoc: 
  char *mapType = argv[2];
  struct cacheBlock *b = (struct cacheBlock*)malloc(sizeof(struct cacheBlock));
  uint32_t add1 = strtol(add, NULL, 16);
  // we have a direct mapped cache 
  // in this case, set offset and tag, return cache block
  if(strcmp(mapType, "direct")==0)
  { 

   b->valid = 0;
   add = hexToBin(add);
    char * newTag = (char *) malloc(sizeof(char)*(tag+1));
    strncpy(newTag, add+index, tag);
    newTag[tag] = '\0';
    b->tag = newTag;
    char *  newIndex = (char *) malloc (sizeof(char) * (index+1)); 
    strncpy(newIndex, add, index);
    newIndex[index] = '\0';
    int ind = indexToInt(newIndex);
    b->index = ind; 
    b->next = NULL; 

    return b; 
  }
  // if its an assoc. cache, there are no sets, just one big one, so just
  // add tag and return. 

  else if(strcmp(mapType, "assoc")==0)
  {
    b->valid = 0;
    b->index = 0;
    b->tag1 = add1 >> blockOffset; 
    b->next=NULL;
    b->linkcount=0;
    return b; 
  } 
  // now check for n-way assoc
  // will be treated like a LL, so only thing different will be a next 
  else
  {
   b->valid = 0;
   add = hexToBin(add);
    char * newTag = (char *) malloc(sizeof(char)*(tag+1));
    strncpy(newTag, add+index, tag);
    newTag[tag] = '\0';
    b->tag = newTag;
    char *  newIndex = (char *) malloc (sizeof(char) * (index+1)); 
    strncpy(newIndex, add, index);
    newIndex[index] = '\0';
    int ind = indexToInt(newIndex);
    b->index = ind; 
    b->next = NULL; 

    return b; 

  }


}


/*
 * this is for checking format of the input
 * inpur for argv[]
 * argv[1] -- cache size
 * argv[2] -- asso.
 * argv[3] -- blocksize
 * argv[4] -- tracefile
 */

bool  isCorrect(char *argv[])
{
  //cachesize has to be a poweer of two 
  int cacheSize = atoi(argv[1]); 
  if(!isPowerofTwo(cacheSize)) return false;
  //check asso. 
  //cam be direct, asso, asso-n

  if(strcmp(argv[2], "direct")!=0&&strcmp(argv[2], "assoc")!=0
      &&(!isPowerofTwo(atoi(&argv[2][6])))) return false;
  //check to see that blocksize isnt bigger that actual cach size 
  int blockSize = atoi(argv[3]);
  if(blockSize>cacheSize) return false;
  if(!isPowerofTwo(blockSize)) return false;
  if(atoi(&argv[2][6]) > cacheSize) return false;
  return true;
}


/* 
 * for checking if the input is a power of 
 * keep dividing by two to find correct input
 */ 

bool isPowerofTwo(int i)
{
  if(i==0)
    return false;

  while(i!=1)
  {
    if(i%2!=0)
      return false;
    else if(i==2) return true;
    else i=i/2;
  }
  return true;
}

char getRW(char * trace)
{ 
  int i=0;
  for(; i<strlen(trace); i++)
  {
    if(trace[i] == 'W') return 'W';
    if(trace[i] == 'R') return 'R';
  }
  printf("not read or write returning %d\n", i);
  
  exit(0);

}

int getAdd(char * trace)
{ 
  int i=0;
  for(; i<strlen(trace); i++)
  {
    if(trace[i] == 'W') return i+2;
    if(trace[i] == 'R') return i+2;
  }
  printf("not read or write returning %d\n", i);
  
  exit(0);

}

#endif
