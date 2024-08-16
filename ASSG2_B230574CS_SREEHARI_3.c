#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int height;
    int val;
    struct node *left;
    struct node *right;
} Node;
int getHeight(Node *n)
{
    if (!n)
        return -1;
    return n->height;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int AVL_balanceFactor(Node *n)
{
    if (!n)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}
Node *createNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->height = 0;
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}
Node *AVL_insert(Node *root, int value)
{
    if (!root)
        return createNode(value);

    if (value < root->val)
        root->left = AVL_insert(root->left, value);
    else if (value > root->val)
        root->right = AVL_insert(root->right, value);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = AVL_balanceFactor(root);

    if (bf > 1 && value < root->left->val)
    {
        return rightRotate(root);
    }
    if (bf > 1 && value > root->left->val)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && value > root->right->val)
    {
        return leftRotate(root);
    }
    if (bf < -1 && value < root->right->val)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
Node *AVL_SeqInsert(Node *root, int arr[], int size)
{
    if (!root)
        return NULL;
    for (int i = 0; i < size; i++)
    {
        root = AVL_insert(root,arr[i]);
    }
    return root;
}
void TreeToParanthesis(Node *root)
{
    if (!root)
        return;
    //leaf node
    if(!root->left && !root->right) {
        printf("%d",root->val);
        return;
    }
    printf("%d", root->val);
    printf("(");
    TreeToParanthesis(root->left);
    printf(")");
    printf("(");
    TreeToParanthesis(root->right);
    printf(")");
}
void removeSpaces(char *trimmed_string, const char *untrimmed_string)
{
    while (*untrimmed_string != '\0')
    {
        if (*untrimmed_string != ' ')
        {
            *trimmed_string = *untrimmed_string;
            trimmed_string++;
        }
        untrimmed_string++;
    }
    *trimmed_string = '\0';
}
Node *AVL_find(Node *root, int k)
{
    if (!root)
        return NULL;
    Node *current = root;
    while (current)
    {
        if (k < current->val)
            current = current->left;
        else if (k > current->val)
            current = current->right;
        else
            return current;
    }
    return NULL;
}
Node* Successor(Node* root, Node* n) {
    if(n->right)
        return minValue(n->right);
    Node* successor = NULL;
    while(root)
        if(n->val < root->val) {
            successor = root;
            root = root->left;

        }
        else if(n->val > root->val)
            root = root->right;
        else 
            break;
    return successor;
}
Node* AVL_SuccessorPath(Node* root, int n) {
    Node* node = AVL_find(root,n);
    if(!node)
        return NULL;
    return Successor(root,node);
    // Dont forget to print the path too
}
void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}
Node *BUILD_TREE(const char **str)
{
    if (**str == '\0' || **str == ')')
        return NULL;
    int key = 0;
    while (**str >= '0' && **str <= '9')
    {
        key = key * 10 + (**str - '0');
        (*str)++;
    }
    Node *node = createNode(key);
    if (**str == '(')
    {
        (*str)++;
        node->left = BUILD_TREE(str);
        (*str)++;
    }
    if (**str == '(')
    {
        (*str)++;
        node->right = BUILD_TREE(str);
        (*str)++;
    }

    return node;
}

void freeTree(Node *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    char *string = "23(10(9(7)())(15(11)(17)))(45(30)(67))";
    char *trimmed_string = (char *)malloc((strlen(string) + 1) * sizeof(char));
    removeSpaces(trimmed_string, string);
    int position = 0;
    const char *str = trimmed_string;
    Node *root = BUILD_TREE(&str);
    int arr[] = {4,14,21};
    root = AVL_SeqInsert(root,arr,3);
    TreeToParanthesis(root);
    freeTree(root);
    free(trimmed_string);

    return 0;
}
