#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "../src/gc.h"

struct node{
  node_t *next;
  node_t *prev;
  elem_t elem;
};

struct list{
  node_t *first;
  node_t *last;
  heap_t* heap;
  element_copy_fun cpy_f;
  element_comp_fun cmp_f;
};

list_t *list_new(element_copy_fun copy, element_comp_fun compare, heap_t* heap){
  list_t *list = h_alloc_struct(heap, "*****");
  //list_t *list = calloc(1, sizeof(list_t));
  list->heap = heap;
                                
  if(copy){
    list->cpy_f = copy;
  }
  if(compare){
    list->cmp_f = compare;
  }
  list->first = NULL;
  list->last = NULL;
  return list;
  
}

node_t *node_new(elem_t elem, node_t *node, heap_t* heap){
  node_t *n = h_alloc_struct(heap, "***");
  // node_t *n = calloc(1, sizeof(node_t));
  n->next = node;

  n->elem = elem;
  if(node){    
  n->prev = node->prev;
  node->prev = n;  
  }

  return n;
}

void list_insert(list_t *list, int index, elem_t elem){
  if(!list){
    return;
  }
  node_t **c = &(list->first);
  
  // Supports negative numbers
  int i = 0;
  index = (index < 0) ? list_length(list) + 1 + index : index;

  while(*c && i < index){ //&& (list->cmp_f) ? list->cmp_f((*c)->elem, elem) : true
    c = &((*c)->next);
    i++;
  }
  elem = (list->cpy_f) ? list->cpy_f(elem) : elem;
  *c = node_new(elem,*c, list->heap);
}

void list_append(list_t *list, elem_t elem){
  list_insert(list,0,elem);
}

void list_prepend(list_t *list, elem_t elem){
  list_insert(list,-1,elem);
}

void list_remove(list_t *list, int index, bool delete){
  if(!list){
    return;
  }
  node_t **c = &(list->first);
  
  // Supports negative numbers
  int i = 0;
  index = (index < 0) ? list_length(list) + index : (index > list_length(list)-1) ? list_length(list)-1 :index;
  while(*c && i < index){ //&& (list->cmp_f) ? list->cmp_f((*c)->elem, elem) : true
    c = &((*c)->next);
    i++;
  }

  //node_t *temp = *c;
  // kanske kan detta vara koden ovan vara problematiskt
  /*if(delete){
    list->free_f((*c)->elem);
    } */
  *c = (*c)->next;
  //free(temp);
}

bool list_get(list_t *list, int index, elem_t *result){
  if(!list){
    return false;
  }
//puts("start");
  // Supports negative numbers
  //printf("index is %d", index);
  index = (index < 0) ? list_length(list) + 1 + index : index;
  node_t *c = list->first;
  //if(c) puts("VALID C");
  //printf("index is %d\n", index);
  for(int i = 0; i < index && c; i++){
    c = c->next;
   // printf("At pos %d\n", i);
  }

  if(c){
      //puts("c found");
    *result = c->elem;
    return true;
  }
  return false;
}

bool list_first(list_t *list, elem_t *result){
  return list_get(list, 0, result);
}

bool list_last(list_t *list, elem_t *result){
  return list_get(list, -1, result);
}

void list_delete(list_t *list, bool delete){
  if(!list){
    return;
  }
  int size = list_length(list);

  for(int i = 0; i < size; i++){
    list_remove(list, 0, delete);
  }
 
  //free(list);
}

int list_length(list_t *list){
  if(list){
    int length = 0;
    node_t *current = list->first;
    while(current != NULL){
      current = current->next;
      length++;
    }
 
    return length; // Check whether length -1 should be returned instead
  }
  return -1;
}

bool list_apply(list_t *list, elem_apply_fun fun, void *data){
  bool success = false;
  if(list){
    node_t *c = list->first;
    while(c){
      bool result = fun(c->elem,data);
      success = result ? result : success;
      c = c->next;
    }
  }  
  return success;
}

int list_contains(list_t *list, elem_t elem){
  int index = -1;
  if(list){
     node_t *c = list->first;
     bool found = false;
     for(int i = 0;c && !found; i++){
       //if(c->elem.i == elem.i){
       if((list->cmp_f) ? list->cmp_f(c->elem, elem) == 0 : (c->elem.i == elem.i || c->elem.u == elem.u || c->elem.p == elem.p || c->elem.f == elem.f)){
         index = i;
         found = true;
       }
       c = c->next;
     }
  }
  return index;
}

//anänds inte i koden
void free_elem_func(elem_t elem){
  free(elem.p);
}

