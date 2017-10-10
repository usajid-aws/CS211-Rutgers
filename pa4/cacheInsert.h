#ifndef cacheInsert_H_
#define cacheInsert_H_ 

#include <stdio.h>
#include <stdlib.h>
#include "cache_init.h"


//for direct-mapped cache, check at index
//if there remove and add, else just add
//
//for assoc, just add at next empty spot
//
//for n-way, check linkcount, if == blockSize, kick out first, else add to end of LL 
struct cacheBlock** cacheInsert(char * argv[], struct cacheBlock * arr[], struct cacheBlock * cache, int assoc)
{

  cache->valid=1;
   if(strcmp(argv[2], "direct")==0)
  {
    
    arr[cache->index] = cache; return arr; 

  }

  else if (strcmp(argv[2], "assoc")==0)
  {
    if(arr[0] -> valid == 0 )
    {
     
      cache -> linkcount=1;
      arr[0] = cache;
      return arr;
       
    }

    struct cacheBlock * temp = arr[0];
    if(temp->linkcount < ( atoi(argv[1]) / atoi(argv[3]) ) )  
    { 
      temp->linkcount++;
      while(temp->next!=NULL)
      {
        temp = temp->next;
      }
      temp->next = cache; 
      return arr;
    }
    else
    {
      temp = temp->next;
      temp->linkcount = (atoi(argv[1]) /  atoi(argv[3]) ) ;
      arr[0] = temp;
      arr[0] -> valid = 1;
      while(temp->next!=NULL)
      {
        temp = temp->next;
      }
      temp->next = cache; 
      return arr;
    }


  }


  else
  {
    struct cacheBlock * b = arr[cache->index];
    if(b->valid == 0)
    { 
      cache->valid = 1;
      cache->linkcount=1;      
      arr[cache->index]=cache;
      return arr;
    }
    if(b -> linkcount < atoi(&argv[2][6]) )
    {
      b->linkcount++;
      while(b->next!=NULL)
      {
        b=b->next;
      }
      b->next=cache;
     
      return arr;
    }
    else // if index LL is == blockSize
    {
      b = b->next;
      b -> linkcount = atoi(&argv[2][6]);
      arr[cache->index] = b;
      arr[cache->index]->valid = 1;
      //at this point, that cacheblock will remain full, remove one add one 
      while(b->next!=NULL)
      {
        b=b->next;
      }
      b->next=cache;
      
      return arr; 
    }
  }





  return arr;



#endif

}
