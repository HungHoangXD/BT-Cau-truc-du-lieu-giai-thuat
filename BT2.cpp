// Bài toán Josephus
#include <iostream>
#include <ctime>
using namespace std;

struct Node
{
    int number;
    Node* next;
};

void insert_people(int x, Node* y)
{
    Node* p = new Node;
    if (p == NULL) return;
    p->number = x;
    p->next = y->next;
    y->next = p;
}

void delete_next_people(Node* y)
{
    Node* p = y->next;
    y->next = p->next;
    p->next = NULL;
    free(p);
}

int Josephus(int N, int M)
{
    Node* p = new Node;
    int k = 0;
    p->number = 1;
    p->next = p;

    for (int i = 2; i <= N; i++)
    {
        insert_people(i, p);
        p = p->next;
    }

    while (p != p->next)
    {
        if (k == M)
        {
            delete_next_people(p);
            k = 0;
        }
        else 
        {
            k++;
            p = p->next;
        }
    }
    return p->number;
}

int main()
{
    int N, M;
    clock_t start, end;
    cout << "Nhap N va M:\n";
    cin >> N >> M;
    start = clock();
    cout << "Nguoi chien thang la so " << Josephus(N, M);
    end = clock();
    cout << "\nThoi gian: " << (double) (end-start) / CLOCKS_PER_SEC << "s";
}
// Độ phức tạp thuật toán với M=1 là O(N)