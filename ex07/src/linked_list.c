#include "../include/linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

node_t  *list_create(void *data) {
   node_t * head = NULL;
   head = malloc(sizeof(node_t));
   head->data = data;
   head->next = NULL;
   return head;
}

void list_destroy(node_t **head, void (*fp)(void *data)) {
    if (head == NULL) {
      return;
    }
    node_t *curr = *head;
    node_t *next;

    while (curr != NULL) {
         fp(curr->data);
         next = curr->next;
         free(curr);
         curr = next;
    }
    *head = NULL;
}

void list_push(node_t *head, void *data) {
  if (head == NULL)
    return;
  while(head->next) head = head->next;
  head->next = malloc(sizeof(node_t));
  head = head->next;
  head->next = NULL;
  head->data = data;
}

void list_unshift(node_t **head, void *data) {
     node_t   *new_node = malloc(sizeof(node_t));
     new_node->data = data;
     new_node->next = *head;
     *head = new_node;
}

void *list_pop(node_t **head){
    node_t *ptr, *pptr = *head;
    void *res;
    if(pptr->next) {
      ptr = pptr->next;
    } else {
      res = (*head)->data;
      free((*head)->data);
      free(*head);
      *head = NULL;
      return res;
    }
    while (ptr->next) {
      ptr = ptr->next;
      pptr = pptr->next;
    }
    res = ptr->data;
    free(ptr->data);
    free(ptr);
    pptr->next = NULL;
    return res;
}

void *list_shift(node_t **head) {
   void *res;
   node_t *temp = *head;
   *head = (*head)->next;
   res = temp->data;
   free(temp->data);
   free(temp);
   return res;
}

void *list_remove(node_t **head, int pos) {
  void *res;
  node_t *ptr = *head, *pptr;
  if (pos == 0) {
      res = ptr->data;
      (*head) = (*head)->next;
      free(ptr->data);
      free(ptr);
      return res;
  }
  pptr = ptr;
  ptr = ptr->next;
  while(pos > 1) {
      ptr = ptr->next;
      pptr = pptr->next;
      pos--;
   }
  pptr->next = ptr->next;
  res = ptr->data;
  free(ptr->data);
  free(ptr);
  return res;
}

void list_print(node_t *head) {
    node_t * current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

void list_visitor(node_t *head, void (*fp)(void *data)) {
    while (head != NULL) {
        (*fp)(head->data);
        head = head->next;
    }
}
/*#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

node_t 		*list_create(void *data)
{
	node_t 	*head;

  head = malloc(sizeof(node_t));
	head->data = data;
	head->next = NULL;

  return head;
}

void      list_destroy(node_t **head, void(*fp)(void *))
{
	if((*head) == NULL)
		return;

  node_t *p = *head;
  head = NULL;
  node_t *del;

  while (p != NULL){
    fp(p->data);
    del = p;
    p = p->next;
    free(del);
  }
}

void      list_push(node_t *head, void *data)
{
  if(head == NULL)
    return;

	node_t *p = head;
  node_t *ptr = malloc(sizeof(node_t));

  while(p->next != NULL)
		p = p->next;

	ptr->data = data;
	ptr->next = NULL;
  p->next = ptr;
}

void 		list_unshift(node_t **head, void *data)
{
  if(*(head) == NULL)
    return;

	node_t 	*p;
	p = malloc(sizeof(node_t));
	p->data = data;
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
		printf("%p", p->data);
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
-*/
