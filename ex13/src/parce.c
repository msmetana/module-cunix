#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "filler.h"
#include "my_string.h"

#define BUF_SIZE 64

req_t 		*parse_all(char *all)
{
	int     i, j, n, index_all;
	req_t   *request;
	pos_t   position;
	char 	  *pos1, *pos2;

	n = 0;
  index_all = 0;
	request = (req_t *) malloc(sizeof(req_t));
	pos1 = (char *) malloc(BUF_SIZE * sizeof(char));
	pos2 = (char *) malloc(BUF_SIZE * sizeof(char));

	memset(pos1, '\0', BUF_SIZE);
	memset(pos2, '\0', BUF_SIZE);

	request->symbol = *all;
	index_all += 2;

	do{
		*(pos1 + n) = *(all + index_all);
		index_all++;
		n++;
	}while(*(all + index_all - 1) != '\n');

	position = parse_size(pos1);
	request->map.h = position.x;
	request->map.w = position.y;

	request->map.array = (char **) malloc(request->map.h * sizeof(char*));

	for(i = 0; i < request->map.h; i++)
		request->map.array[i] = (char *) malloc((request->map.w + 1) * sizeof(char));

	for(i = 0; i < request->map.h; i++)
		for(j = 0; j < request->map.w + 1; j++){
			*(*(request->map.array + i) + j) = *(all + index_all);
			index_all++;
		}

	n = 0;

	do{
		*(pos2 + n) = *(all + index_all);
		index_all++;
		n++;
	}while(*(all + index_all - 1) != '\n');

	position = parse_size(pos2);
	request->elem.h = position.x;
	request->elem.w = position.y;

	request->elem.array = (char **) malloc(request->elem.h * sizeof(char*));

	for(i = 0; i < request->elem.h; i++)
		request->elem.array[i] = (char *)malloc((request->elem.w + 1) * sizeof(char));

	for(i = 0; i < request->elem.h; i++)
		for(j = 0; j < request->elem.w + 1; j++){
			*(*(request->elem.array + i) + j) = *(all + index_all);
		  index_all++;
		}

  free(pos1);
	free(pos2);

  return request;
}

pos_t     parse_size(char *answer)
{
	pos_t 	pos;
	int 	  write_to_c2, t1, t2, i;
	char 	  *c1, *c2;

  c1 = NULL; 
  c2 = NULL;
	write_to_c2 = 0;
  t1 = 0;
  t2 = 0;
  i = 0;
	c1 = (char*) malloc(strlen(answer) * sizeof(char));
	c2 = (char*) malloc(strlen(answer) * sizeof(char));

	memset(c1, '\0', strlen(answer));
	memset(c2, '\0', strlen(answer));

  for(i = 0; *(answer + i) != '\n'; i++){
		if(*(answer + i) == ' '){
			write_to_c2 = 1;
			continue;
		}

		if(write_to_c2 == 0){
		  *(c1 + t1) = *(answer + i);
			t1++;
		}

		if(write_to_c2 == 1){
			*(c2 + t2) = *(answer + i);
			t2++;
		}
	}

	pos.x = atoi(c1);
	pos.y = atoi(c2);

	free(c1);
	free(c2);

	return pos;
}

