#include <stdio.h>
#include <stdlib.h>
typedef struct Counter
{
    int leftCounter;
    int rightCounter;
} Counter;
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
    node->height = 0;
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
Node *rightRotate(Node *y, Counter *counter)
{
    counter->rightCounter++;
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}
void AVL_rotations(Node *root, Counter *counter)
{
    printf("%d %d\n", counter->leftCounter, counter->rightCounter);
}
Node *leftRotate(Node *x, Counter *counter)
{
    counter->leftCounter++;
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}
Node *AVL_insert(Node *root, int value, Counter *counter)
{
    if (!root)
        return createNode(value);

    if (value < root->val)
        root->left = AVL_insert(root->left, value, counter);
    else if (value > root->val)
        root->right = AVL_insert(root->right, value, counter);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = AVL_balanceFactor(root);

    if (bf > 1 && value < root->left->val)
    {
        return rightRotate(root, counter);
    }
    if (bf > 1 && value > root->left->val)
    {
        root->left = leftRotate(root->left, counter);
        return rightRotate(root, counter);
    }
    if (bf < -1 && value > root->right->val)
    {
        return leftRotate(root, counter);
    }
    if (bf < -1 && value < root->right->val)
    {
        root->right = rightRotate(root->right, counter);
        return leftRotate(root, counter);
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
Node *AVL_delete(Node *root, int value, int *printAncestors, Counter *counter)
{
    if (!root)
        return NULL;
    static int succ = 0;
    if (value < root->val)
        root->left = AVL_delete(root->left, value, printAncestors, counter);
    else if (value > root->val)
        root->right = AVL_delete(root->right, value, printAncestors, counter);
    else
    {

        if (*printAncestors)
            printf("%d ", root->val);

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
            int flag = 0;
            Node *temp = minval(root->right);
            root->val = temp->val;
            succ = temp->val;
            root->right = AVL_delete(root->right, temp->val, &flag, counter);
        }
    }
    if (*printAncestors && root->val != succ)
        printf("%d ", root->val);
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = AVL_balanceFactor(root);
    if (bf == 2)
    {
        if (AVL_balanceFactor(root->left) >= 0)
            return rightRotate(root, counter);
        else
        {
            root->left = leftRotate(root->left, counter);
            return rightRotate(root, counter);
        }
    }
    else if (bf == -2)
    {
        if (AVL_balanceFactor(root->right) <= 0)
            return leftRotate(root, counter);
        else
        {
            root->right = rightRotate(root->right, counter);
            return leftRotate(root, counter);
        }
    }

    return root;
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
    Counter *counter = (Counter *)malloc(sizeof(Counter));
    counter->leftCounter = 0;
    counter->rightCounter = 0;

    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'i':
            scanf("%d", &num);
            root = AVL_insert(root, num, counter);
            break;
        case 'd':
        {
            scanf("%d", &num);
            Node *searchNode = AVL_find(root, num);
            if (!searchNode)
            {
                printf("-1");
            }
            else
            {
                int printAncestors = 1;
                root = AVL_delete(root, num, &printAncestors, counter);
            }
            printf("\n");
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
        case 'b':
        {
            scanf("%d", &num);
            Node *node = AVL_find(root, num);
            printf("%d\n", node ? AVL_balanceFactor(node) : -1);
            break;
        }
        case 's':
        {
            AVL_rotations(root, counter);
            break;
        }
        case 'e':
            exit(0);
            break;
        default:
            break;
        }
    }
    free(counter);
    return 0;
}