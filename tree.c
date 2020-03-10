#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} NODE;
NODE *insert(NODE *root, int data)
{
    if (root == NULL)
    {
        printf("%d root oldu\n", data);
        NODE *root = (NODE *)malloc(sizeof(NODE));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else
    {

        if (data > root->data)
        {
            if (root->right == NULL)
            {
                printf("%d nin sagina %d eklendi\n", root->data, data);
                NODE *node = (NODE *)malloc(sizeof(NODE));
                node->data = data;
                node->left = NULL;
                node->right = NULL;
                root->right = node;
            }
            else
                insert(root->right, data);
        }
        else if (data < root->data)
        {
            if (root->left == NULL)
            {
                printf("%d nin soluna %d  eklendi\n", root->data, data);

                root->left = (NODE *)malloc(sizeof(NODE));
                root->left->data = data;
                root->left->left = NULL;
                root->left->right = NULL;
            }
            else
                insert(root->left, data);
        }
    }
    return root;
}
NODE *minBul(NODE *root)
{
    NODE *current = root->right;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
NODE *delete (NODE *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = delete (root->left, data);

    else if (data > root->data)
        root->right = delete (root->right, data);
    else
    {
        if (root->left == NULL)
        {
            NODE *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            NODE *temp = root->left;
            free(root);
            return temp;
        }

        NODE *temp = minBul(root);

        root->data = temp->data;

        root->right = delete (root->right, temp->data);
    }
    return root;
}
void inorder(NODE *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d\n", root->data);
    inorder(root->right);
}
void preorder(NODE *root)
{
    if (root == NULL)
        return;
    printf("%d\n", root->data);
    preorder(root->left);
    preorder(root->right);
}
void postorder(NODE *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d\n", root->data);
}
int main()
{
    NODE *root = NULL;
    root = insert(root, 12);
    root = insert(root, 9);
    root = insert(root, 54);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 37);
    root = insert(root, 62);
    root = insert(root, 2);
    root = insert(root, 11);
    root = insert(root, 41);
    root = insert(root, 57);
    root = insert(root, 1);
    root = insert(root, 42);
    root = insert(root, 36);
    root = insert(root, 40);
    root = insert(root, 39);
    root = insert(root, 38);
    // root = delete (root, 12);

    inorder(root);
    printf("\n\n\n");
    preorder(root);
    printf("\n\n\n");
    postorder(root);
    return 0;
}