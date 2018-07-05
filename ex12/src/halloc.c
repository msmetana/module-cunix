#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define META_SIZE sizeof(struct block_meta)

struct block_meta{
  size_t size;
  struct block_meta *next;
  int free;
};

void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size){
  struct block_meta *current;

  current = global_base;

  while(current && !(current->free && current->size >= size)){
    *last = current;
    current = current->next;
  }

  return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size){
  struct block_meta *block;
  void *request;

  block = sbrk(0);
  request = sbrk(size + META_SIZE);

  if(request == (void*) -1)
    return NULL;

  if(last)
    last->next = block;

  block->size = size;
  block->next = NULL;
  block->free = 0;

  return block;
}

void *halloc(size_t size){
  struct block_meta *block;

  if(size <= 0)
    return NULL;

  if (!global_base){
    block = request_space(NULL, size);

    if(!block)
      return NULL;

    global_base = block;
  }else{
    struct block_meta *last;

    last = global_base;
    block = find_free_block(&last, size);

    if(!block){
      block = request_space(last, size);
      if (!block)
        return NULL;

    }else
      block->free = 0;
  }

  return(block+1);
}

struct block_meta *get_block_ptr(void *ptr){
  return (struct block_meta*)ptr - 1;
}

void my_free(void *ptr){
  if(!ptr)
    return;

  struct block_meta* block_ptr = get_block_ptr(ptr);
  block_ptr->free = 1;
}

