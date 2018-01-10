#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>
#include <stdlib.h>
extern char *strdup(const char *);
typedef union {
    int i;
    float f;
    char *s;
    char c;
} answer_t;

typedef bool (*check_func)(char *);
typedef answer_t (*convert_func)(char *);

enum tree_size {MAX_SIZE = 25};

int read_string(char *buffer, size_t buffer_size);
bool is_number(char *str);
bool is_emtpy(char *str);
answer_t ask_question(char *question, check_func check, convert_func convert);
int ask_question_int(char *question);
char *ask_question_string(char *question);
char *ask_question_shelf(char *question);
float ask_question_float(char *question);
bool valid_option(char *str);
char convert_char(char *str);
int ask_question_list(char *question);
char ask_question_char(char *question);
#endif
