#include "test.h"

char *my_strcpy(char *dest, const char *src)
{
  int i;

  i = -1;

  do{
    i++;
    dest[i] = src[i];
  }
  while(src[i] != '\0');

  return dest;
}

