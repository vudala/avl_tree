#ifndef AVL_INCLUDED
#define AVL_INCLUDED

typedef struct avl_node {
    int key; // Chave
    int bal; // Fator de balanceamento
    struct avl_node* left; // Filho da esquerda
    struct avl_node* right; // Filho da direita
    struct avl_node* father; // Pai
} node;

node* insert(node* root, int key);

node* delete(node* root, int key);

void navigate(node* root, int value);

void destroy(node* root);

void mustAlloc(void* ptr, const char* description);

#endif