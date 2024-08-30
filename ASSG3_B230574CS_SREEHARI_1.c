#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 4

typedef struct StudentName
{
    char name[50];
    char rollNumber[11];
    int age;
} StudentName;

typedef struct Node
{
    StudentName student;
    struct Node *next;
} Node;

Node *studentNode(StudentName student)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->student = student;
    newNode->next = NULL;
    return newNode;
}


int hashFunction(char name[], int age)
{
    if (name == NULL || strlen(name) == 0) 
        return -1;

    int sum = 0;
    while (*name != '\0')
    {
        sum += (int)*name;
        name++;
    }
    return (sum + age) % MAX_SIZE; 
}

void insertIntoHash(StudentName student, Node *hashTable[])
{
    int index = hashFunction(student.name, student.age);
    if (index == -1)
    {
        return;
    }

    if (hashTable[index] == NULL)
    {
        hashTable[index] = studentNode(student);
    }
    else
    {
        Node *current = hashTable[index];
        while (current->next != NULL && strcmp(current->next->student.name, student.name) < 0)
        {
            current = current->next;
        }
        Node *newNode = studentNode(student);
        newNode->next = current->next;
        current->next = newNode;
    }
}
void insertIntoHashWithIndex(StudentName student, Node *hashTable[], int index)
{
    if (hashTable[index] == NULL)
    {
        hashTable[index] = studentNode(student);
    }
    else
    {
        Node *current = hashTable[index];
        while (current->next != NULL && strcmp(current->next->student.name, student.name) < 0)
        {
            current = current->next;
        }
        Node *newNode = studentNode(student);
        newNode->next = current->next;
        current->next = newNode;
    }
}
Node *findStudentByName(Node *hashTable[], int index, char *name)
{
    Node *current = hashTable[index];
    while (current != NULL)
    {
        if (strcmp(current->student.name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
int GroupIndexAndSplit(char name[], Node *hashTable[])
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (findStudentByName(hashTable, i, name) != NULL)
            return i;
    }
    return -1;

}
void GroupCountAndList(Node *hashTable[], int k)
{
    int count = 0;
    Node *current = hashTable[k];
    if (!current) {
        printf("0\n");
        return;
    }

    while (current)
    {
        count++;
        current = current->next;
    }
    printf("%d ", count);
    current = hashTable[k];
    while (current)
    {
        printf("%s ", current->student.name);
        current = current->next;
    }
    printf("\n");
}
void StudentDetails(char rollnumber[], Node *hashTable[])
{
    Node *node = NULL;
    Node *current;
    char branch[3];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        current = hashTable[i];
        while (current != NULL)
        {
            if (strcmp(current->student.rollNumber, rollnumber) == 0)
            {
                node = current;
                break;
            }
            current = current->next;
        }
        if (node)
            break;
    }
    if (node)
    {
        branch[0] = node->student.rollNumber[7];
        branch[1] = node->student.rollNumber[8];
        branch[2] = '\0';
        printf("%s %d %s\n", node->student.name, node->student.age, branch);
    }
    else
        printf("-1\n");
}
void Group_ListByBranch(Node *hashTable[], int m, char branch[])
{
    Node *current = hashTable[m];
    if (!current)
    {
        printf("-1\n");
        return;
    }
    int count = 0;
    while (current)
    {
        if (tolower(current->student.rollNumber[7]) == tolower(branch[0]) && tolower(current->student.rollNumber[8]) == tolower(branch[1]))
            count++;
        current = current->next;
    }
    if (count == 0)
    {
        printf("-1\n");
        return;
    }
    current = hashTable[m];
    while (current)
    {
        if (tolower(current->student.rollNumber[7]) == tolower(branch[0]) && tolower(current->student.rollNumber[8]) == tolower(branch[1]))
            printf("%s ", current->student.name);
        current = current->next;
    }
    printf("\n");
}
void Group_TransferAllByBranch(Node *hashTable[], int source, int target, char branch[])
{
    Node *current = hashTable[source];
    Node *prev = NULL;
    int count = 0;

    while (current)
    {
        if (tolower(current->student.rollNumber[7]) == tolower(branch[0]) && tolower(current->student.rollNumber[8]) == tolower(branch[1]))
        {
            count++;
            Node *temp = current;
            if (prev == NULL)
            {
                hashTable[source] = current->next;
                current = current->next;
            }
            else
            {
                prev->next = current->next;
                current = current->next;
            }
            insertIntoHashWithIndex(temp->student, hashTable,target);
            free(temp);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    printf("%d\n", count);
}

int main()
{
    Node *hashTable[MAX_SIZE] = {NULL};
    int n;
    char name[50];
    char branch[3];
    char rollnumber[11];
    int m;
    int k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        StudentName student;
        scanf("%s %s %d", student.name, student.rollNumber, &student.age);
        insertIntoHash(student, hashTable);
    }
    char c;
    while(1) {
        scanf(" %c",&c);
        switch (c)
        {
        case 'a':
            scanf("%s",name);
            printf("%d\n",GroupIndexAndSplit(name, hashTable));
            break;
        case 'b':
            scanf("%d",&k);
            GroupCountAndList(hashTable, k);
            break;
        case 'c':
            scanf("%d %s",&k, branch);
            Group_ListByBranch(hashTable, k, branch);
            break;
        case 'd':
            scanf("%s",rollnumber);
            StudentDetails(rollnumber, hashTable);
            break;
        case 'e':
            scanf("%d %d %s",&m, &k, branch);
            Group_TransferAllByBranch(hashTable, m, k, branch);
            break;
        case 'f':  
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}
