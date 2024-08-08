#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct node {
    int model_number;
    char* model_name;
    int model_price;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

Node* Create_Node(int model_number, char* model_name, int model_price) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->model_number = model_number;
    node->model_name = (char*)malloc((strlen(model_name) + 1) * sizeof(char));
    strcpy(node->model_name, model_name);
    node->model_price = model_price;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void Add(Node** root, Node* node) {
    if(!(*root)) {
        *root = node;
        return;
    }
    Node* parent = NULL;
    Node* current = *root;
    while(current != NULL) {
        parent = current;
        if(node->model_number < current->model_number) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    node->parent = parent;
    if(node->model_number < parent->model_number) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

void Transplant(Node** root, Node* u, Node* v) {
    if (u->parent == NULL) {
        *root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

Node* Minimum(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void Delete(Node** root, Node* z) {
    if (z->left == NULL) {
        Transplant(root, z, z->right);
    } else if (z->right == NULL) {
        Transplant(root, z, z->left);
    } else {
        Node* y = Minimum(z->right);  
        if (y->parent != z) {
            Transplant(root, y, y->right);
            y->right = z->right;
            if (y->right != NULL) {
                y->right->parent = y;
            }
        }
        Transplant(root, z, y);
        y->left = z->left;
        if (y->left != NULL) {
            y->left->parent = y;
        }
    }
    free(z->model_name); 
    free(z);  
}

Node* Search(Node* root, int model_number) {
    Node* current = root;
    while(current != NULL) {
        if(current->model_number > model_number) current = current->left;
        else if(current->model_number < model_number) current = current->right;
        else return current;
    }
    return NULL; //current is NULL, no node found -_-
}

void Inorder(Node* root) {
    if(!root) return;
    Inorder(root->left);
    printf("%d %s %d\n",root->model_number,root->model_name,root->model_price);
    Inorder(root->right);
}

void Preorder(Node* root) {
    if(!root) return;
    printf("%d %s %d\n",root->model_number,root->model_name,root->model_price);
    Preorder(root->left);
    Preorder(root->right);
}

void Postorder(Node* root) {
    if(!root) return;
    Postorder(root->left);
    Postorder(root->right);
    printf("%d %s %d\n",root->model_number,root->model_name,root->model_price);
}

void Modify(Node* root, int model_number, int new_price) {
    Node* searchedNode = Search(root, model_number);
    if(!searchedNode){
        printf("-1\n");
        return;
    }
    searchedNode->model_price = new_price;
    printf("%d %s %d\n",searchedNode->model_number,searchedNode->model_name,searchedNode->model_price);
}

int main() {
    char c;
    int num;
    char model_name[MAX_SIZE];
    int price;
    Node* root = NULL;
    while(1) {
        scanf(" %c", &c);
        switch (c) {
        case 'a': {
            scanf("%d %99s %d", &num, model_name, &price);
            Node* node = Create_Node(num, model_name, price);
            Add(&root, node);
            break;
        }
        case 'p':
            Preorder(root);
            break;
        case 'd': {
            
            scanf("%d", &num);
            Node* deleteNode = Search(root, num);
            if(!deleteNode) printf("-1\n");
            else Delete(&root, deleteNode);
            break;
        }
        case 's': {
            
            scanf("%d", &num);
            Node* node = Search(root, num);
            if(node) {
                printf("%d %s %d\n",node->model_number,node->model_name,node->model_price);
            } else {
                printf("-1\n");
            }
            break;
        }
        case 'i':
            Inorder(root);
            break;
        case 't':
            Postorder(root);
            break;
        case 'm': {
            int new_price;
            scanf("%d %d",&num,&new_price);
            Modify(root,num,new_price);
            break;
        }
        case 'e':
            exit(0);
            break;
        default:
            printf("Invalid command.\n");
            break;
        }
    }
}
