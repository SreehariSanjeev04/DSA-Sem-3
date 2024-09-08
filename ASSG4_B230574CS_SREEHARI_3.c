#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1000
typedef struct Job
{
    int JID;
    int priority;
} Job;

void swap(Job *a, Job *b)
{
    Job temp = *a;
    *a = *b;
    *b = temp;
}
void min_heapify(Job heap[], int length, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < length && heap[smallest].priority > heap[left].priority)
    {
        smallest = left;
    }
    if (right < length && heap[smallest].priority > heap[right].priority)
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(&heap[smallest], &heap[i]);
        min_heapify(heap, length, smallest);
    }
}
void Add(Job pq[], int *n, int JID, int p)
{
    pq[*n].JID = JID;
    pq[*n].priority = p;
    (*n)++;
    int i = *n - 1;
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (pq[parent].priority > pq[i].priority)
        {
            swap(&pq[parent], &pq[i]);
            i = parent;
        }
        else
        {
            break;
        }
    }
}
void Schedule(Job pq[], int *n)
{
    if(*n  == 0) {
        printf("-1\n");
        return;
    }
    Job job = pq[0];
    swap(&pq[0], &pq[*n - 1]);
    (*n)--;
    min_heapify(pq, *n, 0);
    printf("%d\n",job.JID);
}
void Next_Job(Job pq[], int n)
{
    if(n == 0)
        printf("-1\n");
    else 
        printf("%d\n",pq[0].JID);
}
void Replace_Priority(Job pq[], int n, int JID, int np)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (pq[i].JID == JID)
        {
            break;
        }
    }
    if (i == n)
    {
        printf("-1\n");
        return;
    }
    if (pq[i].priority < np)
    {
        pq[i].priority = np;
        min_heapify(pq, n, i);
    }
    else
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (pq[i].priority > pq[parent].priority)
            {
                swap(&pq[parent], &pq[i]);
                i = parent;
            }
            else
                break;
        }
    }
}
void Display(Job pq[], int n) {
    if(n == 0){
        printf("-1\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        printf("%d %d\n",pq[i].JID,pq[i].priority);
    }
}
int main() {
    char c;
    int JID;
    int p;
    Job pq[MAX_SIZE];
    int n = 0;
    while(1) {
        scanf(" %c",&c);
        switch (c)
        {
        case 'a':
            scanf("%d %d",&JID,&p);
            Add(pq,&n,JID,p);
            break;
        case 'b':
            Schedule(pq,&n);
            break;
        case 'c':
            Next_Job(pq,n);
            break;
        case 'd':
            scanf("%d %d",&JID,&p);
            Replace_Priority(pq,n,JID,p);
            break;
        case 'e':
            Display(pq,n);
            break;
        case 'g':
            exit(0);
            break;
        default:
            break;
        }
    }
}