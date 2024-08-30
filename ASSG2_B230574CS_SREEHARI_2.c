#include <stdio.h>
#include <stdlib.h>

typedef struct map
{
    int key;
    int value;
} Map;

typedef struct node
{
    Map map;
    int height;
    struct node *left;
    struct node *right;
} Node;

int max(int a, int b)
{
    return a > b ? a : b;
}

Node *createNode(int key, int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->height = 0;
    node->map.key = key;
    node->map.value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int getHeight(Node *n)
{
    if (!n)
        return -1;
    return n->height;
}

int getBalanceFactor(Node *n)
{
    if (!n)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node *Insert(Node *root, int key, int value)
{
    if (!root)
        return createNode(key, value);

    if (key < root->map.key)
        root->left = Insert(root->left, key, value);
    else if (key > root->map.key)
        root->right = Insert(root->right, key, value);
    else {
        root->map.value = value;
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int bf = getBalanceFactor(root);

    if (bf > 1 && key < root->left->map.key)
        return rightRotate(root);
    if (bf > 1 && key > root->left->map.key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && key > root->right->map.key)
        return leftRotate(root);
    if (bf < -1 && key < root->right->map.key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *minVal(Node *node)
{
    while (node && node->left != NULL)
        node = node->left;
    return node;
}
Node *Find(Node *root, int key)
{
    Node *current = root;
    while (current)
    {
        if (key < current->map.key)
            current = current->left;
        else if (key > current->map.key)
            current = current->right;
        else
            return current;
    }
    return NULL;
}

Node *UpperBound(Node *root, int key)
{
    Node *node = Find(root, key);
    if (!node)
    {
        Node *successor = NULL;
        Node *current = root;

        while (current != NULL)
        {
            if (key < current->map.key)
            {
                successor = current;
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            return successor;
        }
    }
    return node;
}

int Size(Node *root)
{
    if (!root)
        return 0;
    return 1 + Size(root->left) + Size(root->right);
}

int Empty(Node *root)
{
    return root == NULL;
}

void DisplayElements(Node *root)
{
    if (!root)
        return;
    DisplayElements(root->right);
    printf("%d ", root->map.key);
    DisplayElements(root->left);
}

int main()
{
    char c;
    int key;
    int value;
    Node *root = NULL;
    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'i':
            scanf("%d %d", &key, &value);
            root = Insert(root, key, value);
            break;
        case 'u':
            scanf("%d", &key);
            Node *upper = UpperBound(root, key);
            if (!upper)
                printf("-1\n");
            else
                printf("%d %d\n", upper->map.key, upper->map.value);
            break;
        case 'f':
            scanf("%d", &key);
            Node *find = Find(root, key);
            if (!find)
                printf("-1\n");
            else
                printf("%d %d\n", find->map.key, find->map.value);
            break;
        case 's':
            printf("%d\n", Size(root));
            break;
        case 'e':
            printf("%d\n", Empty(root));
            break;
        case 'd':
            if (Empty(root))
                printf("-1\n");
            else
                DisplayElements(root);
            printf("\n");
            break;
        case 't':
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
