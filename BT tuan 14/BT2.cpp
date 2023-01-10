#include <iostream>
using namespace std;

template <class type>

class BTree
{
private:
    struct Node
    {
        type data;
        Node *left, *right;
        Node(type d)
        {
            Node(d, NULL, NULL);
        }
        Node(type d, Node* l, Node* r)
        {
            data = d; 
            left = l; 
            right = r;
        }
    };
    Node* root;

public:
    void InitBTree()
    {
        root == NULL;
    }
    
    // function to find the parent of a given node P
    Node* FindParent(Node* P)
    {
        if (P == root) return NULL;
        else return FindParent(P, root);
    }
    Node* FindParent(Node* P, Node* r)
    {
        if (r == NULL) return NULL;
        if (r->left == P || r->right == P) return r;
        Node* a = FindParent(P, r->left);
        if (a != NULL) return a;
        Node* b = FindParent(P, r->right);
        return b;
    }

    // function to insert element x as the father of given node P
    void InsertParent(type x, Node* P)
    {
        Node* h = new Node(x);
        Node* f = FindParent(P);
        if (f != NULL)
        {
            if (f->left == P) f->left = h;
            else f->right = h;
        }
        else root = h;
        h->left = P;
    }

    void InsertLeftChild(type x, Node* P)
    {
        Node* h = new Node(x);
        h->left = P->left;
        P->left = h;
    }
    void InsertRightChild(type x, Node* P)
    {
        Node* h = new Node(x);
        h->right = P->right;
        P->right = h;
    }

    // function to find a node with given data x
    Node* FindNode(type x)
    {
        return FindNode(x, root);
    }
    Node* FindNode(type x, Node* r)
    {
        if (r == NULL) return NULL;
        if (r->data == x) return r;
        Node* a = FindNode(x, r->left); 
        if (a != NULL) return a;
        Node* b = FindNode(x, r->right);
        return b;
    }

    // function to find the leftmost node of a subtree
    Node* leftmost(Node* t)
    {
        Node* p = t;
        while (p->left != nullptr)
            p = p->left;
        return p;
    }

    // function to delete a node
    void DeleteCurrentNode(Node* P)
    {
        if (P == root) 
        {
            delete(P);
            root = NULL;
            return;
        }
        Node* f = FindParent(P);

        // P is leaf node
        if (P->left == NULL && P->right == NULL) 
        {
            if (f->left == P) f->left = NULL;
            else f->right = NULL;
            delete(P);
        }

        // P has one child
        else if (P->left == NULL) 
        {
            if (f->left == P) f->left = P->right;
            else f->right = P->right;
            delete(P);
        }
        else if (P->right == NULL) 
        {
            if (f->left == P) f->left = P->left;
            else f->right = P->left;
            delete(P);
        }

        // P has two children
        else
        {
            Node* c = leftmost(P->right);
            P->data = c->data;
            DeleteCurrentNode(c);
        }
    }

    void DeleteLeftChild(Node* P)
    {
        if (P->left != NULL) 
            DeleteCurrentNode(P->left);
    }
    void DeleteRightChild(Node* P)
    {
        if (P->right != NULL) 
            DeleteCurrentNode(P->right);
    }

    int GetSize()
    {
        return GetSize(root);
    }
    int GetSize(Node* r)
    {
        if (r == NULL) return 0;
        int m = GetSize(r->left);
        int n = GetSize(r->right);
        return 1 + m + n;
    }
};

int main()
{
}
