#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"
#include "common.h"
#include "../src/gc.h"
#include <stdio.h>

typedef struct node node_t;

struct node {
  tree_key_t key;
  tree_key_t elem;
  node_t *left;
  node_t *right;
};

struct tree{
  node_t *rootnode;
  heap_t* heap;
  element_copy_fun cpy_f;
  key_free_fun key_f;
  //element_free_fun free_f;
  element_comp_fun cmp_f;
};


/// Creates a new tree
///
/// \param copy (may be NULL) a function applied to all elements when stored in the tree
/// \param key_free (may be NULL) used to free keys in tree_delete
/// \param elem_free (may be NULL) used to free elements in tree_delete
/// \param compare (may be NULL) used to compare keys
/// \returns: empty tree
tree_t *tree_new(element_copy_fun element_copy, key_free_fun key_free, element_comp_fun compare,   heap_t *heap)
{
  tree_t *new_tree = h_alloc_struct(heap, "*****");
  //tree_t *new_tree = calloc(1,sizeof(tree_t));
  new_tree->heap = heap;
  if(element_copy)  {
      new_tree->cpy_f = element_copy;
    }
  if(key_free)    {
    new_tree->key_f = key_free;
  }
  if(compare){
    new_tree->cmp_f = compare;
  }
  new_tree->rootnode = NULL;
  return new_tree;
}

//Ska inte behöva tree_delete_node
/// Remove a tree along with all elem_t elements.
///
/// \param tree the tree
/// \param delete_keys if true, run tree's key_free function on all keys
/// \param delete_elements if true, run tree's elem_free function on all elements
void tree_delete_node(node_t *node, bool delete_keys, bool delete_elements, tree_t *tree){
  if(!node){
    return;
  }
  node_t *l = node->left;
  node_t *r = node->right;
    
  if(delete_keys)
    {
      //node->key = NULL;
      //tree->key_f(node->key);
    }
  if(delete_elements)
    {
      //tree->free_f(node->elem);
    }
    //free(node);
  if(l){
    tree_delete_node(l, delete_keys, delete_elements, tree);
  }
  if(r){
    tree_delete_node(r, delete_keys, delete_elements, tree);
  }
}

//Man behöver inte göra det här. 
void tree_delete(tree_t *tree, bool delete_keys, bool delete_elements)
{
  if(!tree)
    {
      return;
    }
  tree_delete_node(tree->rootnode, delete_keys, delete_elements, tree);
  //free(tree);
}




int tree_size2(node_t *node){
  if(!node){
    return 0;
  }
  else{
    return 1 + tree_size2(node->left) + tree_size2(node->right);
  }
}

int tree_size(tree_t *tree){
  return tree_size2(tree->rootnode);
}



int tree_depth2(node_t *node){
  if (!node){    
    return 0;
  }
  else{
    int leftdepth = tree_depth2(node->left);
    int rightdepth = tree_depth2(node->right);
    if(leftdepth > rightdepth) {
      return leftdepth +1;
    }
    else {
      return rightdepth +1;
    }
  }    
}
  

int tree_depth(tree_t *tree)
{
  if(!tree){
    return -1;
  }
  return tree_depth2(tree->rootnode);
}


node_t *make_node(node_t *node, elem_t Key, elem_t elem, heap_t* heap){
  node_t *new_node = h_alloc_struct(heap, "****");
  //node_t *new_node = calloc(1, sizeof(node_t));
  new_node->key = Key;  
  new_node->elem= elem;
  new_node->left = NULL;
  new_node->right = NULL;
  node = new_node;
  return node;
  
}
/// Insert element into the tree. Returns false if the key is already used.
///
/// Uses the tree's compare function to compare keys.
///
/// If tree's copy function is non-NULL, it will be applied to
/// elem and its result stored in the tree. Otherwise, elem will
/// be stored in the tree. Note that keys are never copied and are
/// assumed to be immutable. (They may however be freed by the
/// tree.)
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended -- this is assumed to be an immutable value
/// \param elem the element 
/// \returns: true if successful, else false
void tree_insert2(node_t *node, tree_key_t key, elem_t elem, element_comp_fun cmp_f, element_copy_fun cpy_f, heap_t* heap){
  node_t *p_new_node = NULL;
  int c = cmp_f(key, node->key);

  if(c < 0){
    if (node->left != NULL){
      tree_insert2(node->left, key, elem, cmp_f, cpy_f, heap);
    }
    else{
      elem = (cpy_f) ? cpy_f(elem, heap) : elem;
      node->left =  make_node(p_new_node, key, elem, heap);
    }
  }
  else if(c > 0){
    if(node->right != NULL){
      tree_insert2(node->right, key, elem, cmp_f, cpy_f, heap);
    }
    else{
      elem = (cpy_f) ? cpy_f(elem, heap) : elem;
      node->right = make_node(p_new_node, key, elem, heap);
    }
  }
}



bool tree_insert(tree_t *tree, tree_key_t key, elem_t elem){
  element_comp_fun cmp_f = NULL;
  element_copy_fun cpy_f = NULL;
  if(tree->cmp_f){
   cmp_f = tree->cmp_f;
  }
  else{
    return false;
  }
  if(tree->cpy_f){
    cpy_f = tree->cpy_f;
  }
  if(tree_has_key(tree, key)){
    return false;
  }
  if(tree->rootnode == NULL){
    tree->rootnode = make_node(tree->rootnode, key, elem, tree->heap);
    return true;
  }
  else{
    tree_insert2(tree->rootnode, key, elem, cmp_f, cpy_f, tree->heap);
    return true;
  } 
}



bool tree_has_key2(node_t *node, tree_key_t key, element_comp_fun cmp_f){
  if(node){
    if(cmp_f(key,node->key) < 0) {
      return tree_has_key2(node->left, key,cmp_f);
    }
    if( cmp_f( key, node->key) > 0) {
      return tree_has_key2(node->right, key, cmp_f);
    }
    if(cmp_f(key, node->key)== 0) {
      return true;
    }
   }
  return false;
}



bool tree_has_key(tree_t *tree, tree_key_t key){
  element_comp_fun cmp_f = tree->cmp_f;
  return tree_has_key2(tree->rootnode, key, cmp_f);
}

/// Finds the element for a given key in tree.
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree
bool tree_get2(node_t *node, tree_key_t key, elem_t *result, element_comp_fun cmp_f){
  if(cmp_f(key, node->key) < 0){
    return tree_get2(node->left, key, result, cmp_f);
  }
  if(cmp_f(key, node->key) > 0){
    return tree_get2(node->right, key, result, cmp_f);
  }
  *result = node->elem;
  return true;
}
    


bool tree_get(tree_t *tree, tree_key_t key, elem_t *result){
 if(tree->cmp_f(key,tree->rootnode->key) == 0){
   *result = tree->rootnode->elem;
   return true;
 }
 else{
   return tree_get2(tree->rootnode, key, result, tree->cmp_f);
 }
}
  

/// Removes the element for a given key in tree.
 ///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree

 node_t *min_node(node_t *node){
   node_t *current = node;
   node_t *prev = node;
   while (current != NULL){
     prev = current;
     current = current->left;
   }
 return prev;
}


node_t *getParent(node_t *root, tree_key_t key, element_comp_fun cmp_f){
    if (root == NULL) return NULL;
    else if (((root->right != NULL) ? cmp_f(root->right->key, key) == 0 : false) || ((root->left != NULL) ? cmp_f(root->left->key, key) == 0 : false)){
      return root;
    }
    else if (cmp_f(root->key, key) > 0){
      return getParent(root->left, key, cmp_f);
    }
    else{
      return getParent(root->right, key, cmp_f);
    }
    puts("end");
    return root;
}


 bool tree_remove(tree_t *tree, tree_key_t key, elem_t *result){
   if(!tree){
     return false;
   }   
   node_t **current = &(tree->rootnode);
   bool found = false;
   while(*current && !found){
     int c = tree->cmp_f(key, (*current)->key);
     if (c < 0) {
       current = &(*current)->left;
     }
     else if(c > 0) {
       current = &(*current)->right;
     }
     else {
       found = true;
     }
   }
   if(found){
     node_t *temp = NULL;
     if( (*current)->left == NULL){
       temp = *current;
       *current = (*current)->right;       
     }
     else if( (*current)->right == NULL) {
       temp = *current;
       *current = (*current) -> left;       
     }
     else{
       node_t *min_node_p = min_node((*current)->right);
       node_t *parent = getParent(tree->rootnode, min_node_p->key, tree->cmp_f);
       //printf("node is %d, parent is %d, ptr 1 %p ptr 2 %p\n", min_node_p->key->i, parent->key->i,min_node_p, *current);
       temp = *current;
       *current = min_node_p;
       (*current)->left = (temp->left == *current) ? NULL : temp->left;
       (*current)->right = (temp->right == *current) ? NULL : temp->right;
       if(parent->left == *current){
         parent->left = NULL;
       }
       if(parent->right == *current){
         parent->right = NULL;
       }
      }
     if(temp){
       *result = temp->elem;
       /* if(result == NULL){
        if(tree->key_f){
            tree->key_f(temp->key);
            }*/
        /* if(tree->free_f){
            tree->free_f(temp->elem);
            }        
            }*/
       //free(temp);
       return true;
     }
   }
   return false;
 }
       
     
 
     

/// Swap the element for a given key for another.
///
/// \param t pointer to the tree
/// \param k the key of elem to be changed
/// \param e the updated element 
/// \param result a elem_t where result will be stored (only defined when result is true)
/// \returns true if both operations succeeded
#define tree_update(t, k, e, tmp) \
  (tree_remove(t, k, &tmp) ? tree_insert(t, k, e) : false)


int tree_to_array(node_t *tree, node_t *array, int index){

   if (!tree){
     return index;
   }
   array[index] = *tree;
   ++index;
   if (tree->left != NULL){
     index = tree_to_array(tree->left, array, index);
   }
   if (tree->right != NULL){
     index = tree_to_array(tree->right, array, index);
   }
   return index;
 }

tree_key_t *tree_keys(tree_t *tree){
   int size = tree_size(tree);
   tree_key_t *keys = h_alloc_struct(tree->heap, "****");
   //tree_key_t *keys = calloc(size,sizeof(node_t));
   node_t array [size];
   tree_to_array(tree->rootnode, array, 0);

   for (int i = 0; i < size; i++ ) {

     keys[i] = array[i].key;
   }
   return keys;
 }

/// Returns an array holding all the elements in the tree
/// in ascending order of their keys (which are not part
/// of the value).
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() elements
int tree_to_array_elements(node_t *tree, node_t *array, int index){

   if (!tree){
     return index;
   }
   array[index] = *tree;
   ++index;
   if (tree->left != NULL){
     index = tree_to_array(tree->left, array, index);
   }
   if (tree->right != NULL){
     index = tree_to_array(tree->right, array, index);
   }
   return index;
 }

 
 elem_t *tree_elements(tree_t *tree){
   int size = tree_size(tree);
   tree_key_t *elements = calloc(size,sizeof(node_t));
   node_t array [size];
   tree_to_array_elements(tree->rootnode, array, 0);

   for (int i = 0; i < size; i++ ) {

     elements[i] = array[i].elem;
   }
   return elements;
 }

/// This function is used in tree_apply() to allow applying a function
/// to all elements in a tree. 
typedef bool(*key_elem_apply_fun)(tree_key_t key, elem_t elem, void *data);

//enum tree_order { inorder = 0, preorder = -1, postorder = 1 };

/// Applies a function to all elements in the tree in a specified order.
/// Example (using shelf as key):
///
///     tree_t *t = tree_new();
///     tree_insert(t, "A25", some_item);
///     int number = 0;
///     tree_apply(t, inorder, print_item, &number);
///
/// where print_item is a function that prints the number and increments it,
/// and prints the item passed to it. 
///
/// \param tree the tree
/// \param order the order in which the elements will be visited
/// \param fun the function to apply to all elements
/// \param data an extra argument passed to each call to fun (may be NULL)
/// \returns the result of all fun calls, combined with OR (||)

bool tree_apply_postorder(node_t *node, key_elem_apply_fun fun, void *data){
  bool l_success = false;
  bool r_success = false;
  bool c_success = false;

  if(node->left != NULL){
    l_success = tree_apply_postorder(node->left, fun, data);
  }
 
  if( node->right !=NULL){
    r_success = tree_apply_postorder(node->right, fun, data);
  }
     c_success = fun(node->key, node->elem, data);
  return l_success || r_success || c_success;
}




bool tree_apply_preorder(node_t *node, key_elem_apply_fun fun, void *data){
  bool l_success = false;
  bool r_success = false;

  bool c_success = fun(node->key, node->elem, data);

  if(node->left != NULL){
    l_success = tree_apply_preorder(node->left, fun, data);
  }
  if( node->right !=NULL){
    r_success = tree_apply_preorder(node->right, fun, data);
  }
  return l_success || r_success || c_success;
  
}



bool tree_apply_inorder(node_t *node,key_elem_apply_fun fun,void *data){
  bool l_success = false;
  bool r_success = false;
  bool c_success = false;
  if(node->left != NULL){
    l_success = tree_apply_inorder(node->left, fun, data);
  }
  c_success = fun(node->key, node->elem, data);
  if( node->right !=NULL){
    r_success = tree_apply_inorder(node->right, fun, data);
  }
  return l_success || r_success || c_success;
  
}


bool tree_apply(tree_t *tree, enum tree_order order, key_elem_apply_fun fun, void *data){
  if(!tree){
    return false;
  }
  node_t *node = tree->rootnode;
  if(order == inorder){
    return tree_apply_inorder(node, fun, data);
  }
  else if(order == preorder){
    return tree_apply_preorder(node, fun, data);
  }
  else if(order == postorder){
    return tree_apply_postorder(node, fun, data);
  }
  return false;
}

bool print_func(tree_key_t key, tree_key_t elem, void *data){
  printf("%d,", key.i);
  return true;
}

bool sort_tree_aux(elem_t key, elem_t elem, void *tree){
  tree_insert((tree_t *)tree, key, elem);
  return true;
}

bool sort_check(node_t *node){
    int left_val = tree_depth2(node->left);
    int right_val = tree_depth2(node->right);
    //printf("left %d right %d\n", left_val, right_val);
    if(abs(left_val - right_val) > 1){
        return false;
    }
    return true;
}

bool check_sort_aux(node_t *node){
    bool l_success = true;
    bool r_success = true;
  
    bool c_success = sort_check(node);
  
    if(node->left != NULL){
      l_success = check_sort_aux(node->left);
    }
    if( node->right !=NULL){
      r_success = check_sort_aux(node->right);
    }
    return l_success && r_success && c_success;
    
  }

  bool check_sort(tree_t *tree){
    if(!tree){
      return false;
    }
    node_t *node = tree->rootnode;
    return check_sort_aux(node);
  }


void sortedArrayToBST(node_t node[], int start, int end, tree_t *tree, tree_key_t keys[])
  {
      /* Base Case */
      if (start > end)
        return;
   
      /* Get the middle element and make it root */
      int mid = (start + end)/2;
      tree_insert(tree, keys[mid], node[mid].elem);
      /* Recursively construct the left subtree and make it
         left child of root */
       sortedArrayToBST(node, start, mid-1, tree, keys);
   
      /* Recursively construct the right subtree and make it
         right child of root */
      sortedArrayToBST(node, mid+1, end, tree, keys);
  }

void sort_tree(tree_t **tree){
  if(!tree) return;
  tree_t *new_tree = tree_new((*tree)->cpy_f, (*tree)->key_f, (*tree)->cmp_f, (*tree)->heap);
  tree_apply(*tree, inorder, sort_tree_aux, new_tree);
  //tree_delete(*tree, false, false);
  *tree = new_tree;
}

void sort_balance(tree_t **tree){
    
    if(!tree) return;
    tree_t *new_tree = tree_new((*tree)->cpy_f, (*tree)->key_f,(*tree)->cmp_f, (*tree)->heap);
    int size = tree_size(*tree);

    node_t array [size];
    sort_tree(tree);
    tree_key_t *keys = tree_keys(*tree);
    tree_to_array((*tree)->rootnode, array, 0);
    
    sortedArrayToBST(array, 0, size -1, new_tree,keys);
    // free(keys);
    //tree_delete(*tree, false, false);
    *tree = new_tree;
}



int int_comp(elem_t x, elem_t y){
  if(x.i > y.i){
    return 5;
  }
  else if(x.i < y.i){
    return -5;
  }
  else{
    return 0;
  }
} 

heap_t* tree_heap(tree_t* t)
{
  return t->heap;
}


/*
void elem_free_f(elem_t elem){
  free(elem.p);
}
*/
