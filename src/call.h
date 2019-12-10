#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* List */
typedef struct {
    int size, length, list_length;
    char *result;   
} list;

#define list_length  10
void linked(int size, list *linked_list);
void clear(list *linked_list);
void handleStack(list *linked_list, const void *elem);
int adder(list *linked_list, const void *elem);

/*transitions*/
typedef enum { none, value, l_move } transition_no;

typedef struct {
    transition_no transition_no; 
    char transition_step;       
} next_nfa;

typedef struct start_nfa {
    struct start_nfa *to[2];      
    next_nfa next_state[2]; 
} start_nfa;

typedef struct {
    start_nfa *start, *end; 
} NFA;            

/* Visualization*/
void visualizeDot(const char *reg_exp, const NFA *nfa, FILE *create);

/*Start*/
NFA firstChar(char c);                               

/* Operators */
NFA concatenation(const NFA *A, const NFA *B);     
NFA kleeneClosure(const NFA *A);                
NFA unionOp(const NFA *A);     
