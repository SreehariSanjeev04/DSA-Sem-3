#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node
{
    int key;
    struct Node *next;
} Node;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

int hashFunction(int key, int MAX_SIZE)
{
    return key % MAX_SIZE;
}

int search(Node *hashTable[], int key, int MAX_SIZE)
{
    int index = hashFunction(key, MAX_SIZE);
    Node *current = hashTable[index];
    int position = 1;
    while (current != NULL && current->key != key)
    {
        current = current->next;
        position++;
    }
    if (current == NULL)
        return -1;
    return position;
}

void insert(Node *hashTable[], int key, int MAX_SIZE)
{
    int index = hashFunction(key, MAX_SIZE);
    if (hashTable[index] == NULL)
    {
        hashTable[index] = createNode(key);
    }
    else
    {
        Node *current = hashTable[index];
        while (current->next != NULL && current->next->key < key)
        {
            current = current->next;
        }
        Node *newNode = createNode(key);
        newNode->next = current->next;
        current->next = newNode;
    }
}

void delete(Node *hashTable[], int key, int MAX_SIZE)
{
    int index = hashFunction(key, MAX_SIZE);
    if(hashTable[index] == NULL)
        return;
    if (hashTable[index]->key == key)

    {
        Node *temp = hashTable[index];
        hashTable[index] = hashTable[index]->next;
        free(temp);
        return;
    }

    Node *current = hashTable[index];
    int position = 1;
    while (current->next != NULL && current->next->key != key)
    {
        current = current->next;
        position++;
    }
    if (current->next == NULL)
    {
        return;
    }
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void update(Node *hashTable[], int oldKey, int newKey, int MAX_SIZE)
{
    int index = hashFunction(oldKey,MAX_SIZE);
    int pos = search(hashTable, oldKey,MAX_SIZE);
    delete (hashTable, oldKey,MAX_SIZE);
    insert(hashTable, newKey,MAX_SIZE);
    printf("%d %d\n", index, pos);
}

void printElementsInChain(Node *hashTable[], int index, int MAX_SIZE)
{
    if (index < 0 || index >= MAX_SIZE || hashTable[index] == NULL)
    {
        printf("-1\n");
        return;
    }
    Node *current = hashTable[index];
    while (current != NULL)
    {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

int main()
{   
    int MAX_SIZE;
    scanf("%d", &MAX_SIZE);
    Node *hashTable[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        hashTable[i] = NULL;
    }
    char c;
    int n;
    int p;
    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'f':
            return 0;
        case 'a':
            scanf("%d", &n);
            if (search(hashTable, n, MAX_SIZE) != -1)
                printf("-1\n");
            else
                insert(hashTable, n, MAX_SIZE);
            break;
        case 'b':
        {
            scanf("%d", &n);
            int index = hashFunction(n, MAX_SIZE);
            int pos = search(hashTable, n, MAX_SIZE);
            if (pos == -1)
                printf("-1\n");
            else
                printf("%d %d\n", index, pos);
            break;
        }
        case 'c':
        {
            scanf("%d", &n);
            int index = hashFunction(n, MAX_SIZE);
            if (!hashTable[index])
                printf("-1\n");

            else
            {
                printf("%d %d\n", index, search(hashTable, n, MAX_SIZE));
                delete (hashTable, n, MAX_SIZE);
            }
            break;
        }
        case 'e':
            scanf("%d", &n);
            printElementsInChain(hashTable, n, MAX_SIZE);
            break;
        case 'd':
            scanf("%d %d", &n, &p);
            if (search(hashTable, n, MAX_SIZE) == -1 || search(hashTable, p, MAX_SIZE) != -1)
                printf("-1\n");
            else
                update(hashTable, n, p, MAX_SIZE);
            break;
        default:
            break;
        }
    }

    return 0;
}
