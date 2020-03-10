#include <stdlib.h>
#include <stdio.h>
#define arti 43
#define eksi 45
#define carpi 42
#define bolu 47

const int SIZE = 50;
typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

int isEmpty(NODE *head)
{
    return head == NULL;
}
int isFull(NODE *head)
{
    NODE *current = head;
    int num = 0;
    while (current != NULL)
    {
        num++;
        current = current->next;
    }
    return num == SIZE;
}
NODE *push(NODE *head, int data)
{

    if (isEmpty(head))
    {
        head = (NODE *)malloc(sizeof(NODE));
        head->data = data;
        head->next = NULL;
        return head;
    }
    if (!isFull(head))
    {
        NODE *current = (NODE *)malloc(sizeof(NODE));
        current->data = data;
        current->next = head;
        return current;
    }
    return head;
}
NODE *pop(NODE *head, int *value)
{
    if (isEmpty(head))
    {
        return head;
    }
    *value = head->data;
    NODE *tmp = head;
    free(head);
    return tmp->next;
}
int peak(NODE *head)
{
    return head->data;
}
int top(NODE *head)
{
    NODE *current = head;
    int topin = 0;
    while (current != NULL)
    {
        topin++;
        current = current->next;
    }
    return topin - 1;
}
void show(NODE *head)
{
    NODE *current = head;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}
int main()
{
    NODE *head = NULL;

    int value;
    char islem[100] = "5*(4/2+3*6)-7";
    int n = 13;
    char *infix = (char *)malloc(sizeof(char) * 100);
    int i = 0;
    int k = 0;
    char c;
    do
    {
        c = islem[i++]; // (

        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (!isEmpty(head))
            {
                int p = peak(head);
                while (!isEmpty(head) && ((p == c) ||
                                          (c == arti || c == eksi) ||
                                          (c == carpi && p == bolu) ||
                                          (c == bolu && p == carpi)))
                {
                    head = pop(head, &p);
                    *(infix + k++) = p;
                    if (!isEmpty(head))
                        p = peak(head);
                }
            }
            head = push(head, c);
        }
        else
        {
            *(infix + k++) = c;
        }
    } while (i < n);
    while (!isEmpty(head))
    {
        head = pop(head, &value);
        *(infix + k++) = value;
    }

    printf("%s", infix);
    return 0;
}
