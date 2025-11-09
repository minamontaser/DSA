/*
 * Copyright (c) 2025 Mina(RR)
 * All rights reserved.
 *
 * This software is provided "as is," without warranty of any kind, express or implied.
 * You are free to use, modify, and distribute this code, provided proper credit is given.
 *
 * Created by Mina(RR)
 */

#include <iostream>
#include <stdexcept>

using namespace std;

#define ll long long

//!Data -> Static -> BSS
int gl_Var;
string message;
static int n;

template <class T>
struct Node {
    T value;
    Node<T>* next;

    Node(){
        value = 0;
        next = nullptr;
    }

    Node(T value) {
        this->value = value;
        this->next = nullptr;
    }
};

template <class T>
class Linked_list { // in
private:
    Node<T>* head, * tail;
    ll size;

public:
    Linked_list();//!
    void append(T data);//!
    void insert_node(T data, int pos);//!
    void delete_node(int pos);//!
    void move_node(T data, int pos);//!
    int search_node(T data);//!
    void reverse();//!
    T get_middle();//!
    int size_of();//!
    bool is_empty();//!
    T operator[](int pos);//!
    Node<T>* get_node_Recursive(Node<T>* current, int pos);//!
    T get_first();//!
    T get_last();//!
    T pop();//!
    void sort();//!
    void delete_duplicates();//!
    Node<T>* get_head();//!
    void display();//!
    ~Linked_list();//!
};

template <class T>
Linked_list<T>::Linked_list(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
void Linked_list<T>::append(T data){
    Node<T>* new_node = new Node<T>(data);
    if (head == nullptr && tail == nullptr) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    size++;
}

template <class T>
void Linked_list<T>::insert_node(T data, int pos){
    if(pos < 0 || pos > size) throw out_of_range("Invalid position.");

    Node<T>* new_node = new Node<T>(data);

    if(pos == size){
        if(tail) tail->next = new_node;
        tail = new_node;
        if(size == 0) head = new_node;
    }else if(pos == 0){
        new_node->next = head;
        head = new_node;
        if(size == 0) tail = new_node;
    }else{
        Node<T>* temp = head;
        pos-=1;
        while(pos){
            temp = temp->next;
            pos--;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    size++;
}

template<class T>
void Linked_list<T>::delete_node(int pos){ // in
    if (pos < 0 || pos >= size) throw std::out_of_range("out of range error!");

    Node<T>* temp = head;

    if(pos == 0){ 
        head = head->next;
        if(size == 1) tail = nullptr;
        if(head == nullptr) tail = nullptr;
        delete temp;
    }
    else {
        Node<T>* prev = nullptr;
        for (int i = 0; i < pos; i++) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;

        if (temp == tail) {
            tail = prev;
        }
        delete temp;
    }
    size--;
}

template<class T>
void Linked_list<T>::move_node(T data, int pos){
    if (pos < 0 || pos >= size) throw std::out_of_range("Invalid position: ", pos);

    int current_pos = search_node(data);
    if(current_pos == -1){
        cout << "Node with value " << data << "not found." << endl;
        return;
    }

    if(current_pos == pos) return;
    delete_node(current_pos);
    insert_node(data, pos);
}

template<class T>
int Linked_list<T>::search_node(T data){
    Node<T>* temp = head;
    int pos = 0;
    while(temp != nullptr){
        if(temp->value == data) return pos;
        temp = temp->next;
        pos++;
    }
    return -1; // target not found
}

template<class T>
void Linked_list<T>::reverse(){
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;
    tail = head;

    while(current != nullptr){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

template<class T>
T Linked_list<T>::get_middle(){
    if(!head) throw std::runtime_error("List is empty!");
    Node<T>* slow = head;
    Node<T>* fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow->value;
}

template<class T>
int Linked_list<T>::size_of() {
    return size;
}

template<class T>
bool Linked_list<T>::is_empty(){
    return size == 0;
}

template<class T>
void Linked_list<T>::display() {
    if(!head){
        cout<<"List is empty!"<<endl;
        return;
    }
    Node<T>* temp = head;
    while (temp != nullptr) {
        cout << temp->value << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

template<class T>
T Linked_list<T>::operator[](int pos){
    if(pos < 0 || pos >= size) return T();
    return get_node_Recursive(head, pos)->value;
}

template<class T>
Node<T>* Linked_list<T>::get_node_Recursive(Node<T>* current, int pos){
    if(pos == 0) return current;
    return get_node_Recursive(current->next, pos-1);
}

template<class T>
T Linked_list<T>::get_first(){
    if(!head) throw std::runtime_error("List is empty!");
    return head->value;
}

template<class T>
T Linked_list<T>::get_last() {
    if (is_empty()) throw std::runtime_error("List is empty!");  
    return tail->value;
}

template<class T>
T Linked_list<T>::pop(){ // in
    if(is_empty()) throw std::runtime_error("List is empty!");
    Node<T>* temp = head;
    T pop_value;
    if(head == tail){
        pop_value = head->value;
        delete head;
        head = tail = nullptr;
    }else{
        while(temp->next != tail){
            temp = temp->next;
        }
        pop_value = tail->value;
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
    size--;
    return pop_value;
}

template<class T>
void Linked_list<T>::sort(){
    if (!head || !head->next) return;
    bool Swap = true;
    while(Swap){
        Swap = false;
        Node<T>* current = head;
        while(current->next){
            if(current->value > current->next->value){
                swap(current->value, current->next->value);
                Swap = true;
            }
            current = current->next;
        }
    }

}

template<class T>
void Linked_list<T>::delete_duplicates(){
    if (!head || !head->next) return;
    sort();
    Node<T>* current = head;
    while(current->next){
        if(current->value == current->next->value){
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
        }else{
            current = current->next;
        }
    }
    tail = current;
}

template<class T>
Node<T>* Linked_list<T>::get_head(){
    return head;
}

//! Deallocation of memory
template<class T>
Linked_list<T>::~Linked_list() {
    Node<T>* temp = head;
    while (temp) {
        Node<T>* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = tail = nullptr;
    size = 0;
}

