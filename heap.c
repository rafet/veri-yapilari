#include <stdio.h>
#include <stdlib.h>

void insert(int heap[], int data, int *location)
{
    int root = ((*location - 1) / 2) - 1;
    if (data < heap[root])
    {
        heap[*location - 1] = data;
    }
    else
    {
        heap[*location - 1] = heap[root];
        heap[root] = data;
    }
    (*location)++;
}
void maxHeapfy(int mix[], int i, int n)
{
    int largest = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    if (left < n && mix[left] > mix[largest])
        largest = left;

    if (right < n && mix[right] > mix[largest])
        largest = right;

    if (largest != i)
    {
        int tmp = mix[i];
        mix[i] = mix[largest];
        mix[largest] = tmp;
        maxHeapfy(mix, largest, n);
    }
}
void heapSort(int mix[], int n)
{
    int i;
    for (i = n - 1; i >= 1; i--)
    {
        int tmp = mix[0];
        mix[0] = mix[i];
        mix[i] = tmp;
        maxHeapfy(mix, 0, i);
    }
}
void createHeap(int mix[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapfy(mix, i, n);
}
int main()
{
    static int mix[100] = {20, 10, 15, 58, 8, 7, 30, 5, 3, 4};
    createHeap(mix, 6);
    heapSort(mix, 6);
    for (int i = 0; i < 6; i++)
    {
        printf("%d  ", mix[i]);
    }
    return 0;
}