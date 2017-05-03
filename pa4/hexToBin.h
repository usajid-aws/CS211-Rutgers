#ifndef hexToBin_H_
#define hexToBin_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char bin[48];
char *  hexToBin(char *hex)
{
 
  
 // char * bin = (char *) malloc (sizeof(char)*48); 
  int len = strlen(hex);
  int i = 0; bin[0]='\0';
  for(i=0; i<48-(4*(len-3)); i++)
  {

    strcat(bin, "0");
  }
  for(i=2; i<strlen(hex); i++)
  {
    switch(hex[i])
    {
      case '0':
        strcat(bin, "0000");
        break;
      case '1':
        strcat(bin, "0001");
        break;
      case '2':
        strcat(bin, "0010");
        break;
      case '3':
        strcat(bin, "0011");
        break;
      case '4':
        strcat(bin, "0100");
        break;
      case '5':
        strcat(bin, "0101");
        break;
      case '6':
        strcat(bin, "0110");
        break;
      case '7':
        strcat(bin, "0111");
        break;
      case '8':
        strcat(bin, "1000");
        break;
      case '9':
        strcat(bin, "1001");
        break;
      case 'a':
      case 'A':
        strcat(bin, "1010");
        break;
      case 'b':
      case 'B':
        strcat(bin, "1011");
        break;
      case  'c':
      case 'C':
        strcat(bin, "1100");
        break;
      case 'd':
      case 'D':
        strcat(bin, "1101");
        break;
      case 'e':
      case 'E':
        strcat(bin, "1110");
        break;
      case 'f':
      case 'F':
        strcat(bin, "1111");
        break;
      default:
        continue;
    }
  }
  return bin;


}

int indexToInt(char * index)
{

  int result = 0;
  int len = strlen(index)-1; 
  int i=0;
  for(; i<strlen(index); i++)
  {
    if(index[i] == '0')
    {
       len--; continue;
    }
    result += pow(2, len);
    len--;
  }
 // printf("input: %s\n" ,index);
  // printf("output: %d\n\n", result);
  return result;

}


#endif
