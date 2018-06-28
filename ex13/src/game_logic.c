#include <stdio.h>
#include <stdlib.h>
#include "filler.h"

int count = 0;
int flag = 1;

pos_t 		play(req_t *core, filler_t *filler)
{
  int quarter;
  pos_t res;
  pos_t first_el;
  FILE 	*logger;
  int 	h, w, i, j, c;

  quarter = 0;
  c = 0;

  h = core->map.h;
  w = core->map.w;

 //logger = fopen("filler1.log", "a");
 //fprintf(logger, "Play\n");
 // fprintf(logger, "core->map.h = %d, core->map.w = %d/n", core->map.h, core->map.w);
 // fclose(logger);

  for(i = 0; i < h && count == 0; i++)
    for(j = 0; j < w; j++)
      if(core->map.array[i][j] == core->symbol){
          first_el.x = j;
          first_el.y = i;
      }

  count++;

  if(first_el.x < w/2 - 1){
    if(first_el.y < h/2 - 1)
      quarter = 1;
    else
      quarter = 2;
  }
  else{
    if(first_el.y < h/2 - 1)
      quarter = 4;
    else
      quarter = 3;
  }

  if( quarter == 1 || quarter == 3){
    for(i = h - 1; i >=0 && flag == 1; i--)
      for(j = w - 1; j >= 0 && flag == 1; j--){
          res.x = j;
          res.y = i;

          if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map),&(core->elem),res,core->symbol)){
            if(h - i < 3 || w - j < 3)
              flag = 2;

          return res;
          }
   }

   for(i = 0; i < h && flag == 2; i++)
     for(j = 0; j < w && flag == 2; j++){
       res.x = j;
       res.y = i;
       if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol)){
         if( i < 1 ||  j < 1)
            flag = 3;
         return res;
       }
    }

  }
  else{
    for(i = 0; i < h && flag == 1; i++)
      for(j = w - 1; j >= 0 && flag == 1; j--){
        res.x = j;
        res.y = i;

        if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol)){
          if(i < 3 || w - j < 3)
            flag = 2;
          return res;
        }
    }

    for(i = h - 1; i >= 0 && flag == 2; i--)
      for(j = 0; j < w && flag == 2; j++){
        res.x = j;
        res.y = i;
        if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol)){
          if(h -  i < 3 || j < 3)
            flag = 3;
          return res;
        }
      }
  }

  while(c < h/2 -3){
   for(i = h/2 - 1 - c; i < h/2 + 1 + c; i++)
     for(j = w/2 - 1 - c; j < w/2 + 1 + c; j++){
       res.x = j;
       res.y = i;
       if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
         return res;
       }
   c++;
  }

  return res;
}

