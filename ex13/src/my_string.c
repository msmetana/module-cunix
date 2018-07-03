#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define COEF 2

stream_t    *string_init()
{
  stream_t  *p;

  p = (stream_t *) malloc(sizeof(stream_t));
  p->str = NULL;
  p->size = 0;
  p->limit = 0;

  return p;
}

stream_t 		*string_create(char* str)
{
  stream_t	*p;
  int       size_str, i;

  p = string_init();
  size_str = strlen(str);
  p->limit = size_str * (COEF + 1);
  p->str = (char *) malloc((size_str * (COEF + 1)) * sizeof(char));

  for(i = 0; i < size_str; i++)
    p->str[p->size + i] = str[i];

  p->size += size_str;

  return p;
}

void 			  string_append(stream_t *ptr, char *str)
{
  int       size_str, i;

  size_str = strlen(str);

  if(ptr == NULL || str == NULL)
    return;

  if(ptr->size + size_str > ptr->limit){
    ptr->limit = ptr->limit * COEF + size_str;
    ptr->str = realloc(ptr->str, ptr->limit * sizeof(char));
  }

  for(i = 0; i < size_str; i++)
    ptr->str[ptr->size + i] = str[i];

  ptr->size += size_str;
}

void  string_destroy(stream_t *str)
{
  free(str->str);
  free(str);
}

