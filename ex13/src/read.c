#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "filler.h"
#include "my_string.h"

#define BUF_SIZE 64


void  find_size_elem(char res[32], char *buf, int start_pos)
{
	int 	i;

	i = 0;

	do{
    res[i] = buf[start_pos];
    start_pos++;
    i++;
  }while (buf[start_pos-1] != '\n');

 	res[i] = '\0';

  return ;
}

int  end_read(stream_t* p)
{
  int i, pos_size_elem, size_map;
  char arr_elem_size[32];
  pos_t 	size_elem;

	i = 0; size_map = 1; pos_size_elem = 0;

  while(i <= p->size){
    if(!isdigit(p->str[i]))
      i++;
    else
      if(size_map){
        while(i <= p->size && p->str[i] != '\n')
          i++;

      		size_map = 0;
          i++;
    	}
    	else{
      			pos_size_elem = i;
      			while(i <= p->size && p->str[i] != '\n')
        	    i++;
        			find_size_elem(arr_elem_size, p->str, pos_size_elem);
        			size_elem = parse_size(arr_elem_size);
        			if(p->size <= i + size_elem.x*(size_elem.y + 1))
          				return -1;
        			else
                return 0;
    		}
  	}

  	return -1;
}
void  read_input(filler_t* filler)
{
  char    buffer[BUF_SIZE];

  while(1){
    memset(buffer, '\0', BUF_SIZE);
    read(0, buffer, BUF_SIZE - 1);

    if(strlen(buffer) == 0)
      break;

		if(filler->current_stream == NULL)
      filler->current_stream = string_create(buffer);
    else
      string_append(filler->current_stream, buffer);
	}
}

req_t  *read_request(filler_t *filler)
{
	req_t  *req = NULL;

	read_input(filler);

	if(end_read(filler->current_stream) == 0)
		req = parse_all(filler->current_stream->str);

	return req;
}

