#define _GNU_SOURCE
#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_number_utils(char *str) {
    int len = strlen(str);
    if (strncmp(str, "-", 1) == 0) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool not_empty(char *str) { return strlen(str) > 0; }

bool is_shelf(char *shelf) {
    if (!isalpha(shelf[0]) || (strlen(shelf) < 2)) {
        return false;
    } else {
        char *end = shelf + 1;  // Skip first char.
        while (*end != '\0') {
            if (!isdigit(*end)) {
                return false;
            }
            ++end;
        }
        return true;
    }
}

bool valid_option(char *str) {
    // http://www.cplusplus.com/reference/cstring/strpbrk/
    char *valid = strpbrk(str, "AaEeRrLlUuSsCcQq");
    if (valid != NULL) {
        return true;
    }
    return false;
}

char convert_char(char *str) {
    char c = str[0];
    return toupper(c);
}
int read_string(char *buffer, size_t buffer_size) {
    int read = getline(&buffer, &buffer_size, stdin);
    // Getline is the modern way of dealing with input:
    // https://www.gnu.org/software/libc/manual/html_node/Line-Input.html
    strtok(buffer, "\n");  // Remove trailing newline.
                           // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
    return read;
}
bool valid_index(char *index) {
    if (!is_number(index)) {
      if (strchr("CPN", toupper(index[0])) != NULL) {
            return true;
        }
        return false;
    } else {
        for (int i = 1; i <= MAX_SIZE; i++) {
            if (i == atoi(index)) {
                return true;
            }
        }
        return false;
    }
}
answer_t ask_question(char *question, check_func check, convert_func convert) {
    size_t buffer_size = 255;
    // Temporary until learning more about memory handling.
    char result[buffer_size];
    int conversation = 0;
    do {
        printf("%s\n", question);
        conversation = read_string(result, buffer_size);
        if (!check(result)) {
            printf("Wrong input. You wrote: %s\n", result);
        }
    } while (!check(result) || (conversation < 2));
    // Empty line is 1 char. Null terminated.
    return convert(result);
}

char *ask_question_shelf(char *question) {
    char *shelf = ask_question(question, is_shelf, (convert_func)strdup).s;
    shelf[0] =
        toupper(shelf[0]);  // Works because is_shelf already verified correct
                            // input.
    return shelf;
}

int ask_question_list(char *question) {
    char *index = ask_question(question, valid_index, (convert_func)strdup).s;
    if (toupper(index[0]) == 'N') {
        free((char *) index);
        return -2;
    }else if (toupper(index[0]) == 'P'){
        free((char *) index);
        return -3;
    }else {
        int val = (toupper(index[0]) == 'C')?-1 :atoi(index);
        free((char *) index);
        return val;
    }
}
bool is_char(char *c){
    return (strlen(c) == 1)?true:false;
}

char ask_question_char(char *question){
    return ask_question(question, is_char, (convert_func)convert_char).c;
}
int ask_question_int(char *question) {
    return ask_question(question, is_number, (convert_func)atoi).i;
}
char *ask_question_string(char *question) {
    return ask_question(question, not_empty, (convert_func)strdup).s;
}
