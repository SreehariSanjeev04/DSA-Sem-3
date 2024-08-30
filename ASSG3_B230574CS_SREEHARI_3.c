#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void sieveOfEratosthenes(int bool[], int key)
{
    for (int i = 0; i <= key; i++)
    {
        bool[i] = 1;
    }
    bool[0] = bool[1] = 0;
    for (int p = 2; p * p <= key; p++)
    {
        if (bool[p] == 1)
        {
            for (int i = p * p; i <= key; i += p)
                bool[i] = 0;
        }
    }
}

int hashFunction(int key, int capacity)
{
    return key % capacity;
}

int secondaryHashFunction(int key, int R)
{
    return R - (key % R);
}

int linearProbingHF(int key, int capacity, int collision)
{
    int hf = hashFunction(key, capacity);
    return (hf + collision) % capacity;
}

int quadraticProbingHF(int key, int capacity, int collision)
{
    int hf = hashFunction(key, capacity);
    return (hf + collision * collision) % capacity;
}

int doubleHF(int key, int capacity, int collision, int R)
{
    return (hashFunction(key, capacity) + collision * secondaryHashFunction(key, R)) % capacity;
}

void LinearProbing(int hashTable[], int arr[], int m, int n, int *col)
{
    int collision;
    for (int i = 0; i < m; i++)
    {
        collision = 0;
        int index = hashFunction(arr[i], n);
        if (hashTable[index] == INT_MIN)
        {
            printf("%d ", index);
            hashTable[index] = arr[i];
        }
        else
        {
            while (hashTable[linearProbingHF(arr[i], n, collision)] != INT_MIN)
                collision++;
            printf("%d ", linearProbingHF(arr[i], n, collision));
            hashTable[linearProbingHF(arr[i], n, collision)] = arr[i];
        }
        *col = *col + collision;
    }
}

void QuadraticProbing(int hashTable[], int arr[], int m, int n, int *col)
{
    int collision;
    for (int i = 0; i < m; i++)
    {
        collision = 0;
        int index = hashFunction(arr[i], n);
        if (hashTable[index] == INT_MIN)
        {
            printf("%d ", index);
            hashTable[index] = arr[i];
        }
        else
        {
            while (hashTable[quadraticProbingHF(arr[i], n, collision)] != INT_MIN)
                collision++;
            printf("%d ", quadraticProbingHF(arr[i], n, collision));
            hashTable[quadraticProbingHF(arr[i], n, collision)] = arr[i];
        }
        *col = *col + collision;
    }
}

void DoubleHashing(int hashTable[], int arr[], int m, int n, int R, int *col)
{
    int collision;
    for (int i = 0; i < m; i++)
    {
        collision = 0;
        int index = hashFunction(arr[i], n);
        if (hashTable[index] == INT_MIN)
        {
            printf("%d ", index);
            hashTable[index] = arr[i];
        }
        else
        {
            while (hashTable[doubleHF(arr[i], n, collision, R)] != INT_MIN)
                collision++;
            printf("%d ", doubleHF(arr[i], n, collision, R));
            hashTable[doubleHF(arr[i], n, collision, R)] = arr[i];
        }
        *col = *col + collision;
    }
}

int main()
{
    int n, m, R;
    int collision = 0;

    scanf("%d %d", &n, &m);

    int boolArray[n + 1];
    int hashTable[n];
    int arr[m];

    if (boolArray == NULL || hashTable == NULL || arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        hashTable[i] = INT_MIN;
    }

    sieveOfEratosthenes(boolArray, n);
    for (int i = 2; i < n; i++)
    {
        if (boolArray[i])
        {
            R = i;
        }
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &arr[i]);
    }

    while (1)
    {
        char c;
        collision = 0;

        scanf(" %c", &c);
        switch (c)
        {
        case 'a':
            LinearProbing(hashTable, arr, m, n, &collision);
            printf("\n%d\n", collision);
            for (int i = 0; i < n; i++)
            {
                hashTable[i] = INT_MIN;
            }
            break;
        case 'b':
            QuadraticProbing(hashTable, arr, m, n, &collision);
            printf("\n%d\n", collision);
            for (int i = 0; i < n; i++)
            {
                hashTable[i] = INT_MIN;
            }
            break;
        case 'c':
            DoubleHashing(hashTable, arr, m, n, R, &collision);
            printf("\n%d\n", collision);
            for (int i = 0; i < n; i++)
            {
                hashTable[i] = INT_MIN;
            }
            break;
        case 'd':
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}
