#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX_SIZE 100

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
} Node;

typedef struct queue {
    Node* queue[MAX_SIZE];
    int front;
    int rear;
} Queue;

int max(int a, int b) {
    return a > b ? a : b;
}
Queue* initializeQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = -1;
    return queue;
}

void enqueue(Node* value, Queue* queue) {
    if (queue->rear == MAX_SIZE - 1) {
        printf("Overflow\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->rear++;
    queue->queue[queue->rear] = value;
}

Node* dequeue(Queue* queue) {
    if (queue->front == -1) {
        printf("Underflow\n");
        return NULL;
    }
    Node* node = queue->queue[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return node;
}

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* buildTree(int preorder[], int hashedInorder[], int preStart, int preEnd, int inStart, int inEnd) {
    if (preEnd < preStart || inEnd < inStart) return NULL;

    Node* root = createNode(preorder[preStart]);
    int rootIdx = hashedInorder[root->val];
    int numsLeft = rootIdx - inStart;
    root->left = buildTree(preorder, hashedInorder, preStart + 1, preStart + numsLeft, inStart, rootIdx - 1);
    root->right = buildTree(preorder, hashedInorder, preStart + numsLeft + 1, preEnd, rootIdx + 1, inEnd);
    return root;
}

int depthOfTree(Node* root) {
    if (!root) return 0;
    int left = depthOfTree(root->left);
    int right = depthOfTree(root->right);
    return left > right ? left + 1 : right + 1;
}

void preOrder(Node* root) {
    if (!root) return;
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

void hashInorder(int arr[], int size, int hashMap[]) {
    for (int i = 0; i < size; ++i) {
        hashMap[arr[i]] = i;
    }
}
int isLeaf(Node* root) {
    return !root->left && !root->right;
}

int* Diameter(Node* root) {
    int* pair = (int*)malloc(2 * sizeof(int));
    if (!root) {
        pair[0] = 0;
        pair[1] = 0;
        return pair;
    }
    int* leftPair = Diameter(root->left);
    int* rightPair = Diameter(root->right);
    int op1 = leftPair[0];
    int op2 = rightPair[0];
    int op3 = leftPair[1] + rightPair[1];
    pair[0] = max(op1, max(op2, op3));
    pair[1] = max(leftPair[1], rightPair[1]) + 1;
    free(leftPair);
    free(rightPair);
    return pair;
}

int RightLeafSum(Node* root) {
    if (!root) return 0;
    int sum = 0;
    if (root->right) {
        if(isLeaf(root->right)) sum += root->right->val;
    }
    sum += RightLeafSum(root->left);
    sum += RightLeafSum(root->right);
    return sum;
}
void LevelMax(Node* root) {
    if (!root) return;

    Queue* queue = initializeQueue();
    enqueue(root, queue);

    while (queue->front != -1) {
        int size = queue->rear - queue->front + 1;
        int maxVal = INT_MIN; 

        for (int i = 0; i < size; i++) {
            Node* node = dequeue(queue);

            if (node->left) {
                enqueue(node->left, queue);
            }
            if (node->right) {
                enqueue(node->right, queue);
            }

            if (node->val > maxVal) {
                maxVal = node->val;
            }
        }

        printf("%d ", maxVal);
    }

    printf("\n");
    free(queue);
}
void ZIG_ZAG(Node* root) {
    if (!root) return;
    Queue* queue = initializeQueue();
    enqueue(root, queue);
    int leftToRight = 0;
    while (queue->front != -1) {
        int size = queue->rear - queue->front + 1;
        int arr[size];
        for (int i = 0; i < size; i++) {
            Node* node = dequeue(queue);
            if (leftToRight) {
                arr[i] = node->val;
            } else {
                arr[size - 1 - i] = node->val;
            }
            if (node->left) {
                enqueue(node->left, queue);
            }
            if (node->right) {
                enqueue(node->right, queue);
            }
        }
        leftToRight = !leftToRight;
        for(int j=0;j<size;j++) {
            printf("%d ",arr[j]);
        }
    }
    printf("\n");

    free(queue->queue);
    free(queue);
}
void PostOrder(Node* root) {
    if(!root) return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ",root->val);
}

int main() {
    int n;
    int inorder[MAX_SIZE];
    int preorder[MAX_SIZE];
    int hashedInorder[MAX_SIZE];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&inorder[i]);
    for(int i=0;i<n;i++) scanf("%d",&preorder[i]);
    hashInorder(inorder,n,hashedInorder);
    Node* root = buildTree(preorder, hashedInorder, 0, n-1, 0, n-1);
    char c;
    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'p':
            PostOrder(root);
            printf("\n");
            break;
        case 'z':
            ZIG_ZAG(root);
            break;
        case 'm':
            LevelMax(root);
            break;
        case 'd': {
            int* pair = Diameter(root);
            printf("%d\n",pair[0] + 1);
            break;
        }
        case 's': {
            int r = RightLeafSum(root);
            printf("%d\n",r);
            break;
        }
        case 'e':
            exit(0);
            break;
        default:
            printf("Invalid option, try again!\n");
            break;
        }
    }
    
    
    return 0;
}
