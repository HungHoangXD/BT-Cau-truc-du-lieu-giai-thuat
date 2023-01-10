#include <iostream>
using namespace std;

struct Node
{
    int sbd;     
    string hoTen; 
    Node *left;   
    Node *right;

    // Ham tao.
    Node(int s, string h, Node *l, Node *r)
    {
        sbd = s;
        hoTen = h;
        left = l;
        right = r;
    }
};

// Lop cay nhi phan tim kiem.
class BSTree
{
private:
    Node *root;
public:                                       
    BSTree() { root = NULL; }                 
    ~BSTree() { makeEmpty(); }                
    bool isEmpty() { return (root == NULL); } 
    void makeEmpty() { makeEmpty(root); }   

    void insert(int sbd, string hoTen)        
    {
        return insert(sbd, hoTen, root);
    } 
    Node *search(int sbd)
    {
        return search(sbd,root);
    }
    void printTree(ostream& out = cout) const{
        return printTree(root,out);
    };
    Node* deleteNode(int sbd)
    {
        return deleteNode(sbd,root);
    }
   
    // xoa rong cay
    void makeEmpty(Node *&t)
    {
        if (t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }

    // Chen mot sinh vien moi vao cay (viet theo kieu de quy).
    void insert(int sbd, string hoTen, Node *&t)
    {
        if (t == NULL) // Cay dang rong thi nut moi se thanh nut goc
            t = new Node(sbd, hoTen, NULL, NULL);
        else if (sbd < t->sbd)
            insert(sbd, hoTen, t->left);
        else if (sbd > t->sbd)
            insert(sbd, hoTen, t->right);
        else
            ;
    }

    // Tim sinh vien theo so bao danh (viet theo kieu de quy).
    Node *search(int sbd, Node *t)
    {
        if (t == NULL)
        {
            cout << "Khong co sinh vien so " << sbd << endl;
            return NULL;
        }
        if (sbd < t->sbd)
            return search(sbd, t->left);
        else if (sbd > t->sbd)
            return search(sbd, t->right);
        else
        {
            cout << "Tim thay sinh vien so " << sbd << endl;
            return t;
        }
    }

    void printTree(Node *t, ostream &out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->sbd << "-" << t->hoTen << endl;
            printTree(t->right, out);
        }
    }

    // Tim node be nhat trong mot cay
    Node* minNode(Node* t)
    {
        Node* p = t;
        while (p->left != nullptr)
            p = p->left;
        return p;
    }

    // Xoa mot node trong cay
    Node* deleteNode(int sbd, Node* t)
    {
        if (t == NULL) return NULL;
        if (sbd < t->sbd)
            t->left = deleteNode(sbd, t->left);
        else if (sbd > t->sbd)
            t->right = deleteNode(sbd, t->right);
        else  // sbd == t->sbd
        {
            // node with no child: remove the node
            if (t->left == NULL && t->right == NULL)
            {
                delete(t);
                return NULL;
            }
            
            // node with one child: remove the node and replace it with its child
            else if (t->left == NULL) 
            {
                Node* p = t->right;
                delete(t);
                return p;
            }
            else if (t->right == NULL) 
            {
                Node* p = t->left;
                delete(t);
                return p;
            }

            // node with two children: copy data of its inorder successor then remove the successor
            else
            {
                Node* p = minNode(t->right);  // get the smallest node in its right subtree
                t->sbd = p->sbd;  // copy data
                t->hoTen = p->hoTen;
                t->right = deleteNode(p->sbd, t->right);  // delete the successor
            }
        }
        return t;
    }
};

int main()
{
    BSTree bst; 
    bst.insert(5, "Tuan");
    bst.insert(6, "Lan");
    bst.insert(3, "Cong");
    bst.insert(8, "Huong");
    bst.insert(7, "Binh");
    bst.insert(4, "Hai");
    bst.insert(2, "Son"); 
    Node *n1 = bst.search(4);
    Node *n2 = bst.search(9); 
    if (n1 != NULL)
        cout << "Sinh vien voi SBD=4 la " << n1->hoTen << endl;
    if (n2 == NULL)
        cout << "Khong tim thay sinh vien voi SBD=9" << endl; // Lam rong cay.
    ostream& out = cout;
    bst.printTree(out);
    bst.deleteNode(3);
    cout << "Danh sach sinh vien sau khi xoa 3:" << endl;
    bst.printTree(out);
    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "Cay da bi xoa rong" << endl;
    return 0;
}