// Chương trình quản lý SV dùng DS liên kết
#include <iostream>
#include <cstring>
using namespace std;

struct Ngay 
{ 
    int ngay, thang, nam; 
}; 
struct SinhVien 
{ 
    char maSV[9]; 
    char hoTen[50]; 
    int gioiTinh; 
    Ngay ngaySinh; 
    char diaChi[100]; 
    char lop[15]; 
    char khoa[10]; 
};
struct Node 
{ 
    SinhVien data; 
    Node *link; 
}; 
struct List 
{ 
    Node *first, *last; 
};

Node* create_Node(SinhVien SV)
{
    Node* p = new Node;
    if (p == NULL) return NULL;
    p->data = SV;
    p->link = NULL;
    return p;
}

void init_List(List* list)
{
    list->first = list->last = NULL;
}

void insert_first(List* list, Node* p)
{
    p->link = list->first;
    list->first = p;
}

void insert_last(List* list, Node* p)
{
    list->last->link = p;
    list->last = p;
}

void insert_after(Node* p, Node* y)
{
    p->link = y->link;
    y->link = p;
}

void attach_Node(List* list, SinhVien SV, int x, Node* y)
{
    Node* p = create_Node(SV);
    if (p == NULL) return;
    if (list->first == NULL) list->first = list->last = p;
    else 
    {
        switch (x) 
        {
            case 0: insert_first(list, p); break;
            case 1: insert_last(list, p); break;
            case 2: insert_after(p, y); break;
        }
    }
}


SinhVien input_data()
{
    SinhVien SV;
    cout << "MSSV: ";
    cin >> SV.maSV;
    cout << "Ho & ten: ";
    cin.ignore(); 
    cin.getline(SV.hoTen, 50);
    cout << "Gioi tinh (nam 0, nu 1): ";
    cin >> SV.gioiTinh;
    cout << "Ngay thang nam sinh: ";
    cin >> SV.ngaySinh.ngay >> SV.ngaySinh.thang >> SV.ngaySinh.nam;
    cout << "Dia chi: ";
    cin.ignore(); 
    cin.getline(SV.diaChi, 100); 
    cout << "Lop: ";
    cin.getline(SV.lop, 15);
    cout << "Khoa: ";
    cin.getline(SV.khoa, 10);
    return SV;
}

void input_List(List* list)
{
    int add = 1;
    cout << "------------NHAP DSSV------------\n";
    while (add == 1)
    {
        attach_Node(list, input_data(), 1, NULL);
        cout << "Ban muon nhap them SV moi khong? Nhap 1 neu co: ";
        cin >> add;
    }
    cout << "----------KET THUC NHAP----------\n";
}

void print_data(SinhVien SV)
{
    cout.width(12); cout << left << SV.maSV;
    cout.width(25); cout << SV.hoTen;
    if (SV.gioiTinh == 0) cout << "Nam   ";
    else cout << "Nu    ";
    cout.width(2); cout << right << SV.ngaySinh.ngay << '/'; 
    cout.width(2); cout << SV.ngaySinh.thang << '/';
    cout.width(4); cout << SV.ngaySinh.nam << "    ";
    cout.width(25); cout << left << SV.diaChi;
    cout.width(15); cout << SV.lop;
    cout << SV.khoa << endl;
}

void print_List(List list)
{   
    cout << "-------------IN DSSV-------------\n";
    Node* p = list.first;
    while(p != NULL)
    {
        print_data(p->data);
        p = p->link;
    }
    cout << "-----------KET THUC IN-----------\n";
}

Node* find_Node_before(List list, SinhVien SV) 
{
    Node* p = list.first;
    while (p != list.last && strcmp(SV.maSV, p->link->data.maSV) > 0)
    {
        p = p->link;
    } 
    return p;
}

void add_to_sorted_List(List* list)
{
    cout << "Nhap thong tin SV moi:\n";
    SinhVien SV = input_data();
    int x = strcmp(SV.maSV, list->first->data.maSV);
    if (x == 0) 
    {
        cout << "MSSV bi trung, khong the them vao DS.\n";
        return;
    }
    if (x < 0) 
    {
        attach_Node(list, SV, 0, NULL); 
        cout << "Da them SV moi vao DS.\n";
        return;
    }
    Node* p = find_Node_before(*list, SV);
    if (strcmp(SV.maSV, p->link->data.maSV) != 0) 
    {
        attach_Node(list, SV, 2, p);
        cout << "Da them SV moi vao DS.\n";
        return;
    }
    cout << "MSSV bi trung, khong the them vao DS.\n";
}

bool check_birth(Node* a, Node* b)
{
    if (a->data.ngaySinh.ngay == b->data.ngaySinh.ngay) return true;
    else return false;
}

Node* find_Node_before_2(List list, Node* x)  
{
    Node* p = list.first;
    while (p != list.last && p->link->data.ngaySinh.ngay != x->data.ngaySinh.ngay)
    {
        p = p->link;
    } 
    if (p != list.last) return p;
    else return NULL;
}

int main()
{
    List list;
    init_List(&list);
    input_List(&list);
    print_List(list);
    add_to_sorted_List(&list);
    print_List(list);
}