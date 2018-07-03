#include "../include/hash.h"
#include "../include/linked_list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

hashtable_t  *hash_create(unsigned int size)
{
  unsigned int i;
	hashtable_t *new;

	if(size <= 0)
    return NULL;

	new = (hashtable_t*) malloc(sizeof(hashtable_t));
  new->size = size;
  new->table = (void **) malloc(size*sizeof(void*));

  for(i = 0; i < size; i++)
		new->table[i] = NULL;

  return new;
}

void 	hash_destroy(hashtable_t *ht)
{
  unsigned int i;
	node_t *p;

	for(i = 0; i < ht->size; i++)
		if(ht->table[i] != NULL){
			p = ht->table[i];
			list_destroy(&p);
	  }

	free(ht->table);
	free(ht);
}

unsigned int 		hash_func(char *key)
{
	int  sum, i;

  sum = 0; i = 0;

	if(key == NULL)
		return 0;

  for(i = 0; key[i] != '\0'; i++)
		sum += key[i];

	return sum;
}

void 			hash_set(hashtable_t *ht, char *key, void *ptr)
{
	unsigned int 	k = hash_func(key) % ht->size;

  if(ht->table[k] == NULL){
		ht->table[k] = list_create(ptr,key);
	}
	else{
		list_push(ht->table[k], ptr, key);
	}

}

void 			*hash_get(hashtable_t *ht, char *key)
{
	int 		k = hash_func(key) % ht->size;
  node_t    *p;

	if(ht->table[k] == NULL)
		return NULL;

	p = ht->table[k];

	return p->data;
}

void      *hash_print(hashtable_t *ht)
{
  unsigned int i;

  if(ht == NULL)
    return NULL;

  for(i = 0; i < ht->size; i++)
    if(ht->table[i] != NULL)
      list_print((node_t *)ht->table[i]);

  printf("\n");

  return NULL;
}

