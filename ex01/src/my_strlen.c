#include "test.h"

unsigned int my_strlen( char *arg)
{
   int i;

   i = 0;

   while (arg[i] != '\0')
     i++;

   return i;
}

