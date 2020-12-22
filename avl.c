#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

void mustAlloc(void* ptr, const char* description){
    if(!ptr){
        fprintf(stderr, "Couldn't allocate memory for %s\n", description);
        exit(1);
    }
}

node* newNode(int key){
    node* n = malloc(sizeof(node));
    mustAlloc(n, "new node");

    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->father = NULL;
    n->height = 1;

    return n;
}

int height(node* n){
    if(n)
        return n->height;

    return 0;
}

// Entre a e b retorna o maior deles
int max(int a, int b){
    return a > b ? a : b;
}

// Desbalanceado a esquerda retorna < 0, desbalanceado a direita retorna > 0
int balance(node* n){
    if(n)
        return height(n->right) - height(n->left);
    
    return 0;
}

node* rotR(node* root){
    if(!root || !root->left)  // Certifica que os elementos necessários a rotação existem
        return root; 

    node* left = root->left;
    node* left_bigChild = left->right;
    
    left->right = root;
    if(left->right)
        left->right->father = left;

    root->left = left_bigChild;
    if(root->left)
        root->left->father = root;

    // Atualiza as alturas dos nodos rotados
    root->height = max(height(root->left), height(root->right)) + 1;
    left->height = max(height(left->left), height(left->right)) + 1;

    return left;
}

node* rotL(node* root){
    if(!root || !root->right) // Certifica que os elementos necessários a rotação existem
        return root; 

    node* right = root->right;
    node* right_smallChild = right->left;

    right->left = root;
    if(right->left)
        right->left->father = right;

    root->right = right_smallChild;
    if(root->right)
        root->right->father = root;

    // Atualiza as alturas dos nodos rotados
    root->height = max(height(root->left), height(root->right)) + 1;
    right->height = max(height(right->left), height(right->right)) + 1;
   
    return right;
}

node* rebalance(node* root){
    root->height = max(height(root->left), height(root->right)) + 1;

    int bal = balance(root);

    if(bal < -1 && balance(root->left) < 0) // Left Left
        return rotR(root);

    if(bal < -1 && balance(root->left) >= 0){ // Left Right
        root->left = rotL(root->left);
        return rotR(root);
    }

    if(bal > 1 && balance(root->right) < 0){  // Right Left
        root->right = rotR(root->right);
        return rotL(root);
    }

    if(bal > 1 && balance(root->right) >= 0) // Right Right
        return rotL(root);

    return root;
}

node* insert(node* root, int key){
    if(!root)
        return newNode(key);
    else if(key > root->key){
        root->right = insert(root->right, key);
        root->right->father = root;
    }        
    else if(key < root->key){
        root->left = insert(root->left, key);
        root->left->father = root;
    }
    else 
        return root;

    return rebalance(root);
}

// Captura o menor da árvore da direita de root
node* successor(node* root){
    node* next = NULL;
    node* n = root->right;

    while(n){
        next = n;
        n = n->left;
    }

    return next;
}

node* delete(node* root, int key){
    if(!root)
        return root;

    if(key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        // Se algum deles for nulo, significa que root tem 1 ou 0 filhos
        if(!root->left || !root->right){
            node* aux = root->left ? root->left : root->right;
            if(!aux){ // 0 filhos
                if(root->father->key > root->key)
                    root->father->left = NULL;
                else
                    root->father->right = NULL;

                free(root);
                root = NULL;
                
                return NULL;
            }
            else { // 1 filho
                *root = *aux;
                delete(aux, aux->key);
            }
            aux = NULL;
        }
        else { // 2 filhos
            node* next = successor(root); // Utiliza o sucessor para substituir
            root->key = next->key;
            delete(next, next->key);
            next = NULL;
        }
    }

    return rebalance(root);
}

void navigate(node* root, int value){
    if(!root) return;
    
    navigate(root->left, value + 1);
    printf("%d,%d\n", root->key, value);
    navigate(root->right, value + 1);
}

void destroy(node* root){
    if(!root) return;
    
    destroy(root->left);
    destroy(root->right);
    free(root);
}