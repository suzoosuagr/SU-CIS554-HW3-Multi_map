//HW1_solution
//Implement the three member functions of linked_list class: sort, remove_all, and insert
//as described in the code blow
//Due: 11:59pm, Friday, September 8
//Submit a text vesion of your program to blackboard

//Linked List Examples by C-Y (Roger) Chen, Syracuse University

#include <iostream>
using namespace std;

class node {
public:
    int value;
    node * next;
    node() { next = nullptr; }
    node(int k) { value = k; next = nullptr; }
};

class linked_list {
public:
    int num_nodes;
    node * head;
    linked_list() { num_nodes = 0; head = nullptr; }
    void make_random_list(int k);//create a linked list of
    //k nodes with values in 0 ..99 randomly
    void print(); //Print values of all nodes from head node
    
    void reverse(); //Reverse the order of nodes of linked list
    //*********************
    //Implement the following three member functions.
    
    void sort(); //Sort the nodes, based on ascending order of node values
    
    void insert(int k); //Create a new node with values k, and properly add it to an already sorted list
    //After the insertion, the entire linked list is still sorted.
    
    void remove_all(int k); //Remove all nodes whose node values are equal to k
    
};
void linked_list::make_random_list(int k) {
    node * p;
    for (int i = 0; i < k; i++) {
        p = new node(rand() % 100);
        p->next = head;
        head = p;
        num_nodes++;
    }
}

void linked_list::print() {
    node * p = head;
    cout << endl;
    while (p != nullptr) {
        cout << p->value << " ";
        p = p->next;
    }
}

void linked_list::reverse() {
    if (num_nodes <= 1) return;
    node * p1 = head, *p2 = head->next, *p3;
    while (p2 != nullptr) {
        p3 = p2->next;
        p2->next = p1;
        if (p1 == head) p1->next = nullptr;
        p1 = p2;
        p2 = p3;
    }
    head = p1;
}

void linked_list::sort(){
    if(num_nodes <= 1) return;
    
    node *f, *p, *x, *y;
    f = nullptr;
    
    while(f != head->next->next)
    {
        //外层是N - 1次循环,升序
        for(p = head; p -> next -> next != f; p = p -> next)
        {
            
            if(p -> next -> value > p -> next -> next -> value)
            {
                x = p -> next;
                y = p -> next -> next;
                p -> next = y;
                x -> next = y -> next;
                y -> next = x;
            }
        }
        f = p -> next;
    }
    if( head->value > head->next->value){
        int temp;
        temp = head->value;
        head->value = head->next->value;
        head->next->value = temp;
        while(f != head->next->next)
        {
            //外层是N - 1次循环,升序
            for(p = head; p -> next -> next != f; p = p -> next)
            {
                if(p -> next -> value > p -> next -> next -> value)
                {
                    x = p -> next;
                    y = p -> next -> next;
                    p -> next = y;
                    x -> next = y -> next;
                    y -> next = x;
                }
            }
            f = p -> next;
        }
    }
}

void linked_list::insert(int k){
    node *p, *q,*pre = nullptr;
    int f = 0;
    p = head;
    q = new node(k);
        for (p = head; p->next != nullptr && f == 0;p = p->next) { //head and middle
            if (p->value >= k) {
                if(p == head){
                    q->next = p;
                    head = q;
                    f = 1;//finishi insert
                }
                else{
                    q->next = p->next;
                    p->next = q;
                    f = 1;//finish insert
                }
               
            }
            pre = p;//pre pointer
        }
        if (p->next == nullptr) {//last interval
            if (p->value >= k) {
                q->next = p;
                pre->next =q;
            }
            else{//tail
                p->next = q;
                q->next = nullptr;
            }
    }
    
}

void linked_list::remove_all(int k){
    node *p = head,*pre = nullptr;//*f=nullptr;
    p = head;
    for (p = head; p->next != nullptr; p = p->next) {
        if (p == head){
            if (p->value == k) {
                pre = nullptr;
                head = p->next;
            }
        }
        else if(p->value == k){
            pre->next = p->next;
            p = nullptr;
            p = pre;
        }
        pre = p;
    }
    if(p->next == nullptr){
        if(p->value == k){
            pre->next = nullptr;
            p = nullptr;
        }
    }
    
    
}

int main(){
    linked_list testlist;
    testlist.make_random_list(10);
    testlist.print();
    testlist.sort();
    testlist.print();
    testlist.insert(78);
    testlist.print();
    testlist.remove_all(78);
    testlist.print();
    std::cout<<endl;
    return 0;
}
