#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"

/*
 *This program implements a dynamically memory allocated array
 *in C compareable to Java's ArrayList
 *
 *
 * Author: Ahmar Gordon
 * UserID: gordona
 */



//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);
//----------------------------------------------------------------------

/*
 *initialize - creates an instance of the arrayList struct for use
 *
 * Params:
 *      type - the data type the list will contain.
 *
 * Returns:
 *       pointer to the new struct.
 */
arrayList * initialize(primitiveType type)
{
    arrayList * newList = (arrayList*) malloc(sizeof(arrayList));
    newList->elementSize = getSize(type);
    newList->numElements = 0;
    newList->arraySize = 4;
    newList->type = type;
    newList->array = (void*) malloc(4 * newList->elementSize);
    return newList;
}

/*
 *getSize - calculates the size in bytes of a primitive type.
 *
 *Params:
 *      type - your desired data type
 *
 * Returns - number of bytes the data type contains.
 */
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

/*
 *addElement - Adds an element to the list. If there isn't
 *             enough space in the array, more is allocated.
 *
 * Params:
 *      *arylstP - pointer to arrayList struct
 *      *element - pointer to element to be added
 */
void addElement(arrayList * arylstP, void * element)
{
    if(arylstP->numElements >= arylstP->arraySize)
    {
        char * newArray = malloc(((arylstP->elementSize) *2) *arylstP->numElements);
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
    else
        return;
    arylstP->numElements++;
}

/*
 *removeElement - Removes an element at a given index of the
 *                list. Does nothing if index is out of bounds.
 *
 *Params:
 *      *arylstP - pointer to arrayList struct
 *      index - index of array in arrayList
 */
void removeElement(arrayList * arylstP, int index)
{
   if(index < 0 || index > arylstP->arraySize)
       return;

   int i;
   for(i = index; i < arylstP->arraySize - 1; i++)
   {
         if(arylstP->type == intType)
         {
             ((int*)arylstP->array)[i] = ((int*)arylstP->array)[i+1];
         }
         else if(arylstP->type == charType)
         {
             ((char*)arylstP->array)[i] = ((char*)arylstP->array)[i+1];
         }
         else if(arylstP->type == shortType)
         {
             ((short*)arylstP->array)[i] = ((short*)arylstP->array)[i+1];
         }
   }
   arylstP->numElements--;
}
      
/*
 *printArray - prints out the array correctly depending on
 *             the type of data it contains
 */
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
         printf("%04x ", (((short*)arylstP->array)[i]) & 0xffff);
      else if (arylstP->type == intType)
         printf("%08x ", (((int*)arylstP->array)[i]) & 0xffffffff);
   }
   printf("\n");
}

