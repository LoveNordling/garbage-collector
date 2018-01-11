#include "goods.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "list.h"
#include "tree.h"
#include "utils.h"
#include "../src/gc.h"

struct goods {
    char *name;
    char *desc;
    list_t *shelves;
    int price;
};

typedef struct action {
    enum { NOTHING, ADD, REMOVE, EDIT } type;
    goods_t *data;
} action_t;

typedef struct goods goods_t;

char *string_toupper(char *temp) {
    // Convert to upper case
    char *s = strdup(temp);
    while (*s) {
      *s = toupper((unsigned char) *s);
      s++;
    }
    return s;
  }
/*
void list_delete_func(elem_t elem){
  free((char *)(((shelf_t *)elem.p)->name));
  //printf("\n\n\ndeleting in delete func ptr %p\n\n\n", elem.p);
  free(elem.p);

}
*/
elem_t list_copy_func(elem_t elem, heap_t* h){
  shelf_t *shelf = h_alloc_struct(h, "*i");//calloc(1, sizeof(shelf_t));
  shelf->name = strdup(((shelf_t *)(elem.p))->name);
  shelf->qty = ((shelf_t *)(elem.p))->qty;
  return (elem_t) {.p = shelf};
}

int list_comp_func(elem_t a, elem_t b){
  return strcmp(((shelf_t *)(a.p))->name, (((shelf_t *)(b.p))->name));
}

/*
void list_delete_taken_func(elem_t elem){
    free((char *)(elem.p));
  }
*/

elem_t list_copy_taken_func(elem_t elem, heap_t* h){
    char *new = strdup(elem.p);
    return (elem_t) {.p = new};
}
  
int list_comp_taken_func(elem_t a, elem_t b){
    return strcmp(a.p,b.p);
}
/*
void tree_delete_key_func(elem_t elem){
  free((char *)(elem.p));
}
*/
/*
void tree_delete_elem_func(elem_t elem){
  list_delete(((goods_t *)(elem.p))->shelves, true);
  free((char *)(((goods_t *)(elem.p))->name));
  free((char *)(((goods_t *)(elem.p))->desc));
  free(elem.p);
}
*/

bool tree_copy_func_aux(elem_t elem, void *data, heap_t* h){
  elem_t new_elem = list_copy_func(elem, h);
  //printf("The shelf is %s, new is %s\n", ((shelf_t*)(elem.p))->name, ((shelf_t*)(new_elem.p))->name);
  list_append(data, new_elem);  
  //list_delete_func(new_elem);
  return true;
}

elem_t tree_copy_func(elem_t elem, heap_t* h){
 //goods_t *goods = calloc(1, sizeof(goods_t));
  //goods->name = strdup(((goods_t *)(elem.p))->name);
  //goods->desc = strdup(((goods_t *)(elem.p))->desc);
  //goods->price = ((goods_t *)(elem.p))->price;
  //list_t *new_list = list_new(list_copy_func, list_delete_func, list_comp_func);

  //list_apply(((goods_t *)(elem.p))->shelves, tree_copy_func_aux, new_list);
  
  return (elem_t) {.p = elem.p};
}

elem_t tree_copy_complete_func(elem_t elem, heap_t* heap){
  goods_t *goods = h_alloc_struct(heap, "***i");//calloc(1, sizeof(goods_t));
    goods->name = strdup(((goods_t *)(elem.p))->name);
    goods->desc = strdup(((goods_t *)(elem.p))->desc);
    goods->price = ((goods_t *)(elem.p))->price;
    list_t *new_list = list_new(list_copy_func, list_comp_func, heap);
  
    list_apply(((goods_t *)(elem.p))->shelves, tree_copy_func_aux, new_list);
    goods->shelves = new_list;
    return (elem_t) {.p = goods};
  }

int tree_comp_func(elem_t a, elem_t b){
    //char *tempA = string_toupper(a.p);
    //char *tempB = string_toupper(b.p);
    //int result = strcmp(tempA, tempB);
    //printf("NAME %s   %s\n", a.p, tempA);
    //free((char *)tempA);
    //free((char *)tempB);
    return strcmp(a.p, b.p);
}

bool shelf_taken(list_t *taken, char *newshelf, bool update) {
  int len = list_length(taken); //- 1;
  if (len == 0 || update) {
    return false;
  }
  for (int i = 0; i < len; i++) {
    //shelf_t *tshelf = calloc(1, sizeof(shelf_t));
    elem_t temp ;//= {.p = tshelf};
    list_get(taken, i, &temp);
    if (!strcmp(temp.p, newshelf)) {
      printf("Shelf %s is already taken. \n", newshelf);
      return true;
    }
    //free(tshelf);
  }
  return false;
}

void list_shelf(list_t *head) {
  for (int i = 0; i < list_length(head); i++) {
    elem_t temp;
    list_get(head, i, &temp);
    //shelf_t *shelf = list_get(head, i);
    printf("%d.Shelf: %s, Amount: %d\n", i + 1,((shelf_t *)temp.p)->name, ((shelf_t *)temp.p)->qty);
  }
}

int choose_shelf(list_t *list) {
    list_shelf(list);
    int choice;
    do {
        choice = ask_question_int("Choose which shelf: [number]");
    } while (choice > list_length(list) || choice < 1);
    return (choice - 1);
}

shelf_t *make_shelf(list_t *taken, char *shelf, int amount) {
    //shelf_t new = {.name = shelf, .qty = amount};
  shelf_t *new = h_alloc_struct(list_heap(taken), "*i");//calloc(1, sizeof(shelf_t));
    new->name = shelf;
    new->qty = amount;
    list_append(taken, (elem_t) {.p = shelf});
    //list_delete_taken_func((elem_t) {.p = shelf});
    //free((char *)(new->name));
    return new;
}

shelf_t *make_shelf_ui(list_t *taken) {
    char *shelf = NULL;
    do {
        if(shelf != NULL) free((char *)shelf);
        shelf = ask_question_shelf("Please input the shelf of the goods:");
    } while (shelf_taken(taken, shelf, false));
    int amount = ask_question_int("Please input the amount of goods:");
return make_shelf(taken, shelf, amount);
}

goods_t *input_goods(tree_t *tree, list_t *taken, char *name, char *desc, int price) {
    if (tree_has_key(tree, (elem_t) {.p = name})) {
      //free((char *) name);
      //free((char *) desc);
        return NULL;
        //fattar inte exakt vad dessa frees gör.
    }

    goods_t *goods = h_alloc_struct(tree_heap(tree), "***i");//calloc(1, sizeof(goods_t));
    goods->name = name;
    goods->desc = desc;
    goods->price = price;
   // goods->shelves = list;
    return goods;
}




goods_t *input_goods_ui(tree_t *tree, list_t *taken, heap_t* heap) {
    char *name = ask_question_string("Please input the name of the goods:");
    if (tree_has_key(tree, (elem_t) {.p = name})) {
        printf(
            "%s exists in the database. Using current description and price.\n",
            name);
        elem_t temp;
        //goods_t *exist =
        tree_get(tree, (elem_t) {.p = name}, &temp);
        puts("Please make a new shelf.");
        shelf_t *newsh = make_shelf_ui(taken);
        list_append(((goods_t *)temp.p)->shelves, (elem_t) {.p = newsh});
        //list_delete_func((elem_t) {.p = newsh});
        //free(newsh);
        // Updating the item
        goods_t *goods = h_alloc_struct(heap, "***i");//malloc(sizeof(goods_t));
        goods->name = ((goods_t *)temp.p)->name;
        goods->desc = ((goods_t *)temp.p)->desc;
        goods->price = ((goods_t *)temp.p)->price;
        goods->shelves = ((goods_t *)temp.p)->shelves;
        //free((char *) name);
        return goods;
    }
    char *desc =
        ask_question_string("Please input the description of the goods:");
    int price =
        ask_question_int("Please input the price of the goods in cents (SEK):");

    goods_t *temp = input_goods(tree, taken, name, desc, price);

    list_t *list = list_new(list_copy_func, list_comp_func, heap);
    shelf_t *new = make_shelf_ui(taken);
    list_insert(list, 0, (elem_t) {.p = new});
    //list_delete_func((elem_t) {.p = new});
    temp->shelves = list;
    return temp;
}

goods_t *edit_item(goods_t *goods, list_t *taken) {
    char choice;
    choice = ask_question_char(
        "What would you like to edit? [D]esc, [P]rice, [S]helf, [A]mount");
    if (choice == 'D') {
        printf("Old desc is: %s\n", goods->desc);
        //TODO: utökning att skriva_ask_question function som använder vår heap.
        free((char *) goods->desc);
        goods->desc = ask_question_string("Please input new description:");
    }

    if (choice == 'P') {
        printf("Old price is: %d\n", goods->price);
        goods->price = ask_question_int("Please input new price:");
    }
    if (choice == 'S' || choice == 'A') {
        int s = choose_shelf(goods->shelves);
        elem_t old;
        //shelf_t *old =
        bool fetched = list_get(goods->shelves, s, &old);
        if (choice == 'A' && fetched) {
            //int newamount = ask_question_int("How much would you like to add?") + ((shelf_t *)(old.p))->qty;
            ((shelf_t *)(old.p))->qty = ask_question_int("How much would you like to add?") + ((shelf_t *)(old.p))->qty;
            //elem_t new= list_copy_func(old);
            //((shelf_t *)(new.p))->qty = newamount;
            //list_remove(goods->shelves, s, false);
            //list_insert(goods->shelves, s,new);
            //list_delete_func(new);
        }
        else if(!fetched){
            puts("Could not fecth the shelf :(");
        }
        //shelf_t *r = malloc(sizeof(shelf_t));
        
        //free(r);
        if (choice == 'S') {
            shelf_t *newsh = make_shelf_ui(taken);
            int index = list_contains(taken, (elem_t) {.p = newsh->name});
            if(index >= 0){
                list_remove(taken, index, true);
            }
            list_remove(goods->shelves, s, true);
            list_append(goods->shelves, (elem_t) {.p = newsh});
            //list_delete_func((elem_t) {.p = newsh});
        }
    }
    puts("Item has been updated");
    return goods;
}
void add_goods(tree_t *tree, list_t *taken, action_t *undo, heap_t* heap) {
  goods_t *new = input_goods_ui(tree, taken, heap);
    //list_shelf(new->shelves);
    char choice;
    while (1) {
        choice = ask_question_char("Add item? [Y]es/[No]/[E]dit");
        // printf("Choice: %c\n", choice);
        if (choice == 'Y') {
            puts("Adding item to db");
            tree_insert(tree, (elem_t) {.p = new->name}, (elem_t) {.p = new});
            //elem_t temp;
            //tree_get(tree, (elem_t) {.p = new->name}, &temp);
            //list_shelf(((goods_t *)temp.p)->shelves);
            //list_shelf(new->shelves);
            if(undo->type != NOTHING){
                //tree_delete_elem_func((elem_t) {.p = undo->data});
            }
            undo->type = ADD;
            undo->data = new;
            //tree_delete_elem_func((elem_t) {.p = new});
            return;
        } else if (choice == 'N') {
            //shelf_t *r = malloc(sizeof(shelf_t));
            list_remove(taken, -1, true);
            //free(r);
            //free(new);
            //tree_delete_elem_func((elem_t) {.p = new});
            return;
        } else if (choice == 'E') {
            new = edit_item(new, taken);
            tree_insert(tree, (elem_t) {.p = new->name}, (elem_t) {.p = new});

            if(undo->type != NOTHING){
                //tree_delete_elem_func((elem_t) {.p = undo->data});
            }
            undo->type = ADD;
            undo->data = new;
            return;
        }
    }
}


void display_goods(goods_t *goods) {
    int crowns = goods->price / 100;
    int cents = goods->price % 100;
    printf("Name: %s\n", goods->name);
    printf("Desc: %s\n", goods->desc);
    printf("Price: %d.%d SEK\n", crowns, cents);
    list_shelf(goods->shelves);
}

goods_t *choose_goods(tree_t *tree, char *question) {
  int page = 1;
  int length = tree_size(tree);
  elem_t *keys = tree_keys(tree);
  const int LIMIT = MAX_SIZE;
  int choice = -200;  // Random negative number as constructor.
  char *arr[LIMIT - 1];
  while (choice != -1) {
    int noitems = ((length - LIMIT * (page - 1)) < LIMIT)
      ? length - LIMIT * (page - 1)
      : LIMIT;
    for (int i = 0; i < noitems; i++) {
      int localindex = i + LIMIT * (page - 1);
      printf("%d. %s\n", (i + 1), keys[localindex].p);
      arr[i] = keys[localindex].p;
    }
    printf("Page: %d / %d\n", page, (((length-1) / LIMIT)) + 1);
    puts("[C] to cancel, [N] for next page, [P] for previous page");
    choice = ask_question_list(question);
    if (choice == -2) {
      if (length > (page * LIMIT)) {  // N
        ++page;
      } else {
        puts("You're already at the last page");
      }
    } else if (choice == -3) {  // P
      if (page != 1) {
        --page;
      } else {
        puts("You're already at page 1!");
      }
    } else if (choice == -1) {  // C
      //free(keys);
      return NULL;
    } else if (choice > noitems) {
      puts("That's an invalid index");
    } else {
        
      elem_t temp;
      tree_get(tree, (elem_t) {.p = arr[choice - 1]}, &temp);
      goods_t *goods = temp.p;
      //free(keys);
      return goods;
    }
  }
  //free(keys);
  return NULL;
}

void list_goods(tree_t *tree) {
    if (tree_size(tree) == 0) {
        puts("Database is empty");
        return;
    }
    goods_t *goods = choose_goods(tree, "Which item would you like to view?");
    if (goods == NULL) {
        return;
    }
    display_goods(goods);
}

void remove_goods(tree_t *tree, list_t *taken, action_t *undo) {
  if (tree_size(tree) == 0) {
    puts("Database is empty");
    return;
  }
  goods_t *choice = choose_goods(tree, "Which item would you like to remove?");
  if (choice == NULL) {  // Cancel
    return;
  } else {
    //goods_t *save = calloc(1, sizeof(goods_t));
    //goods_t *save = tree_copy_complete_func((elem_t) {.p = choice}).p;
    elem_t temp_elem;
    tree_remove(tree, (elem_t) {.p = choice->name}, &temp_elem);

    if(undo->type != NOTHING){
      // tree_delete_elem_func((elem_t) {.p = undo->data});
    }
    undo->type = REMOVE;
    undo->data = temp_elem.p;
  }
}

void edit_goods(tree_t *tree, list_t *taken, action_t *undo, heap_t* heap) {
    if (tree_size(tree) == 0) {
        puts("Database is empty");
        return;
    }
    goods_t *choice = choose_goods(tree, "What item would you like to edit?");
    if (choice == NULL) {
        return;
    }
    goods_t *removed = tree_copy_complete_func((elem_t) {.p = choice}, heap).p;//problem-källa kanske? 
    //goods_t *updated = tree_copy_complete_func((elem_t) {.p = edit_item(choice, taken)}).p; 
    goods_t * updated = edit_item(choice, taken);
    list_shelf(updated->shelves);
    printf("The goods %p %p\n", choice, updated);
    
    //return;
    //elem_t temp_elem;
    //char *temp_name = strdup(updated->name);
    printf("NAME %s PTR %p\n", updated->name, updated);
    //tree_remove(tree, (elem_t) {.p = choice->name}, &temp_elem);
    // crashes here, something removs that shouldn't, works when removing all the frees in tree remove, check what gets removed that shouldnt
    // could be that it tries to remove something that is removed already, work by disabling one by one free in freeing functions.
    printf("NAME %s PTR %p\n", updated->name, updated);
    printf("NAME %s PTR %p\n", updated->name, removed); // NAME   

    //tree_insert(tree, (elem_t) {.p = updated->name}, (elem_t) {.p = updated});

    if(undo->type != NOTHING){
      //tree_delete_elem_func((elem_t) {.p = undo->data});
    }
    undo->type = EDIT;
    undo->data = removed;
}

void print_greeting() {
    printf("Storage Program v.1.0 What would you like to do?\n");
}

char ask_question_menu() {
  return ask_question(
                      "[A]dd an item\n[R]emove an item\n[E]dit an item\n[S]ort database\n[C]heck if sorted\n[U]ndo last "
                      "action\n[L]ist catalogue\n[Q]uit",
                      valid_option, (convert_func)convert_char)
    .c;
}

void undo_action(tree_t *tree, list_t *taken, action_t *undo) {
  if (undo->type == NOTHING) {
    printf("No action has been taken\n");
    return;
  }
  if (undo->type == ADD) {
      puts("inside ADD");
      printf("Goods name %s\n", undo->data->name);
    //goods_t *removed = calloc(1, sizeof(goods_t));
    elem_t temp_elem;
    tree_remove(tree, (elem_t) {.p = undo->data->name} , &temp_elem);
    printf("You added %s, it has now been removed\n", undo->data->name);
    //shelf_t *r = malloc(sizeof(shelf_t));
    list_remove(taken, -1, true);  // Last list element to be added so last element to be removed;
    //tree_delete_elem_func(temp_elem);
    //tree_delete_elem_func((elem_t) {.p = undo->data});
    //free(temp);
  }
  if (undo->type == REMOVE) {
    puts("inside remove");
    printf("Goods name %s\n", undo->data->name);
    tree_insert(tree, (elem_t) {.p = undo->data->name}, (elem_t) {.p = undo->data});
    printf("You removed %s, it has now been restored\n", undo->data->name);
    //tree_delete_elem_func((elem_t) {.p = undo->data});
  }
  if (undo->type == EDIT) {
    puts("inside edit");
    printf("Goods name %s\n", undo->data->name);
    elem_t temp_elem;
    tree_remove(tree, (elem_t) {.p = undo->data->name} , &temp_elem);
    printf("You changed %s, it has now been reverted\n", undo->data->name);
    tree_insert(tree, (elem_t) {.p = undo->data->name}, (elem_t) {.p = undo->data});
    //tree_delete_elem_func(temp_elem);
    //tree_delete_elem_func((elem_t) {.p = undo->data});
  }
  undo->type = NOTHING;
}

void list_shelf_printer(elem_t elem, FILE *fPointer) {
    fprintf(fPointer,"%s\n", ((shelf_t*)(elem.p))->name );
    fprintf(fPointer,"%d\n", ((shelf_t*)(elem.p))->qty );
    
  }
  
  
  void key_elem_print_fun(tree_key_t key, elem_t elem, FILE *fPointer){
    //fprintf(fPointer,"%s", key);
    
    fprintf(fPointer,"%s\n", ((goods_t *)(elem.p))->name);
    fprintf(fPointer,"%s\n", ((goods_t *)(elem.p))->desc);
    fprintf(fPointer,"%d\n", ((goods_t *)(elem.p))->price);
    fprintf(fPointer,"%d\n", list_length(((goods_t*)(elem.p))->shelves) );
    list_apply(((goods_t* )(elem.p))->shelves ,(elem_apply_fun)list_shelf_printer, fPointer);
  } 
  
  void print_database_to_file(tree_t * tree) {
    FILE* fPointer;
      fPointer = fopen("Database.txt", "w");
      fprintf(fPointer, "%d\n", tree_size(tree));
      tree_apply(tree, inorder,(key_elem_apply_fun)key_elem_print_fun, fPointer); 
      fclose(fPointer);
     
  }
  
    void file_reader(tree_t *tree, list_t *taken, heap_t* heap){
    FILE* fPointer;
    fPointer = fopen("Database.txt", "r");
    size_t size = 0;
    char *amount = NULL;
    char *item = NULL;
    getline(&amount, &size, fPointer);
    size = 0; 
    int limit = atoi(amount);
    free(amount);
    for(int i = 1; i <= limit; i++) {
      getline(&item, &size, fPointer);
      char *t= item;
      strtok(t, "\n");
      char *name = strdup(t);
      size = 0;
      free(item);
      getline(&item, &size, fPointer);
      t= item;
      strtok(t, "\n");
      char *desc = strdup(t);
      free(t);
      size=0;
      
      getline(&item, &size, fPointer);
      int price = atoi(item);
      size = 0;
      
      free(item);
      getline(&item, &size, fPointer);
      int s_amount = atoi(item);
      size = 0;
      free(item);
      goods_t *temp = input_goods(tree, taken, name, desc, price);
      
      //free(desc);
      list_t *list = list_new(list_copy_func, list_comp_func, heap);
      for(int s = 1; s <= s_amount; s++){
         char *var = NULL;
         getline(&var, &size, fPointer);
         strtok(var, "\n");
         char *name = strdup(var);
         
         size = 0;
         
         getline(&item, &size, fPointer);
         int qty = atoi(item);
         free(item);
         size = 0;
        shelf_t *new = make_shelf(taken, name, qty);
        list_insert(list, 0, (elem_t) {.p = new});
        //list_delete_func((elem_t) {.p = new});
        free((char *)var);

        free(name);
      }

      //free(item);
      temp->shelves = list;
      tree_insert(tree, (elem_t) {.p = temp->name}, (elem_t) {.p = temp});
      //free(name);
      //tree_delete_elem_func((elem_t) {.p = temp});
    }
    //tree_delete(tree, true, true);
    fclose(fPointer);
}

void event_loop() {
    heap_t * heap =h_init(40000, true, 0.5);
    action_t *undo = h_alloc_struct(heap, "i*");//malloc(sizeof(action_t));
    undo->type = NOTHING;
    tree_t *tree = tree_new(tree_copy_func, NULL /*tree_delete_key_func*/,tree_comp_func, heap);
    list_t *taken = list_new(list_copy_taken_func, list_comp_taken_func, heap);
    //test_goods(tree, taken);
    file_reader(tree, taken, heap);
    
    char choice;
    while (true) {
        print_greeting();
        choice = ask_question_menu();
        if (choice == 'A') {
          add_goods(tree, taken, undo, heap);
        }
        if (choice == 'R') {
            remove_goods(tree, taken, undo);
        }
        if (choice == 'E') {
          edit_goods(tree, taken, undo, heap);
        }
        if (choice == 'U') {
            undo_action(tree, taken, undo);
        }
        if (choice == 'L') {
            
            list_goods(tree);
        }
        if (choice == 'S') {
            if (tree_size(tree) == 0) {
                puts("Database is empty");
            }
            else{
                sort_balance(&tree);
            }
        }
        if (choice == 'C') {
            if (tree_size(tree) == 0) {
                puts("Database is empty");
            }
            else{
                if(check_sort(tree)){
                    puts("Database is sorted!");
                }
                else{
                    puts("Database is NOT sorted!");
                }
            }
        }
        if (choice == 'Q') {
            print_database_to_file(tree);
            tree_delete(tree, true, true);
            list_delete(taken, true);
            
            if(undo->data){
              //free(undo->data);
              //tree_delete_elem_func((elem_t) {.p = undo->data});
            }
            h_delete(heap);
            //free(undo);
            //free(tree);
            //free(taken);
            // tree_delete(tree, false);
            // Need to add list delete as well.
            return;
        }
    }
}

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    event_loop();
    return 0;
}
