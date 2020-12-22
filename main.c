#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDSIZE 20

int main(){

    node* root = NULL;

    char* aux = malloc(MAXWORDSIZE);
    mustAlloc(aux, "aux string");

    char* op = NULL; // Qual operação executar
    int value; // Com qual valor executar

    while(fgets(aux, MAXWORDSIZE, stdin)){
        op = strtok(aux, " ");
        value = atoi(strtok(NULL, " "));
        if(!strcmp(op, "i"))
            root = insert(root, value);
        else if(!strcmp(op, "r"))
            root = delete(root, value);
    }
    
    navigate(root, 0); // Imprime os nodos em ordem e suas alturas

    // Libera a memória ocupada por todas as estruturas
    destroy(root);
    root = NULL;
    op = NULL;
    free(aux);
    aux = NULL;

    return 0;
}