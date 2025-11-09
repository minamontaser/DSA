/*
#include <iostream>
#include <stdexcept>

using namespace std;

template<class T> struct Node{
    T value;
    Node<T>* next;

    Node(){
        this->value = 0;
        this->next = nullptr;
    }

    Node(T value){
        this->value = value;
        this->next = nullptr;
    }
};

//!Linked list
template<class T> class Linked_list{
    private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    public:
    Linked_list(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    Linked_list(int size){
        if(size <= 0) throw std::invalid_argument("Size must be a positive integer.");
        head = nullptr;
        tail = nullptr;
        this->size = size;
    }

    void append(T data){
        Node<T>* newNode = new Node<T>(data);
        if(head == nullptr && tail == nullptr){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    T pop(){
        if(is_empty()) throw std::logic_error("Empty linked list");
        Node<T>* temp = head;
        T poped_node = tail->value;
        if(head == tail && size == 1){
            head = tail = nullptr;
            delete temp;
        }else{
            while(temp->next != tail){
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        size--;
        return poped_node;
    }

    void insert_node(T data, int pos){
        if(pos < 0 || pos > size) throw std::out_of_range("Invalid position.");
        Node<T>* newNode = new Node<T>(data);
        if(pos == 0){
            newNode->next = head;
            head = newNode;
            if(size == 0) tail = newNode;
        }else if(pos == size){
            tail->next = newNode;
            tail = newNode;
            if(size == 0) head = newNode;
        }else{
            Node<T>* temp = head;
            for(int i=0;i<pos;i++){
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    T delete_node(int pos){
        if(pos < 0 || pos > size) throw std::out_of_range("Invalid position.");
        T deleted_node;
        Node<T>* temp = head;
        if(pos == 0){
            deleted_node = head->value;
            head = head->next;
            if(size == 1) tail = nullptr;
            delete temp;
        }else{
            Node<T>* prev = nullptr;
            for(int i=0;i<pos;i++){
                prev = temp;
                temp = temp->next;
            }
            deleted_node = temp->value;
            prev->next = temp->next;
            if(temp == tail) tail = prev;
            delete temp;
        }
        size--;
        return deleted_node;
    }

    void delete_duplicates(){
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

    void move_node(T data, int pos){
        if(pos < 0 || pos > size) throw std::out_of_range("Invalid position.");
        int current_pos = search_node(data);
        if(current_pos == -1) throw std::runtime_error("Element not found!");
        if(current_pos == pos) return;
        delete_node(current_pos);
        insert_node(data, pos);
    }

    void sort(){
        if(!head || !head->next) return;
        bool valid = true;
        while(valid){
            Node<T>* current = head;
            valid = false;
            while(current->next){
                if(current->value > current->next->value){
                    swap(current->value, current->next->value);
                    valid = true;
                }
                current = current->next;
            }
        }
    }

    int search_node(T data){
        Node<T>* temp = head;
        int index = 0;
        while(temp){
            if(temp->value == data){
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    void reverse(){
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        tail = head;
        while(current){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    bool is_empty(){ return size == 0; }

    int get_size(){ return size; }

    T operator[](int pos){
        if(pos < 0 || pos > size) throw std::out_of_range("Invalid position.");
        return get_node_Recursive(head, pos)->value;
    }

    Node<T>* get_node_Recursive(Node<T>* node, int pos){
        if(pos == 0) return node;
        return get_node_Recursive(node->next, --pos);
    }

    T get_first(){
        if(is_empty()) throw std::logic_error("List is empty.");
        return head->value;
    }

    T get_middle(){
        if(is_empty()) throw std::logic_error("List is empty.");
        Node<T>* slow = head;
        Node<T>* fast = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->value;
    }

    T get_last(){
        if(is_empty()) throw std::logic_error("List is empty.");
        return tail->value;
    }

    Node<T>* get_head(){ return head; }

    void display(){
        if(is_empty()){
            cout<<"List is empty."<<endl;
            return;
        }
        Node<T>* temp = head;
        while(temp != nullptr){
            cout<<temp->value<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }

    ~Linked_list(){
        Node<T>* current;
        while(current != nullptr){
            current = head;
            head = head->next;
            delete current;
        }
        head = tail = nullptr;
        size = 0;
    }
};

//!Stack
template<class T> class Stack{
    private:
    Node<T>* top;
    int size;

    public:
    Stack(){
        this->top = nullptr;
        this->size = 0;
    }

    void push(T data){
        Node<T>* newNode = new Node<T>(data);
        newNode->next = top;
        top = newNode;
        size++;
    }

    T pop(){
        if(is_empty()){
            throw std::logic_error("Stack is empty!");
        }
        T poped_value = top->value;
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
        return poped_value;
    }

    T peek(){
        if(is_empty()){
            throw std::logic_error("Stack is empty!");
        }
        return top->value;
    }

    T bottom(){
        if(is_empty()){
            throw std::logic_error("Stack is empty!");
        }
        Node<T>* temp = top;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        return temp->value;
    }

    bool contains(T data){
        if(is_empty()){
            return false;
        }
        Node<T>* temp = top;
        while(temp){
            if(temp->value == data){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void reverse(){
        if(is_empty()){
            return ;
        }
        Node<T>* prev = nullptr;
        Node<T>* current = top;
        Node<T>* next = nullptr;
        while(current){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        top = prev;
    }

    T get_middle(){
        if(is_empty()){
            throw std::logic_error("Stack is empty!");
        }
        Node<T>* slow = top;
        Node<T>* fast = top;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->value;
    }

    T* toArray() {
        if (is_empty()) {
            return nullptr;
        }
        T* result = new T[size];
        Node<T>* temp = top;
        for (int i = 0; i < size; i++, temp = temp->next) {
            result[i] = temp->value;
        }
        return result;
    }

    bool is_empty(){
        return size == 0;
    }

    int get_size(){
        return size;
    }

    void clear(){
        while(!is_empty()){
            pop();
        }
        top = nullptr;
        size = 0;
    }

    void print(){
        if(is_empty()){
            cout<<"Stack is empty."<<endl;
            return;
        }
        Node<T>* temp = top;
        while(temp){
            cout<<temp->value<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }

    ~Stack(){
        clear();
    }
};

//!Stack_array
template<class T> class Stack_array{
    private:
    T* stack;
    int capacity, current;
    void resize(){
        T* temp = new T[capacity*=2];
        for(int i=0;i<current;i++){
            temp[i] = stack[i];
        }
        delete[] stack;
        stack = temp;
    }

    public:
    Stack_array(){
        capacity = 1, current = 0, stack = new T[capacity];
    }

    void push(T data){
        if(current == capacity) resize();
        stack[current++] = data;
    }

    T pop(){
        if(is_empty()) throw std::logic_error("Stack is empty!");
        T poped_value = stack[--current];
        stack[current] = new T();
        return poped_value;
    }

    void reverse(){
        if(is_empty()) return ;
        int start = 0, end = current -1;
        while(start < end){
            swap(stack[start], stack[end]);
            stack++, end--;
        }
    }

    bool contains(T data){
        if(is_empty()) return false;
        for(int i=0;i<current; i++){
            if(stack[i] == data){
                return true;
            }
        }
        return false;
    }

    T* toArray(){
        if(is_empty()) return nullptr;
        T* arr = new T[current];
        for(int i=0;i<current; i++){
            arr[i] = stack[i];
        }
        return arr;
    }

    T top(){
        if(is_empty()) throw std::logic_error("Stack is empty!");
        return stack[current - 1];
    }

    T get_middle(){
        if(is_empty()) throw std::logic_error("Stack is empty!");
        int mid = (current - 1) / 2;
        return stack[mid];
    }

    T bottom(){
        if(is_empty()) throw std::logic_error("Stack is empty!");
        return stack[0];
    }

    bool is_empty(){ return current == 0; }

    bool is_full(){ return current == capacity; }

    int get_size(){ return current; }

    int get_capacity(){ return capacity; }

    void clear(){
        delete[] stack;
        capacity = 1, current = 0, stack = new T[capacity];
    }

    void print(){
        if(is_empty()){
            cout<<"Stack is empty."<<endl;
            return;
        }
        for(itn i=0;i<current;i++){
            cout<<stack[i]<<" ";
        }
        cout<<"\n";
    }

    ~Stack_array(){
        delete[] stack;
        stack = nullptr;
        capacity = 0, current = 0;
    }
};
*/

#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>struct Node{
    Node<T>* next;
    T value;
    Node(){
        this->next = nullptr;
        this->value = T();
    }

    Node(T value){
        thie->next = nullptr;
        this->value = value;
    }
};

template<class T> class Linked_list{
    private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    public:
    Linked_list(){
        head = tail = nullptr;
        size = 0;
    }

    void append(T data){
        Node<T>* newNode = new Node<T>(data);
        if(this->head == nullptr && this->tail == nullptr && size == 0){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    T pop(){
        if(is_empty()) throw std::logic_error("Empty linked list");
        Node<T>* temp = head;
        T poped_node = tail->value;
        if(head == tail && size == 1){
            head = tail = nullptr;
            delete temp;
        }else{
            while(temp->next != tail){
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        size--;
        return poped_node;
    }

    void insert_node(T data, int pos){
        if(pos < 0 || pos > size) throw std::out_of_range("Position out");
        Node<T>* newNode = new Node<T>(data);
        if(pos == 0){
            newNode->next = head;
            head = newNode;
        }else if(pos == size){
            tail->next = newNode;
            tail = newNode;
        }else{
            Node<T>* temp = head;
            for(int i=0;i<pos;i++){
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    int search_node(T data){
        Node<T>* temp = head;
        for(int i=0;i<size;i++){
            if(temp->value == data) return i;
            temp = temp->next;
        }
        return -1;
    }

    void delete_node(T data){
        if(is_empty()) throw std::underflow_error("Empty linked list");
        int pos = search_node(data);
        if(pos == -1) throw std::out_of_range("Node not found");
        Node<T>* temp = head;
        if(pos == 0){
            head = head->next;
            delete temp;
        }else{
            Node<T>* prev = nullptr;
            for(int i=0;i<pos;i++){
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
            if(temp == tail) tail = prev;
            delete temp;
        }
        size--;
    }
};

template<class T>
class Stack{
    private:
    Node<T>* head;
    int size;

    public:
    Stack(){
        head = nullptr;
        size = 0;
    }

    void push(T data){
        Node<T>* newNode = new Node<T>(data);
        if(head == nullptr && size == 0){
            head = newNode;
        }else{
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    T pop(){
        if(is_empty()) throw std::underflow_error("Stack is empty");
        T data = head->value;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return data;
    }

    T peek(){
        if(is_empty()) throw std::underflow_error("Stack is empty");
        return head->value;
    }

    bool is_empty(){return size == 0;}

    void display(){
        Node<T>* temp = head;
        while(temp != nullptr){
            cout<<temp->value<<endl;
            temp = temp->next;
        }
    }
};

template<class T> class Queue{
    private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    public:
    Queue(){
        head = tail = nullptr;
        size = 0;
    }

    void push(T data){
        Node<T>* newNode = new Node<T>(data);
        if(head == nullptr && tail == nullptr && size == 0){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    T pop(){
        if(is_empty()) throw std::underflow_error("Queue is empty");
        T data = head->value;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return data;
    }

    T top(){
        if(is_empty()) throw std::underflow_error("Queue is empty");
        return head->value;
    }

    bool is_empty(){return size = 0;}

    void display(){
        Node<T>* temp = head;
        while(temp != nullptr){
            cout<<temp->value<<endl;
            temp = temp->next;
        }
    }
};

template <class T> class Stack_array{
    private:
    T* stack;
    int capacity, size;
    T top;

    public:
    Stack_array(int capacity){
        this->capacity = capacity;
        stack = new T[capacity];
        size = 0;
    }

    void push(T data){
        if(size == capacity) throw std::overflow_error("Stack is full");
        stack[size++] = data;
    }

    T pop(){
        if(is_empty()) throw std::underflow_error("Stack is empty");
        T data = stack[--size];
        stack[size] = T();
        return data;
    }

    T top(){
        if(is_empty()) throw std::underflow_error("Stack is empty");
        return stack[size - 1];
    }

    T bottom(){
        if(is_empty()) throw std::underflow_error("Stack is empty");
        return stack[0];
    }

    bool contains(T data){
        if(is_empty()) throw std::underflow_error("Stack is empty");
        for(int i=;i<size;i++){
            if(stack[i] == data) return true;
        }
        return false;
    }

    void reverse(){
        int start = 0, end = size - 1;
        while(start < end){
            swap(stack[start], stack[end]);
            start++, end--;
        }
    }

    bool is_empty(){return size == 0;}

    bool is_full(){return size == capacity;}

    void display(){
        if(size == 0) throw std::runtime_error("stack is empty!");
        for(int i = 0;i<size;i++){
            cout<<stack[i]<<" ";
        }
        cout<<"\n";
    }
};