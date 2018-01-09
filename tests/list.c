#include <stdlib.h>
#include "common.h"
#include "list.h"

typedef struct node node_t;

struct node {
  elem_t value;
  node_t *next;
};

struct list {
  element_copy_fun elem_cp;
  element_free_fun elem_free;
  element_comp_fun elem_comp;
  node_t *head;
  int length;
  heap_t* heap;
};

list_t *list_new(element_copy_fun copy, element_free_fun l_free, element_comp_fun compare, heap_t* h) {
  list_t *l = h_alloc_struct(l->heap, "****i*");//(list_t *) malloc(sizeof(list_t));
  l->head = NULL;
  l->length = 0;
  l->elem_cp = copy;
  l->elem_free = l_free;
  l->elem_comp = compare;
  l->heap = h;
  return l;
}

/// Creates a new node with the element and links it to the specified node
node_t *node_new(node_t *next, elem_t elem, heap_t* h) {
  node_t *node = h_alloc_struct(h, "**");//(node_t *) malloc(sizeof(node_t));
  node->value = elem;
  node->next = next;
  return node;
}

int correct_index(int index, int list_length) {
  if (index > list_length) { //index out of range
    index = -1;
  }
  if (index < (-list_length)) {
    index = 0;
  }
  if (index < 0) {
    // negative indices should count from the back
    index =  list_length + index + 1;
  }
  return index;
}

bool list_insert(list_t *list, int index, elem_t elem) {
  index = correct_index(index,list_length(list));

  node_t **curr = &list->head;
  //node_t *curr = list->head;
  for (int i = 0; i < index; i++) {
    curr = &(*curr)->next;
    //curr = curr->next;
  }

  elem_t insert_elem;
  
  if (list->elem_cp == NULL) {
    insert_elem = elem;
  }
  else {
    insert_elem = list->elem_cp(elem); 
  }
  
  node_t *node = node_new(*curr, insert_elem, list->heap);
  
  *curr = node;

  list->length++;
  return true;
}

void list_append(list_t *list, elem_t elem) {
  list_insert(list, 0, elem);
}


void list_prepend(list_t *list, elem_t elem) {
  list_insert(list,-1,elem);
}

void list_remove(list_t *list, int index, bool delete) {
  index = correct_index(index,list_length(list));
  if (list_length(list) == 0) {
    return;
  }
  
  if (list_length(list) == 1) {
    if (delete && list->elem_free != NULL) {
      list->elem_free(list->head->value);
    }
    free(list->head);
    list->head = NULL;
    list->length--;
    return;
  }
  
  node_t **prev = &list->head;
  node_t *curr = list->head->next;
  for (int i = 0; i < index-1; i++) {
    prev = &(*prev)->next;
    curr = curr->next;
  }

  //*elem = (*prev)->value;
  if (delete && list->elem_free != NULL) {
    
    list->elem_free((*prev)->value);
  }
  free(*prev);
  *prev = curr;
  list->length--;

  return;

}

bool list_get(list_t *list, int index, elem_t *result) {
  index = correct_index(index,list_length(list));

  node_t *curr = list->head;
  for (int i = 0; i < index; i++) {
    curr = curr->next;
  }
  *result = curr->value;
  return true;
}

bool list_first(list_t *list,elem_t *result) {
  return list_get(list, 0,result);
}

bool list_last(list_t *list, elem_t *result) {
  return list_get(list, -1,result);
}

int list_length(list_t *list) {
  return list->length;
}

void list_delete(list_t *list, bool delete) {
  node_t *curr = list->head;
  
  while (curr != NULL) {
    node_t *next = curr->next;
    if (delete && list->elem_free != NULL) {
      list->elem_free(curr->value);
    }
    free(curr);
    
    curr = next;
  }
  free(list);
}

bool list_apply(list_t *list, elem_apply_fun fun, void *data) {
  bool out = false;
  for (node_t *curr = list->head; curr != NULL; curr = curr->next) {
    bool ans = fun(curr->value, data);
    out = out || ans;
  }
  return out;
}

int list_contains(list_t *list, elem_t elem) {
  int out = -1;

  //element_comp_fun comp = (==);

  node_t *curr = list->head;
  for (int i = 0; i < list_length(list);i++) {
    if (list->elem_comp == NULL) {
      if (elem.i == (curr->value).i) {
        out = i;
      }
    }
    else {
      if (list->elem_comp(elem,curr->value) == 0) {
        out = i;
      }
    }
  }

  
  return out;
}
