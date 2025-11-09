#include <iostream>
#include <cassert>

using namespace std;

template <class T>class Stack{
    private:
    T* stack;
    int current, capacity;

    void resize(){
        capacity*=2;
        T* temp = new T[capacity];
        for(int i=0;i<current;i++){
            temp[i] = stack[i];
        }
        delete[] stack;
        stack = temp;
    }

    public:
    Stack(){
        stack = new T[1];
        capacity = 1, current = 0;
    }

    void push(T data){
        if(current == capacity){
            resize();
        }
        stack[current++] = data;
    }

    T top(){
        if(current < 1){
            throw std::runtime_error("Stack is empty!");
        }
        return stack[current - 1];
    }

    T bottom(){
        if(current < 1){
            throw std::runtime_error("Stack is empty!");
        }
        return stack[0];
    }

    T pop(){
        if(current < 1){
            throw std::runtime_error("Stack is empty!");
        }
        T pop_value = stack[--current];
        stack[current] = T();
        return pop_value;
    }

    T* toArray(){
        T*copy_array = new T[current];
        for(int i=0;i<current ;i++){
            copy_array[i] = stack[i];
        }
        return copy_array;
    }

    void reverse(){
        int start = 0, end = current -1;
        while(start < end){
            swap(stack[start], stack[end]);
            start++, end--;
        }
    }

    T getMiddle() {
        if (current == 0) {
            throw runtime_error("Stack is empty!");
        }
        int midIndex = (current - 1) / 2;
        return stack[midIndex];
    }

    bool contains(T data) const{
        for(int i=0;i<current;i++){
            if(stack[i] == data){
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const{
        return current == 0;
    }

    bool is_full() const{
        return current == capacity;
    }

    int getSize() const{
        return current;
    }

    int getCapacity() const{
        return capacity;
    }

    void clear(){
        delete[] stack;
        stack = new T[1];
        capacity = 1, current = 0;
    }

    void print() const{
        for(int i=0;i<current;i++){
            cout<<stack[i]<<" ";
        }
        cout<<"\n";
    }

    ~Stack(){
        delete[] stack;
        stack = nullptr;
        capacity = 0, current = 0;
    }
};