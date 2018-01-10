#ifndef __goods_h__
#define __goods_h__

struct shelf{
  char *name;
  int qty;
};

typedef struct goods goods_t;
typedef struct shelf shelf_t;
void test_goods();
//void list_goods(tree_t *tree);
#endif
