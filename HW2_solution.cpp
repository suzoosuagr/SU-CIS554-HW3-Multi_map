//CIS-554-homework#2 solution
//HW2: Sparse Vector Operations Using Linked List structures
//Due: 11:59PM, Friday, September 22

//Implement the following member functions for class my_vector:
//add_node
//operator+
//operator*





#include <iostream>
#include <fstream>
using namespace std;

ofstream out("data1.txt");

class node {
public:
    int value;
    int position;
    node * next;
    node() { value = -9999; position = -1; next = nullptr; }
    node(int i, int j) { value = i; position = j; next = nullptr; }
};

class my_vector {
public:
    int size;
    int num_nodes; //number of non-zero elements
    node * head;
    my_vector() { size = num_nodes = 0; head = nullptr; }
    
    void add_node(int v, int p); //add a new node with value v and position p;
    //if a node at position p already exists, update its value to v
    
    void make_random_vector(int s, int n, int k);
    //set the value of size  to s;
    //randomly create n nodes in -(k-1) to k-1
    
    my_vector operator+(my_vector V); //vector addition
    
    int operator*(my_vector V);//inner product
    
    void print();
};

void my_vector::make_random_vector(int s, int n, int k) {
    size = s;
    for (int i = 0; i < n; i++) {
        int p = rand() % s;
        int v = rand() % (2 * k - 1) - (k - 1);
        add_node(v, p);
    }
}

void my_vector::print() {
    out << endl;
    node * p = head;
    while (p != nullptr) {
        out << "[" << p->value << " " <<"," << " " << p->position << "]" << "  ";
        p = p->next;
    }
}

my_vector my_vector::operator+(my_vector V) {//need modify
    my_vector temp;
    node * thisp = this->head;
    node * vp = V.head;
    
    for (int i = this->num_nodes; i > 0; i--) {
        temp.add_node(thisp->value, thisp->position);
        thisp = thisp->next;
    }
    
    for (int i = V.num_nodes; i > 0; i--) {
        temp.add_node(vp->value, vp->position);
        vp = vp->next;
    }
    
    node * outp = nullptr;
    node * innerp = nullptr;
    node * innerppre = temp.head;
    
    for (outp = temp.head; outp->next != nullptr;outp = outp->next){
        for(innerp = outp->next; innerp->next != nullptr;innerp = innerp->next){
            if(outp->position == innerp->position){
                    outp->value += innerp->value;
                    innerppre->next = innerp->next;
                    temp.num_nodes--;
                }
            else{
                    innerppre = innerp;
                }
            }
        if(innerp->next == nullptr){
            if (outp->position == innerp->position) {
                outp->value += innerp->value;
                innerppre->next = nullptr;
                innerp = outp->next;
                innerppre = outp;
                temp.num_nodes--;
            }
            else{
                innerppre = outp->next;
            }
        }
    }
    
    return temp;
}

int my_vector::operator*(my_vector V){
    int result = 0;
    node * p1 = this->head;
    node * p2 = V.head;
    
    for(int i = this->num_nodes; i > 0; p1 = p1->next){
        for (p2 = V.head; p2->next != nullptr; p2 = p2->next) {
            if (p1->position == p2->position) {
                result += p1->value * p2->value;
            }
        }
        if (p2->next == nullptr) {
            if (p1->position == p2->position) {
                result += p1->value * p2->value;
            }
        }
        i--;
    }
    
    
    
    return result;
}

void my_vector::add_node(int v, int p){
    node * pnode;
    pnode = new node(v,p);
    pnode->next = head;
    head = pnode;
    num_nodes++;
}

int main() {
    
    my_vector V1, V2, V3;
    V1.make_random_vector(30, 10, 10);
    V1.print();
    V2.make_random_vector(30, 13, 10);
    V2.print();
    V3 = V1 + V2;
    V3.print();
    out<<endl;
    int inner_product = V1 * V2;
    out << inner_product << endl;
    
    //out.close();
    return 0;
    
}



