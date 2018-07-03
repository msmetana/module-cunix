#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

node_t 		*list_create(void *data, char *key)
{
	node_t 	*head;
  head = malloc(sizeof(node_t));
	head->data = data;
  head->key = key;
	head->next = NULL;

  return head;
}

void      list_destroy(node_t **head)
{
	if((*head) == NULL)
		return;

  node_t *p = *head;
  head = NULL;
  node_t *del;

  while (p != NULL){
    del = p;
    p = p->next;
    free(del);
  }
}

void      list_push(node_t *head, void *data, char *key)
{
  if(head == NULL)
    return;

	node_t *p = head;
  node_t *ptr = malloc(sizeof(node_t));

  while(p->next != NULL)
		p = p->next;

  ptr->key = key;
	ptr->data = data;
	ptr->next = NULL;
  p->next = ptr;
}

void 		list_unshift(node_t **head, void *data, char *key)
{
  if(*(head) == NULL)
    return;

	node_t 	*p;
	p = malloc(sizeof(node_t));
	p->data = data;
  p->key = key;
	p->next = *head;
	*head = p;
}

void 		*list_pop(node_t **head)
{
	node_t 	*p;
	node_t 	*cur;

  p   = *head;
  cur = *head;

	if((*head)->next == NULL){
    free((*head)->data);
		free(*head);
		*head = NULL;

    return NULL;
	}

	cur  = cur->next;
	while(cur->next != NULL){
		cur = cur->next;
		p  = p->next;
	}

	void *ret = cur->data;
  free(cur->data);
	free(cur);
	p->next = NULL;
	return ret;
}

void 		*list_shift(node_t **head)
{
  if(*(head) == NULL)
    return NULL;

	node_t 	*p = *head;
	*head = p->next;
	void *ret = p->data;
  free(p->data);
	free(p);
  return ret;
}

void 		*list_remove(node_t **head, int pos)
{
  if(*(head) == NULL)
    return NULL;
  if(pos == 0)
    return list_shift(head);

  int num = 1;
  node_t *p = *head;
  node_t *cur = (*head)->next;
  while(num != pos){
    p = p->next;
    cur = cur->next;
    num++;
  }

  void *ret = cur->data;
  p->next = cur->next;
  free(cur->data);
  free(cur);
  return ret;
}


void 		list_print(node_t *head)
{
	node_t 	*p = head;
	while(p != NULL){
    printf("\n%s: %s", p->key, (char*) p->data);
    p = p->next;
  }
}

void 		list_visitor(node_t *head, void(*fp)(void *data))
{
  while (head != NULL) {
    (*fp)(head->data);
    head = head->next;
  }
}

