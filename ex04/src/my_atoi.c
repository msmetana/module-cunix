#include "test.h"
#include <string.h>
#include <ctype.h>


int my_atoi(const char *nptr)
{
  int i, flag, mul, n, count;

  n = strlen(nptr);
  i = 0; mul = 1; count = 0; flag = 1;

  while( i < n){
    if(isalpha(nptr[n-1]))
        flag = 1;

    if(isalpha(nptr[n-i-1]) && flag == 0)
        break;

    if(nptr[n-i-1] >= '1' && nptr[n-i-1] <= '9')
      count += (nptr[n-i-1] - '0')*mul;

    if(!isalpha(nptr[n-1-i]))
      mul = 10*mul;

    i++;
  }

  if(count >= 4294967296)
      count -= 4294967296;
  if (nptr[0] == '-')
    count = (-1)*count;
  return count;
}

