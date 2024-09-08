#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1000
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int heap[], int length, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < length && heap[largest] < heap[left])
    {
        largest = left;
    }
    if (right < length && heap[largest] < heap[right])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(&heap[largest], &heap[i]);
        max_heapify(heap, length, largest);
    }
}

void DeleteKey(int heap[], int *n, int key)
{
    int i;
    for (i = 0; i < *n; i++)
    {
        if (heap[i] == key)
            break;
    }
    if (i == *n)
    {
        printf("-1\n");
        return;
    }

    heap[i] = heap[*n - 1];
    (*n)--;

    if (heap[i] < key)
    {
        max_heapify(heap, *n, i);
    }
    else
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] < heap[i])
            {
                swap(&heap[parent], &heap[i]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    if (*n == 0)
    {
        printf("0\n");
    }
}

void InsertKey(int heap[], int *n, int key)
{
    heap[*n] = key;
    int i = *n;
    (*n)++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap[parent] < heap[i])
        {
            swap(&heap[parent], &heap[i]);
            i = parent;
        }
        else
        {
            break;
        }
    }
}

int ExtractMax(int heap[], int *n)
{
    if (*n == 0)
    {
        return -1;
    }
    int maxVal = heap[0];
    swap(&heap[0], &heap[*n - 1]);
    (*n)--;
    max_heapify(heap, *n, 0);
    return maxVal;
}

void PrintLevelOrder(int heap[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int KthLargest(int heap[], int n, int k)
{
    if (k > n)
    {
        return -1;
    }
    int length = n;
    int arr[length];
    for (int i = 0; i < n; i++)
        arr[i] = heap[i];

    while (k > 1)
    {
        ExtractMax(arr, &n);
        k--;
    }
    return ExtractMax(arr, &n);
}

int FindMax(int heap[], int n)
{
    if (n == 0)
        return -1;
    return heap[0];
}

void ReplaceKey(int heap[], int n, int oldKey, int newKey)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (heap[i] == oldKey)
            break;
    }
    if (i == n)
    {
        printf("%d\n", abs(oldKey - newKey));
        return;
    }
    heap[i] = newKey;
    if (newKey < oldKey)
    {
        max_heapify(heap, n, i);
    }
    else
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] < heap[i])
            {
                swap(&heap[parent], &heap[i]);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }
}

int main()
{
    char c;
    int n;
    int k;
    int heap[MAX_SIZE];
    int size = 0;
    while (1)
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'a': {
            scanf("%d", &n);
            int findKey = -1;
            for(int i = 0; i < size; i++) {
                if (heap[i] == n)
                {
                    findKey = i;
                    break;
                }
            }
            if(findKey == -1) InsertKey(heap, &size, n);
            break;
        }
        case 'b':
            printf("%d\n", FindMax(heap, size));
            break;
        case 'c':
            printf("%d ", ExtractMax(heap, &size));
            if (size)
                PrintLevelOrder(heap, size);
            else
                printf("\n");
            break;
        case 'd':
            scanf("%d", &k);
            printf("%d\n", KthLargest(heap, size, k));
            break;
        case 'e':
        {
            scanf("%d", &n);
            int findKey = -1;
            for (int i = 0; i < size; i++)
            {
                if (heap[i] == n)
                {
                    findKey = i;
                    break;
                }
            }
            DeleteKey(heap, &size, n);
            if (size && findKey != -1)
                PrintLevelOrder(heap, size);
            break;
        }
        case 'f':
        {
            scanf("%d %d", &n, &k);
            int findKey = -1;
            for (int i = 0; i < size; i++)
            {
                if (heap[i] == n)
                {
                    findKey = i;
                    break;
                }
            }
            ReplaceKey(heap, size, n, k);
            if (size && findKey != -1)
                PrintLevelOrder(heap, size);
            break;
        }
        case 'g':
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
