#ifndef cacheRun_H_
#define cacheRun_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache_init.h"
#include "cacheInsert.h"


//will check assoc
//if direct, will go to index, if there cache hit, if not, cache miss, memRead
void  cacheRead(char *argv[],struct cacheBlock *arr[], struct cacheBlock * cache, int * res, int assoc,int type)
{

  if(strcmp(argv[2], "direct") == 0) //cache is empty at the index
  {

    struct cacheBlock * block = arr[cache -> index];
    if(block ->valid == 0)
    {
      res[0]++;
      res[3]++;
      cacheInsert(argv, arr, cache, assoc);
      return;
    }
    else //check tag
    {
      //if tags are same, cache hit, else cache miss++, memRead++
      if( block->tag1 == cache->tag1 && type ==1 )
      {    
        res[2]++; 
        return;
      }
      else if(cache->tag!=NULL && strcmp(block->tag, cache->tag) == 0&&type==2)
      {
        res[2]++;
        return;       
      }
      else
      {  
        res[0]++;
        res[3]++;
        cacheInsert(argv, arr, cache, assoc);
        return;
      }
    }

  }

  //else assoc cache
  //this means no index bits, just tag bit,
  //go through whole array and compare tags
  //if mactch tag, cache hit, if done with array, cache miss, memRead
  else if(strcmp(argv[2], "assoc")==0)
  {

    if(arr[0]->valid==0)
    {
      res[0]++;
      res[3]++;
      cacheInsert(argv, arr, cache, assoc);
      return;

    }
    struct cacheBlock * block = arr[0];
    while(block->next!=NULL)
    {
      if( block->tag1 == cache->tag1 )
      {    
        res[2]++; 
        return;
      }
      else 
      {
        block=block->next; continue;
      }

    }
      if( block->tag1 == cache->tag1 )
      {    
        res[2]++; 
        return;
      }
    else 
    {
      res[0]++;
      res[3]++;
      cacheInsert(argv, arr, cache, assoc);
      return;
    }

  }

  // else asoc:n 
  // go to index and travers LL 
  // if tag matches cache hit. not miss memRead

  else
  {

    
    struct cacheBlock * block = arr[cache -> index];
    if(block->valid == 0 ) //cache miss 
    {
      res[0]++;
      res[3]++;
      cacheInsert(argv, arr, cache, assoc);
      return;// res;
    }

    else 
    {

      while(block -> next != NULL)
      {
      if( block->tag1 == cache->tag1 && type ==1 )
      {    
        res[2]++; 
        return;
      }
      else if(cache->tag!=NULL && strcmp(block->tag, cache->tag) == 0&&type==2)
      {
        res[2]++;
        return;       
      }
        else
        {
          block = block -> next;
        }

      }
      //check last node
      if( block->tag1 == cache->tag1 && type ==1 )
      {    
        res[2]++; 
        return;
      }
      else if(cache->tag!=NULL && strcmp(block->tag, cache->tag) == 0&&type==2)
      {
        res[2]++;
        return;       
      }
      else
      {
        res[0]++;
        res[3]++;
        cacheInsert(argv, arr, cache, assoc);
        return;// res;


      }





    }
  }




}

void  cacheWrite(char *argv[],struct cacheBlock *arr[], struct cacheBlock * cache, int * res, int assoc, int type)
{

  if(strcmp(argv[2], "direct") == 0) //cache is empty at the index
  {

    struct cacheBlock * block = arr[cache -> index];
    if(block->valid ==0)
    {
      res[0]++;
      res[3]++;
      arr = cacheInsert(argv, arr, cache, assoc);
      res[1]++;
      return; 
    }
    else //check tag
    {

      //if tags are same, cache hit, else cache miss++, memRead++
      if(block->tag1 == cache->tag1&&type==1)
      {
        res[2]++;
        res[1]++; 
        return;
      }
      else if(block->tag != NULL && strcmp(block->tag, cache->tag) == 0&&type==2)
      {
        res[2]++;
        res[1]++; 
        return;
     }
      else
      {
        res[0]++;
        res[3]++;
        cacheInsert(argv, arr, cache, assoc);
        res[1]++; 
        return;
      }
    }


  }//endif

  else if(strcmp(argv[2], "assoc")==0)
  {
    if(arr[0] -> valid == 0)
    {
      res[0]++;
      res[3]++;
      arr  = cacheInsert(argv, arr, cache, assoc);
      res[1]++;
      return;

    }
    struct cacheBlock * block = arr[0];
    while(block->next!=NULL)
    {
      if(block->tag1 == cache->tag1)
      {
        res[2]++;
        res[1]++; 
        return;
      }
      else 
      {
        block=block->next; continue;
      }

    }
      if(block->tag1 == cache->tag1)
      {
        res[2]++;
        res[1]++; 
        return;
      }
    else 
    {
      res[0]++;
      res[3]++;
      arr =cacheInsert(argv, arr, cache, assoc);
      res[1]++;
      return;
    }

  }//endelsif

  else
  {
    struct cacheBlock * block = arr[cache -> index];
    if(block->valid==0) //cache miss 
    {
      res[0]++;
      res[3]++;
      cacheInsert(argv, arr, cache, assoc);
      res[1]++;
      return ;//res;
    }

    else 
    {

      while(block -> next != NULL)
      {
      if(block->tag1 == cache->tag1&&type==1)
      {
        res[2]++;
        res[1]++; 
        return;
      }
      else if(block->tag != NULL && strcmp(block->tag, cache->tag) == 0&&type==2)
      {
        res[2]++;
        res[1]++; 
        return;
     }
        else
        {
          block = block -> next;
        }

      }
      //check last node
      if(block->tag1 == cache->tag1&&type==1)
      {
        res[2]++;
        res[1]++; 
        return;
      }
      else if(block->tag != NULL && strcmp(block->tag, cache->tag) == 0&&type==2)
      {
        res[2]++;
        res[1]++; 
        return;
     }
      else
      {
        res[3]++;
        res[0]++;
        cacheInsert(argv, arr, cache, assoc);
        res[1]++;
        return;// res;

      }





    }//endelse



  }




}
#endif
