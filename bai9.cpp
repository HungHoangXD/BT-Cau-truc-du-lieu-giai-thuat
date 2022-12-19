/*
Rearrange linked list in increasing order (Sort linked list)
Mô tả vào/ra: 
    - Input: A linked list
    - Output: A linked list sorted in increasing order
Mô tả thuật toán: 
// first: the first node of given list
function sort_list()
{
    Node* p = first->link;
    first->link = NULL;   // make a new list start from first node
    while (p != NULL)   // insert each node to the new list
    {
        Node* next = p->link;   // note the next node before we change p->link
        if (p->data < first->data)
        {
            Add p at beginning of list and change first to p;
        }
        else
        {
            Node* x = first;
            while (x->link != NULL && x->link->data < p->data)   // find correct position to insert p
            {
                x = x->link; 
            }
            Insert p after x;
        }
        p = next;   // move to next node
    }
}
*/
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* link;
};

struct List
{
    Node *first, *last;
};

Node* create_node(int num)
{
    Node* p = new Node;
    if (p == NULL) return NULL;
    p->data = num;
    p->link = NULL;
    return p;
}

void init_list(List* list)
{
    list->first = list->last = NULL;
}

void attach_node(List* list, int num)
{
    Node* p = create_node(num);
    if (p == NULL) return;
    if (list->first == NULL)
    {
        list->first = list->last = p;
    }
    else
    {
        list->last->link = p;
        list->last = p;
    }
}

void print_list(List list)
{
    cout << "Print list:\n";
    Node* p = list.first;
    while (p != NULL)
    {
        cout << p->data << " -> ";
        p = p->link;
    }
    cout << "NULL";
}

void input_list(List* list)
{
    int num = 1;
    cout << "Type the numbers (type 0 to end):\n";
    while (num != 0)
    {
        cin >> num;
        if (num == 0) break;
        attach_node(list, num);
    }
}

void insert_node_sorted(List* list, Node* p)
{
    if (p->data < list->first->data)
    {
        p->link = list->first;
        list->first = p;
    }
    else
    {
        Node* x = list->first;
        while (x->link != NULL && x->link->data < p->data)
        {
            x = x->link;
        }
        p->link = x->link;
        x->link = p;
    }
}

void sort_list(List* list)
{
    Node *p = list->first->link, *next;
    list->first->link = NULL;
    while (p != NULL)
    {   
        next = p->link;
        insert_node_sorted(list, p);
        p = next;
    }
}

int main()
{
    List list;
    init_list(&list);
    input_list(&list);
    sort_list(&list);
    print_list(list);
}