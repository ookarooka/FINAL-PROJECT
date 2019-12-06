#include "util.h"

NFA reg_exp(char**);
NFA start(char**);
NFA nextReg(char**);

NFA reg_exp(char **exp) {
    NFA left, step, right;
    char ch;
    for (left = nextReg(exp);; left = step) {
        ch = **exp;
        if (isalnum(ch) || ch == '(') { 
            right = nextReg(exp);
            step = concatenation(&left, &right);
        }
        else return left;              
    }
    return step;   
}

NFA start(char **exp) {
    NFA step;
    char ch = **exp;
    if (isalnum(ch)) {         
        step = firstChar(ch);
        *exp += 1;     
    }
    else if (ch == '(') {       
        *exp += 1;     
        step = reg_exp(exp);
        if (**exp != ')') {
            fprintf(stderr, "No matching ')' found\n");
            exit(-1);
        }
        *exp += 1;        
    }
    else {
        fprintf(stderr, "Unrecognized Character \"%c\"\n", ch);
        exit(-1);
    }
    return step;
}

NFA nfa_generate(const char *regexp) {
    char **place = (char **)(&regexp);
    NFA nfa = reg_exp(place);
    if (**place != '\0') {
        fprintf(stderr, "Invalid input \"%c\"\n", **place);
        exit(-1);
    }
    return nfa;
}

NFA nextReg(char **exp) {
    NFA left = start(exp), step;
    char ch = **exp;
    if (ch == '*') {            
        step = kleeneClosure(&left);
        *exp += 1;      
    }
    else if (ch == '+') {       
        step = NFA_Union(&left);
        *exp += 1;      
    }
    else return left;           
    return step;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s 'EXPRESSION'\n", argv[0]);
        exit(-1);
    }
    FILE *create = fopen("nfa1.dot", "w");
    if (create == NULL) {
        perror("fopen");
        exit(-1);
    }
    printf("reg_exp: '%s'\n", argv[1]);
    NFA nfa = nfa_generate(argv[1]);     
    visualizeDot(argv[1], &nfa, create);    
    fclose(create);
    return 0;
}