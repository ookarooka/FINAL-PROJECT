#include "call.h"

start_nfa* step_nfa() {
    next_nfa node = {none, 0};  
    start_nfa *start = malloc(sizeof(start_nfa));
     start->next_state[0] = start->next_state[1] = node;
    start->to[0] = start->to[1] = NULL;
    return start;
}

int transition_nfa(const start_nfa *start) {
    if (start->next_state[1].transition_no != none) return 2;
    if (start->next_state[0].transition_no != none) return 1;
    return 0;
}

int nfa_adder(start_nfa *from, transition_no type, char trans, start_nfa *to) {
    int x = transition_nfa(from);
    if (x >= 2)  return -1;      /* no empty slot avaliable */
    from->next_state[x].transition_no = type;
    from->next_state[x].transition_step = trans;
    from->to[x] = to;
    return 0;
}


NFA firstChar(char c) {
    NFA nfa = {step_nfa(), step_nfa()};
    if (c == '\0') exit(-1);
    nfa_adder(nfa.start, value, c, nfa.end);
    return nfa;
}

int lambda(start_nfa *from, start_nfa *to) {
    return nfa_adder(from, l_move, 0, to);
}

/* Operations */

NFA concatenation(const NFA *A, const NFA *B) {
    NFA C = {A->start, B->end};
    lambda(A->end, B->start);
    return C;
}

NFA kleeneClosure(const NFA *A) {
    NFA C = {step_nfa(), step_nfa()};
    lambda(A->end, C.start);
    lambda(C.start, A->start);
    lambda(C.start, C.end);
    return C;
}

NFA NFA_Union(const NFA *A) {
    NFA C = {step_nfa(), step_nfa()};
    lambda(C.start, A->start);
    lambda(A->end, C.start);
    lambda(A->end, C.end);
    return C;
}

/* Graph Visualization*/

void Edges(const start_nfa *start, int reach_next, FILE *create) {
    switch(start->next_state[reach_next].transition_no) {
    case l_move:     
        fprintf(create, "addr_%p -> addr_%p [ label = \"\u03BB\" ];\n",
            (void*)start, (void*)start->to[reach_next]);
        break;
    case value:
        fprintf(create, "addr_%p -> addr_%p [ label = \"%c\" ];\n",
            (void*)start, (void*)start->to[reach_next],
            start->next_state[reach_next].transition_step);
        break;
    default: abort();  
    }
}

void leave_state(const start_nfa *start, list *marked, FILE *create) {
    for (int x = 0; x < transition_nfa(start); ++x) {
        Edges(start, x, create);  
        if (adder(marked, &start->to[x]) != 0)
            leave_state(start->to[x], marked, create);
    }
}

void visualizeDot(const char *reg_exp, const NFA *nfa, FILE *create) {
    list state_marked;
    linked(sizeof(start_nfa*), &state_marked);
    fprintf(create, "digraph nfa {\n"
        "    labelloc=\"b\";\n    label=\"Regular Expression : %s\";"
        "    rankdir=LR;\n    size=\"10,5\"\n"
        "    node [label=\"\" shape = doublecircle]; addr_%p\n"
        "    node [shape = circle]\n", reg_exp, (void*)nfa->end);
    handleStack(&state_marked, &nfa->start);
    leave_state(nfa->start, &state_marked, create);
    fprintf(create, "    node [label=\"\" shape = point]; start\n");
    fprintf(create, " -> addr_%p [ label = \"\" ]\n}\n",
        (void*)nfa->start);
    clear(&state_marked);
}

void add_states(const start_nfa *start, const char c, list *linked_list) {
    for (int x = 0; x < transition_nfa(start); ++x) {
        if (start->next_state[x].transition_no == l_move)
            adder(linked_list, start->to[x]);
        if (start->next_state[x].transition_step == c)
            adder(linked_list, start->to[x]);
    }
}
