#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    char letter;
    int frequency;
    struct node *left, *right, *next;

} Node;

////////////// Queue Operations
/// Queue yapısını en son tree'yi ekrana basmak için kullanıyoruz
typedef struct queue
{
    Node *q[100];
    int rear, front;
} Queue;
void enqueue(Queue *q, Node *node)
{
    q->q[q->front++] = node;
}
Node *dequeue(Queue *q)
{
    return q->q[q->rear++];
}
int isEmpty(Queue *q)
{
    return q->front - q->rear == 1;
}

//////////////

/*
 * Function:  createNode 
 * --------------------
 * Node oluşturmak için gerekli parametreleri alır ve bellekte 
 * yer açıp pointer'ı geri döndürür
 *
 *  letter: Node'u temsil eden harf
 *  freq: Harfin frekansı
 *
 *  returns: Node* : Node için açılan yerin adresi.
 */
Node *createNode(char letter, int freq)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->letter = letter;
    node->frequency = freq;
    node->next = NULL;
    node->right = NULL;
    node->left = NULL;
    return node;
}

/*
 * Function:  insertSorted 
 * --------------------
 * Linkli listemize node'ları sıralı bir şekilde ekler.
 *
 *  head: Listenin ilk node'u
 *  newNode: Eklenecek node
 *
 *  returns: Node* : Listenin yeni head pointer'ı
 */
Node *insertSorted(Node *head, Node *newNode)
{
    if (head == NULL || newNode->frequency < head->frequency)
    {
        // Listemiz henüz boşsa ya da gelen yeni değer head değerinden küçükse
        // yeni node'u listenin başına ekleriz ve head olarak geri döndürürüz
        newNode->next = head;
        return newNode;
    }

    // Insertion Sort algoritmasına dayanarak sırali bir listeye bir eleman eklerken
    // listeyi baştan taramaya başlarız. Elimizdeki değerden büyük bir değere denk geldiğimiz zaman
    // eklemek istediğimiz node'u büyük node'un soluna ekleriz
    Node *cur = head;
    while (cur->next != NULL && cur->next->frequency <= newNode->frequency)
        cur = cur->next;

    // Eğer elimizdeki değerden büyük bir değer yoksa node'u listenin soluna ekleriz
    if (cur->next != NULL)
    {
        Node *tmp = cur->next;
        newNode->next = tmp;
    }

    cur->next = newNode;
    return head;
}

/*
 * Function:  calcFrequencies 
 * --------------------
 * Elimizdeki yazıdaki harflerin frekansını hesaplar.
 *
 *  word: Frekansı hesaplanacak yazı.
 *
 *  returns: int* : Frekansları içinde bulunduran int pointer'ı.
 */
int *calcFrequencies(char word[])
{
    // frekansların ilk değerleri 0 olacağı için static anahtar kelimesini kullandık.
    static int freqs[26], i;
    for (i = 0; i < strlen(word); i++)
        // her bir harften 'a' karakterinin ascii değerini çıkararak harflerin
        // dizide karşılık gelen indislerini buluyoruz ve 1 artırıyoruz.
        freqs[word[i] - 'a']++;
    return freqs;
}

/*
 * Function:  printList 
 * --------------------
 * Listeyi ekrana yazar.
 *
 *  head: Listenin head'i.
 */
void printList(Node *head)
{
    Node *cur = head;
    while (cur != NULL)
    {
        printf("%c: %d\t", cur->letter, cur->frequency);
        cur = cur->next;
    }
}

/*
 * Function:  fillLinkedList 
 * --------------------
 * Elimizdeki frekans değerlerini linked list'e ekler.
 *
 *  head: Listenin head'i.
 *  word: Frekansı hesaplanacak yazı.
 * 
 *  returns: Node* : linked list'in head pointer'ı.
 */
Node *fillLinkedList(Node *head, char *word)
{
    int i;
    int *frequencies = calcFrequencies(word);
    for (i = 0; i < 26; i++)
        if (frequencies[i] != 0) // kelimeden geçmeyen harfleri es geçiyoruz
            head = insertSorted(head, createNode(i + 'a', frequencies[i]));
    return head;
}

/*
 * Function:  treefy 
 * --------------------
 * Huffman algoritamsı kullanarak linked list'i tree yapısına çevirir.
 *
 *  head: Listenin head'i.
 * 
 *  returns: Node* : linked list'in head pointer'ı.
 */
Node *treefy(Node *head)
{
    // root adında yeni bir node oluşturup, bu node'a head (left) ve head->next (right) frekanslarını toplayıp atıyoruz.
    // Root'u node ekler gini insertSorted fonksiyonuna gönderiyoruz ve listemize ekliyoruz.
    Node *leftNode = head,
         *rightNode = head->next,
         *root = createNode(0, leftNode->frequency + rightNode->frequency);
    root->left = leftNode;
    root->right = rightNode;
    insertSorted(head, root);
    return rightNode->next;
}

/*
 * Function:  printTree 
 * --------------------
 * Tree'nin her seviyesini ayrı ayrı ekrana yazdırır.
 *
 *  head: Listenin head'i.
 */
void printTree(Node *head)
{
    // Tree yapısını ekrana bastırmak için Queue yapısından faydalanıyoruz.
    // İlk olarak sıranın ilk elemanı olarak listemizin head'ini ekliyoruz.
    // Her seviye bittiği zaman sıraya bir NULL ekliyoruz. Dolayısıyla head'i ekledikten
    // sonra sıraya bir NULL ekliyoruz.
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;

    enqueue(queue, head);
    enqueue(queue, NULL);

    Node *node = NULL;

    while (!isEmpty(queue))
    {
        do
        {
            // Sıradan bir eleman alıyoruz.
            // eleman NULL değil ise ekrana yazıp sol ve sağ node'larını (eğer varsa) sıraya ekleriz.
            Node *node = dequeue(queue);
            if (node != NULL)
            {
                printf("%d%c ", node->frequency, node->letter);
                if (node->left != NULL)
                    enqueue(queue, node->left);
                if (node->right != NULL)
                    enqueue(queue, node->right);
            }
            // Node NULL ise seviyedeki bütün elemanları yazmışız demektir.
            // Seviye bittiği için alt satıra geçeriz ve seviyenin bittiğini belirtmek için
            // Sıraya bir NULL daha ekleriz.
            else
            {
                printf("\n");
                enqueue(queue, NULL);
            }
        } while (node != NULL);
    }
}

int main()
{
    char *word = "aebabcbade";
    Node *head = fillLinkedList(head, word);
    while (head->next != NULL)
        head = treefy(head);
    printTree(head);
    return 0;
}