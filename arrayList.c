#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);

arrayList * initialize(primitiveType type)
{
    arrayList * newList = malloc(sizeof(arrayList));
    newList->elementSize = getSize(type);
    newList->numElements = 0;
    newList->arraySize = 10;
    newList->type = type;
    return newList;
}

int getSize(primitiveType type)
{
    if(type == shortType)
        return sizeof(short);
    else if(type == charType)
        return sizeof(char);
    else if(type == intType)
        return sizeof(int);
    else
        return 0;
}

void addElement(arrayList * arylstP, void * element)
{
    if(arylstP->numElements >= arylstP->arraySize)
    {
        char * newArray = malloc((sizeof(getSize(arylstP->type)) *2) *arylstP->numElements);
        int i;
        for(i = 0; i < (arylstP->elementSize*arylstP->numElements); i++)
        {
            newArray[i] = ((char*)arylstP->array)[i];
        }
        free(arylstP->array);
        arylstP->array = newArray;
        arylstP->arraySize *= 2;
    }
    if(arylstP->type == intType)
    {
        ((int*)arylstP->array)[arylstP->numElements] = *((int*)element);
    }
    else if(arylstP->type == charType)
    {
        ((char*)arylstP->array)[arylstP->numElements] = *((char*)element);
    }
    else if(arylstP->type == shortType)
    {
        ((short*)arylstP->array)[arylstP->numElements] = *((short*)element);
    }
    arylstP->numElements++;
}

void removeElement(arrayList * arylstP, int index)
{
   if(index < 0 || index > arylstP->arraySize)
       return;

   int i;
   for(i = index; i < arylstP->arraySize - 1; i++)
   {
      // arylstP->array[i] = arylstP->array[i+1];
   }
   arylstP->arraySize--;
}
      

void printArray(arrayList * arylstP)
{
   int i;
   printf("array size: %d, num elements: %d contents: ", 
          arylstP->arraySize, arylstP->numElements);
   for (i = 0; i < arylstP->numElements; i++)
   {
      if (arylstP->type == charType)
         printf("%02x ",(((char*)arylstP->array)[i])& 0xff);
      else if (arylstP->type == shortType)
         //fill in the missing code that gets the element and &s it with 0xffff
         printf("%04x ", (((short*)arylstP->array)[i]) & 0xffff);
      else if (arylstP->type == intType)
         //fill in the missing code that gets the element and &s it with 0xffffffff
         printf("%08x ", (((int*)arylstP->array)[i]) & 0xffffffff);
   }
   printf("\n");
}

