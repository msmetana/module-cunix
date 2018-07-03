#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

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

int my_printf(const char *format, ...)
{
   extern long write(int, const char*, unsigned int);
   va_list args;
   char *my_string, *str;
   int i, j, im, c, flag, flag_0;

   my_string = malloc(256*sizeof(char));
   va_start(args, format);

   i = 0,j = 0,im = 0,c = -1;
   flag = 0, flag_0 = 0;

   while(format[i] != '\0'){
     if(format[i] == '%'){
        flag = 0; flag_0 = 0;
        if(format[i+1] == '%'){
          my_string[im] = '%';
          im++; i+=2;
          continue;
        }
        if(format[i+1] == '0'){
          flag_0 = 1;
          i++;
        }
        if(format[i+1] >= '0' && format[i+1] <= '9'){
          if(format[i+2] >= '0' && format[i+2] <= '9'){
             c = atoi(&format[i+1]);
             i++;
          }
          else
            c = atoi(&format[i+1]);
          i++;
          flag = 1;
        }
        if(format[i+1] == 's' || format[i+1] == 'd'){
          if(format[i+1] == 'd'){
            int num = va_arg(args, int);
            str = my_itoa(num);
          }
          else
            str = va_arg(args, char *);
          if (flag ){
            int k = c - strlen(str);
            while(k > 0){
              if(flag_0)
                my_string[im] = '0';
              else
                my_string[im] = ' ';
              k--; im ++;
            }
          }
          j = 0;
          while(j < (int) strlen(str)){
            my_string[im] = str[j];
            j++; im++;
          }
          i += 2;
          continue;
        }
     }
     my_string[im] = format[i];
     i++; im++;
   }

   my_string[im] = '\0';
   write(1, my_string, strlen(my_string));
   va_end(args);
   free(my_string);

   return 0;
}

