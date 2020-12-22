#ifndef AVL_INCLUDED
#define AVL_INCLUDED

typedef struct avl_node {
    int key;
    int height;
    struct avl_node* left;
    struct avl_node* right;
    struct avl_node* father;
} node;

node* insert(node* root, int key);

node* delete(node* root, int key);

void navigate(node* root, int value);

void destroy(node* root);

int height(node* n);

void mustAlloc(void* ptr, const char* description);

#endif