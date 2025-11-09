/*
Functions:
Stack()
push()
pop()
top()
bottom()
toArray()
reverse()
getMiddle()
clear()
contains()
isEmpty()
getSize()
print()
~Stack()
*/

#include <iostream>

using namespace std;

template <class T>struct Node{
    T value;
    Node<T>* next;

    Node(){
        value = 0;
        next = nullptr;
    }

    Node(T value){
        this->value = value;
        next = nullptr;
    }
};

template <class T>class Stack{
    private:
    Node<T>* head;
    T* arr;
    int size;

    public:
    Stack(){
        head = nullptr;
        size = 0;
        arr = nullptr;
    }

    void push(T data){
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        size++;
    }

    T top() const{
        if(head == nullptr){
            throw std::runtime_error("Stack is empty!");
        }

        return head->value;
    }

    T pop(){
        if(head == nullptr){
            throw std::runtime_error("Stack is empty!");
        }

        T pop_value = head->value;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return pop_value;
    }

    T bottom() const{
        if(head == nullptr){
            throw std:: runtime_error("Stack is empty!");
        }

        Node<T>* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }

        return temp->value;
    }

    T* toArray() const {
        T* array = new T[size];
        Node<T>* temp = head;
        for (int i = 0; i < size; i++, temp = temp->next) {
            array[i] = temp->value;
        }
        return array;
    }
    
    void reverse(){
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;

        while(curr != nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }

    T getMiddle(){
        if(head == nullptr){
            throw std::runtime_error("Stack is empty!");
        }

        Node<T>* slow = head;
        Node<T>* fast = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->value;
    }

    void clear(){
        while(head != nullptr){
            pop();
        }
    }

    bool contains(T data){
        Node<T>* temp = head;
        while(temp != nullptr){
            if(temp->value == data){
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    bool isEmpty() const{
        return size == 0;
    }

    int getSize() const{
        return size;
    }

    void print() const{
        Node<T>* temp = head;
        cout<<"Stack: ";
        while(temp != nullptr){
            cout<<temp->value<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }

    ~Stack(){
        while(head != nullptr){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        delete[] arr;
        head = nullptr;
        arr = nullptr;
        size = 0;
    }
};