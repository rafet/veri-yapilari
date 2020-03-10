#include <stdlib.h>
#include <stdio.h>

typedef struct queue
{
    int q[10];
    int front;
    int rear;
} Queue;
int isFull(Queue *sira)
{
    return ((sira->rear + 1) % 10 == sira->front);
}
int isEmpty(Queue *sira)
{
    return sira->rear == sira->front;
}
void insert(Queue *sira, int data)
{
    if (!isFull(sira))
    {
        sira->q[(sira->rear)] = data;
        sira->rear++;
        sira->rear = sira->rear % 10;
    }
}
void delete (Queue *sira)
{
    if (!isEmpty(sira))
    {
        if (sira->rear + 1 != sira->front)
        {
            sira->front++;
            sira->front = sira->front % 10;
        }
    }
}

int peek(Queue *sira)
{
    return sira->q[sira->front];
}
void show(Queue *sira)
{
    int i;
    if (sira->front > sira->rear)
    {
        for (i = sira->front; i < (10 + sira->rear); i++)
        {
            printf("%d ", sira->q[i % 10]);
        }
    }
    else
        for (i = sira->front; i < sira->rear; i++)
        {
            printf("%d ", sira->q[i]);
        }
    printf("\n%d %d", sira->front, sira->rear);
}
int main()
{
    Queue *sira = (Queue *)malloc(sizeof(Queue));
    sira->front = 0;
    sira->rear = 0;

    insert(sira, 3);
    insert(sira, 9);
    insert(sira, 7);
    insert(sira, 6);
    delete (sira);
    delete (sira);
    delete (sira);
    delete (sira);
    insert(sira, 34);
    insert(sira, 67);
    insert(sira, 54);
    show(sira);
    return 0;
}