#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 100
typedef struct node
{
    int height;
    int val;
    struct node *left;
    struct node *right;
} Node;

Node *minVal(Node *root)
{
    if (!root)
        return NULL;
    Node *current = root;
    while (current && current->left)
        current = current->left;
    return current;
}
Node *maxVal(Node *root)
{
    if (!root)
        return NULL;
    Node *current = root;
    while (current && current->right)
        current = current->right;
    return current;
}

int getHeight(Node *n)
{
    if (!n)
        return -1;
    return n->height;
}
int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
void Preorder(Node *root)
{
    if (!root)
        return;
    printf("%d ", root->val);
    Preorder(root->left);
    Preorder(root->right);
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
    for (int i = 0; i < size; i++)
    {
        root = AVL_insert(root, arr[i]);
    }
    return root;
}

void TreeToParanthesis(Node *root)
{
    if (!root)
    {
        return;
    }
    if (!root->left && !root->right)
    {
        printf("%d ", root->val);
        return;
    }
    printf("%d ", root->val);
    printf("( ");
    TreeToParanthesis(root->left);
    printf(") ");
    printf("( ");
    TreeToParanthesis(root->right);
    printf(") ");
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

Node *Successor(Node *root, Node *n)
{
    if (n->right)
        return minVal(n->right);
    Node *successor = NULL;
    while (root)
    {
        if (n->val < root->val)
        {
            successor = root;
            root = root->left;
        }
        else if (n->val > root->val)
            root = root->right;
        else
            break;
    }
    return successor;
}
Node *Predecessor(Node *root, Node *n)
{
    if (n->left)
        return maxVal(n->left);
    Node *predecessor = NULL;
    while (root)
    {
        if (n->val < root->val)
            root = root->left;
        else if (n->val > root->val)
        {
            predecessor = root;
            root = root->right;
        }
        else
            break;
    }
    return predecessor;
}

int AVL_SubtreeSum(Node *root, Node *node)
{
    if (!node || !root)
    {
        return -1;
    }
    int leftSum = 0;
    int rightSum = 0;

    if (node->left)
    {
        leftSum = AVL_SubtreeSum(root, node->left);
    }
    if (node->right)
    {
        rightSum = AVL_SubtreeSum(root, node->right);
    }

    return node->val + leftSum + rightSum;
}

void AVL_SuccessorPath(Node *root, int n)
{
    if (!root)
        return;
    Node *node = AVL_find(root, n);
    if (!node)
    {
        printf("%d", root->height);
        return;
    }
    Node *successor = Successor(root, node);
    if (!successor)
    {
        printf("%d", root->height);
        return;
    }
    Node *current = root;
    while (current)
    {
        printf("%d ", current->val);
        if (current->val < successor->val)
        {
            current = current->right;
        }
        else if (current->val > successor->val)
            current = current->left;
        else
            break;
    }
}

void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

Node *BUILD_TREE(char **str)
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
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

Node *AVL_delete(Node *root, int value)
{
    if (!root)
        return NULL;
    if (value < root->val)
        root->left = AVL_delete(root->left, value);
    else if (value > root->val)
        root->right = AVL_delete(root->right, value);
    else
    {
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
            Node *temp = minVal(root->right);
            root->val = temp->val;
            root->right = AVL_delete(root->right, temp->val);
        }
    }

    if (!root)
        return NULL;

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

Node *AVL_RangeDelete(Node *root, int n1, int n2, int *count)
{
    if (!root)
        return NULL;

    root->left = AVL_RangeDelete(root->left, n1, n2, count);
    root->right = AVL_RangeDelete(root->right, n1, n2, count);

    if (n1 <= root->val && root->val <= n2)
    {
        root = AVL_delete(root, root->val);
        (*count)++;
    }
    if (root)
    {
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
    }
    return root;
}
int AVL_FindClosest(Node *root, int n)
{
    Node *node = AVL_find(root, n);
    if (node)
    {
        Node *successor = Successor(root, node);
        Node *predecessor = Predecessor(root, node);

        if (!successor && predecessor)
            return predecessor->val;
        else if (successor && !predecessor)
            return successor->val;
        else if (!successor && !predecessor)
            return -1;
        else
        {
            if (abs(successor->val - n) == abs(predecessor->val - n))
                return predecessor->val;
            else if (abs(successor->val - n) > abs(predecessor->val - n))
            {
                return predecessor->val;
            }
            else
                return successor->val;
        }
    }
    return -1;
}

int main()
{
    int c;
    int num;
    char *string = (char *)malloc(MAX_SIZE * sizeof(char));
    fgets(string, MAX_SIZE, stdin);
    char *trimmed_string = (char *)malloc((strlen(string) + 1) * sizeof(char));
    removeSpaces(trimmed_string, string);
    Node *root = BUILD_TREE(&trimmed_string);
    char input[MAX_SIZE];
    while (1)
    {
        fgets(input, MAX_SIZE, stdin);
        c = input[0];
        if (c == 'a')
        {
            int arr[MAX_SIZE];
            int i = 0;
            char *token = strtok(input + 1, " ");
            while (token != NULL)
            {
                arr[i++] = atoi(token);
                token = strtok(NULL, " ");
            }
            root = AVL_SeqInsert(root, arr, i);
            TreeToParanthesis(root);
            printf("\n");
        }
        else if (c == 'b')
        {
            int arr[2];
            int i = 0;
            int count = 0;
            char *token = strtok(input + 1, " ");
            while (token != NULL)
            {
                arr[i++] = atoi(token);
                token = strtok(NULL, " ");
            }
            root = AVL_RangeDelete(root, arr[0], arr[1], &count);
            if (count == 0)
                printf("-1\n");
            else
            {
                printf("%d ", count);
                Preorder(root);
                printf("\n");
            }
        }

        else if (c == 'c')
        {
            int n;
            char *token = strtok(input + 1, " ");
            if (token != NULL)
                n = atoi(token);
            AVL_SuccessorPath(root, n);
            printf("\n");
        }
        else if (c == 'd')
        {
            int n;
            char *token = strtok(input + 1, " ");
            if (token != NULL)
                n = atoi(token);
            Node *node = AVL_find(root, n);
            int sum = AVL_SubtreeSum(root, node);
            printf("%d ", sum);
            if (node && root)
                TreeToParanthesis(node);
            printf("\n");
        }
        else if (c == 'e')
        {
            int n;
            char *token = strtok(input + 1, " ");
            if (token != NULL)
                n = atoi(token);
            Node *node = AVL_find(root, n);
            if (!root || !node)
                printf("-1\n");
            else
            {
                printf("%d\n", AVL_FindClosest(root, n));
            }
        }
        else if (c == 'g')
        {
            exit(0);
        }

        else
        {
            continue;
        }
    }

    free(trimmed_string);

    return 0;
}

