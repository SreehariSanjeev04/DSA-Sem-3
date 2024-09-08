#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1000

typedef struct Patient
{
    char name[100];
    int pid;
    int severity;
} Patient;

void swap(Patient *a, Patient *b)
{
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(Patient heap[], int length, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < length && heap[smallest].severity > heap[left].severity)
    {
        smallest = left;
    }
    if (right < length && heap[smallest].severity > heap[right].severity)
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(&heap[smallest], &heap[i]);
        min_heapify(heap, length, smallest);
    }
}

void AdmitPatient(Patient pq[], int *n, int pid, char name[], int severity)
{
    pq[*n].pid = pid;
    strcpy(pq[*n].name, name);
    pq[*n].severity = severity;
    int i = *n;
    (*n)++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (pq[parent].severity > pq[i].severity)
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

Patient TreatPatient(Patient pq[], int *n)
{
    Patient minPriority = pq[0];
    swap(&pq[0], &pq[*n - 1]);
    (*n)--;
    min_heapify(pq, *n, 0);
    return minPriority;
}

void UpdateSeverity(Patient pq[], int n, int pid, int new_severity)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (pq[i].pid == pid)
        {
            break;
        }
    }
    if (pq[i].severity < new_severity)
    {
        pq[i].severity = new_severity;
        min_heapify(pq, n, i);
    }
    else
    {
        pq[i].severity = new_severity;
        while (i > 0 && pq[i].severity < pq[(i - 1) / 2].severity)
        {
            swap(&pq[i], &pq[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

void QueryPatient(Patient pq[], int n, int pid)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (pq[i].pid == pid)
        {
            printf("%s %d\n", pq[i].name, pq[i].severity);
            return;
        }
    }
    printf("-1\n");
}

void FindMostSevere(Patient pq[], int n)
{
    if(n==0) {
        printf("-1\n");
        return;
    }
    int length = n;
    Patient heap[n];
    for (int i = 0; i < n; i++)
    {
        heap[i] = pq[i];
    }
    if (n < 3)
    {
        for (int i = 0; i < n; i++)
        {
            Patient patient = TreatPatient(heap, &length);
            printf("%d %s %d\n", patient.pid, patient.name, patient.severity);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            Patient patient = TreatPatient(heap, &length);
            printf("%d %s %d\n", patient.pid, patient.name, patient.severity);
        }
    }
}

void PrintLevelOrder(Patient pq[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pq[i].pid);
    }
    printf("\n");
}

int main()
{
    Patient pq[MAX_SIZE];
    int n = 0;
    char c;
    char name[100];
    int pid;
    int severity;
    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'a':
            scanf("%d %d %s", &pid, &severity, name);
            AdmitPatient(pq, &n, pid, name, severity);
            PrintLevelOrder(pq, n);
            break;
        case 'b':
        {
            if (n == 0)
            {
                printf("-1\n");
                break;
            }
            else
            {
                Patient patient = TreatPatient(pq, &n);
                printf("%d %s\n", patient.pid, patient.name);
            }
            break;
        }
        case 'c':
        {
            scanf("%d %d", &pid, &severity);
            int flag = 0;
            for (int i = 0; i < n; i++)
            {
                if (pq[i].pid == pid)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                UpdateSeverity(pq, n, pid, severity);
                PrintLevelOrder(pq, n);
            }
            else
                printf("-1\n");
            break;
        }
        case 'd':
            scanf("%d", &pid);
            QueryPatient(pq, n, pid);
            break;
        case 'e':
            FindMostSevere(pq, n);
            break;
        default:
            return 0;
        }
    }
}
