#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "filler.h"
#include "my_string.h"

int   set_nonblocking(int fd)
{
  int flags;

  flags = fcntl(fd, F_GETFL, 0);
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void  fatal(char *msg)
{
  dprintf(2, msg);
  exit(1);
}

void  create_filler(filler_t *filler)
{
  filler->current_stream = NULL;
  filler->status = 0;
  filler->find_enemy = 0;
}

void  destroy_filler(filler_t *filler)
{
  string_destroy(filler->current_stream);
}


int   check_free_space(map_t *map, elem_t *new_elem, pos_t p)
{
  int i, j;

  for(i = 0; i < new_elem->h; i++)
    for(j = 0; j < new_elem->w; j++)
      if(new_elem->array[i][j] == '*'){
        if(i + p.y < map->h && j + p.x < map->w && i + p.y >= 0 && j + p.x >= 0){
          if(map->array[i + p.y][j + p.x] != '.')
            return -1;
        }
        else
          return -1;
      }

  return 0;
}

int   check_connection(map_t *map, elem_t *new_elem, pos_t p, char symbol)
{
  int i, j;

  for(i = 0; i < new_elem->h; i++)
    for(j = 0; j < new_elem->w; j++)
      if(new_elem->array[i][j] != '.'){
        if(i + p.y + 1 < map->h && map->array[i + p.y + 1][j + p.x] == symbol)
          return 0;
        if (i + p.y - 1 >= 0 && map->array[i + p.y - 1][j + p.x] == symbol)
          return 0;
        if (j + p.x + 1 < map->w && map->array[i + p.y][j + p.x + 1] == symbol)
          return 0;
        if (j + p.x - 1 >= 0 && map->array[i + p.y][j + p.x - 1] == symbol)
          return 0;
      }

  return -1;
}

