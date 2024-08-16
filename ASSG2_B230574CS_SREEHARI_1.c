#include <stdio.h>
#include <stdlib.h>
int rightCounter = 0;
int leftCounter = 0;
typedef struct node
{
    int val;
    int height;
    struct node *left;
    struct node *right;
} Node;
int getHeight(Node *n)
{
    if (!n)
        return -1;
    return n->height;
}
Node *createNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->height = 1;
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
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
int AVL_balanceFactor(Node *n)
{
    if (!n)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}
int max(int a, int b)
{
    return a > b ? a : b;
}
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}
void AVL_rotations(Node* root) {
    printf("%d %d\n",leftCounter,rightCounter);
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

    if (bf > 1 && value < root->left->val) {
        rightCounter++;
        return rightRotate(root);
    }
    if (bf > 1 && value > root->left->val)
    {   
        leftCounter++;
        rightCounter++;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && value > root->right->val) {
        leftCounter++;
        return leftRotate(root);
    }
    if (bf < -1 && value < root->right->val)
    {
        rightCounter++;
        leftCounter++;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *minval(Node *root)
{
    Node *current = root;
    while (current && current->left)
        current = current->left;
    return current;
}
Node *AVL_delete(Node *root, int value, int *printAncestors)
{
    if (!root)
        return NULL;

    if (*printAncestors)
        printf("%d ", root->val);

    if (value < root->val)
        root->left = AVL_delete(root->left, value, printAncestors);
    else if (value > root->val)
        root->right = AVL_delete(root->right, value, printAncestors);
    else
    {
        if (*printAncestors)
            printf("%d ", root->val);
        *printAncestors = 0;

        if (!root->left)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            Node *temp = minval(root->right);
            root->val = temp->val;
            root->right = AVL_delete(root->right, temp->val, printAncestors);
        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int bf = AVL_balanceFactor(root);
        if (bf == 2)
        {
            if (AVL_balanceFactor(root->left) >= 0)
                return rightRotate(root);
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        else if (bf == -2)
        {
            if (AVL_balanceFactor(root->right) <= 0)
                return leftRotate(root);
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }

        return root;
    }
}
void AVL_postorder(Node *root)
{
    if (!root)
        return;
    AVL_postorder(root->left);
    AVL_postorder(root->right);
    printf("%d ", root->val);
}
int main()
{
    char c;
    int num;
    Node *root = NULL;
    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'i':
            scanf("%d", &num);
            root = AVL_insert(root, num);
            break;
        case 'd':
        {
            scanf("%d", &num);
            int printAncestors = 1;
            root = AVL_delete(root, num, &printAncestors);
            break;
        }
        case 'p':
            AVL_postorder(root);
            printf("\n");
            break;
        case 'f':
        {
            scanf("%d", &num);
            Node *node = AVL_find(root, num);
            if (node)
            {
                Node *current = root;
                while (current)
                {
                    printf("%d ", current->val);
                    if (current->val > num)
                        current = current->left;
                    else if (current->val < num)
                        current = current->right;
                    else
                        break;
                }
                printf("\n");
            }
            else
                printf("-1\n");
            break;
        }
        case 'b': {
            scanf("%d", &num);
            Node *node = AVL_find(root, num);
            printf("%d\n", node ? AVL_balanceFactor(node) : -1);
            break;
        }
        case 's': {
            AVL_rotations(root);
            break;
        }
        case 'e':
            exit(0);
            break;
        default:
            break;
        }
    }
}