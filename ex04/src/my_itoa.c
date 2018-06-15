#include "test.h"
#include <stdlib.h>
#include <stdio.h>

char* write_to_str(int flag, char *str, int *mas)
{
  int i;

  i = 0;

  while(i < 10){
    if(mas[i] < 0){
      i++;
      continue;
    }
    str[flag] = '0' + mas[i];
    flag++;
    i++;
  }

  str[flag] = '\0';

  return str;
}

char* my_itoa(int nmb)
{
  int dig, i, j, flag;
  const int n = 10;
  int mas[n];
  char* str = calloc(16, sizeof(char));

  dig = nmb;
  i = 0, flag = 0, j = 0;

  if(nmb == 0){
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  if (dig < 0){
    flag = 1;
    dig = (-1) * dig;
    str[0] = '-';
  }

  for(j = 0; j < 10;j++)
    mas[j] = -1;

  while (dig > 0){
    mas[n - 1 - i] = dig % 10;
    i++;
    dig = dig / 10;
  }

  return write_to_str(flag, str, mas);
}
