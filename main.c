#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define COUNT 10
void print2D(node* root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 

    // Increase distance between levels 
    space += COUNT; 

    // Process right child first 
    print2D(root->right, space); 

    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->key); 

    // Process left child 
    print2D(root->left, space); 
}

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

    print2D(root, 0);
    
    navigate(root, 0); // Imprime os nodos e suas alturas em ordem

    // Libera a memória ocupada por todas as estruturas
    destroy(root);
    root = NULL;
    op = NULL;
    free(aux);
    aux = NULL;

    return 0;
}