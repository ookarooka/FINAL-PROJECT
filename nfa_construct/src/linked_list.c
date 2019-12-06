#include "util.h"

void linked(int size, list *linked_list) {
    linked_list->size = size;
    linked_list->length = list_length;
    linked_list->result = (char*)malloc(size * list_length);
}

int adder(list *linked_list, const void *elem) {
    char *place = linked_list->result;
    for (int x = 0; x < linked_list->length; x++, place += linked_list->size)
        if (*((int**)place) == *((int**)elem)) return 0;  
    handleStack(linked_list, elem);
    return 1;
}

void handleStack(list *gl, const void *elem) {
    memcpy(gl->result + gl->size * gl->length++, elem, gl->size);
}

void end(list *linked_list) {linked_list->length = 0;}

void clear(list *linked_list) {free(linked_list->result);}
