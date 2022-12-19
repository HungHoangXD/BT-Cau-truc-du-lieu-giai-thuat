/*
Queue Implementation using a Linked List 
Mô tả vào/ra:
    - Input: Order of nodes entering and leaving a queue
    - Output: Result queue
Mô tả thuật toán:
    // front, rear: the front and rear node of queue
    function enqueue(int num)
    {
        Node* p = new Node; 
        p->data = num; p->link = NULL;
        if (p == NULL) return;
        if (front == NULL)
        {
            front = rear = p;
        }
        else
        {
            rear->link = p;
            rear = p;
        }
    }
    function dequeue()
    {
        if (front == NULL) return;
        Node* p = front;
        front = p->link;
        if (front == NULL)
        {
            rear = NULL;
        }
        delete p;
    }
*/
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* link;
};

struct Queue
{
    Node *front, *rear;
};

void init_queue(Queue* Q)
{
    Q->front = Q->rear = NULL;
}

Node* create_node(int num)
{
    Node* p = new Node;
    if (p == NULL) return NULL;
    p->data = num;
    p->link = NULL;
    return p;
}

void enqueue(Queue* Q, int num)
{
    Node* p = create_node(num);
    if (p == NULL) return;
    if (Q->front == NULL)
    {
        Q->front = Q->rear = p;
    }
    else
    {
        Q->rear->link = p;
        Q->rear = p;
    }
}

int dequeue(Queue* Q)
{
    if (Q->front == NULL) return 0;
    Node* p = Q->front;
    Q->front = p->link;
    if (Q->front == NULL)
    {
        Q->rear = NULL;
    }
    int num = p->data;
    delete p;
    return num;
}

void print_queue(Queue Q)
{
    if (Q.front == NULL)
    {
        cout << "Queue is empty";
        return;
    }
    cout << "Print queue from front:\n";
    Node* p = Q.front;
    while (p != Q.rear)
    {
        cout << p->data << " -> ";
        p = p->link;
    }
    cout << p->data;
}

void input_queue(Queue* Q)
{
    int num = 1;
    cout << "Type numbers to enqueue, type -1 to dequeue, type 0 to end:\n";
    while (num != 0)
    {
        cin >> num;
        if (num == 0) break;
        if (num == -1) 
        {
            dequeue(Q);
        }
        else
        {
            enqueue(Q, num);
        }
    }
}

int main()
{
    Queue Q;
    init_queue(&Q);
    input_queue(&Q);
    print_queue(Q);
}