#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>struct Node{
    T value;
    Node<T>* next;
    Node(T value){
        this->value = value;
        this->next = nullptr;
    }
};

template <class T> class Queue{
    private:
    Node<T>* head, *tail;
    int size;

    public: 
    Queue(){
        head = tail = nullptr;
        size = 0;
    }

    void enqueue(T data){
        Node<T>* newNode = new Node<T>(data);
        if(tail == nullptr) head = tail = newNode;
        else{
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    T dequeue(){
        if(isEmpty()){
            throw std::runtime_error("Queue is empty!");
        }
        T data = head->value;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if(head == nullptr){
            tail = nullptr;
        }
        size--;
        return data;
    }

    bool contains(T data){
        Node<T>* temp = head;
        while(temp!=nullptr){
            if(temp->value == data){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void reverse(){
        Node<T>* prev = nullptr, *current = head, *next = nullptr;
        tail = head;
        while(current != nullptr){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    T top(){
        if(isEmpty()){
            throw std::runtime_error("Queue is empty!");
        }
        return head->value;
    }

    T bottom(){
        if(isEmpty()){
            throw std::runtime_error("Queue is mepty!");
        }
        return tail->value;
    }

    int getSize(){
        return size;
    }

    T* toArray(){
        if(isEmpty()){
            throw std::runtime_error("Queue is empty!");
        }
        T* arr = new T[size];
        Node<T>* temp = head;
        for(int i=0;i<size;i++){
            arr[i] = temp->value;
            temp = temp->next;
        }
        return arr;
    }

    T getMiddle(){
        if(isEmpty()){
            throw std::runtime_error("Queue is empty!");
        }
        Node<T>* slow = head, *fast = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->value;
    }

    void clear() {
        Node<T>* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        
        tail = nullptr;
        size = 0;
    }    

    bool isEmpty(){
        return head == nullptr;
    }

    void print(){
        Node<T>* temp = head;
        while( temp != nullptr){
            cout<<temp->value<<" -> ";
            temp = temp->next;
        }
        cout<<"Null terminated"<<endl;
    }

    ~Queue(){
        clear();
    }
};