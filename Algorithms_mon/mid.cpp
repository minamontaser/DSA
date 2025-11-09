#include <iostream>
#include <string>

using namespace std;

template<class T> struct Node{
    Node<T>* next;
    T value;
    Node(T value){
        this->next = nullptr;
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

    bool is_empty(){
        return size == 0;
    }

    void display_for_loop(){
        if(is_empty()){
            throw std::runtime_error("Linked_list is empty!");
        }
        for(Node<T>* temp = head; temp != nullptr; temp = temp->next){
            cout<<temp->value<<endl;
        }
    }

    void display_while_loop(){
        if(is_empty()){
            throw std::runtime_error("Linked_list is empty!");
        }
        Node<T>* temp = head;
        while(temp != nullptr){
            cout<<temp->value<<endl;
            temp = temp->next;
        }
    }
};

int main(){

    Linked_list<int> linked_list;
    cout<<"inserting elements in the list!!!!"<<endl;
    for(int i =0;i<10;i++){
        linked_list.push(i + 1);
    }

    cout<<"display the list by using for loop: "<<endl;
    linked_list.display_for_loop();

    cout<<"display the list by using while loop: "<<endl;
    linked_list.display_while_loop();

    return 0;
}