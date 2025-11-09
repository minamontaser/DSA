#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class Queue{
    private:
    T* queue;
    bool valid = false;
    int front, rear, capacity, size;

    void resize(){
        capacity*=2;
        T* temp = new T[capacity];
        for(int i=0;i<current;i++){
            temp[i] = queue[size - i - 1];
        }
        delete[] queue;
        queue = temp;
    }

    public:

    Queue(){
        capacity = 1, size  = 0, front = 0, rear = -1;
        queue = new T[capacity];
        valid = true;
    }

    Queue(int capacity){
        this->capacity = capacity;
        int size = 0, front = 0, rear = -1;
        queue = new T[capacity];
    }

    void enqueue(T data){
        if(isFull() && !valid){
            throw std::runtime_error("Queue is full!");
        }
        if(valid){
            resize();
        }

        rear = (rear + 1) % capacity;
        queue[rear] = data;
        size++;
    }

    T dequeue(){
        if(isFull() && !valid){
            throw std::runtime_error("Queue is empty!");
        }
        if(valid){
            T data = queue[front];
            front = (front + 1) % capacity;
            size--;
        }
        return data;
    }

    void reverse(){
        if(isEmpty()) return;
        int start = front, end = rear;
        while(true){
            swap(queue[start], queue[end]);
            start = (start + 1) % capacity;
            end = (end - 1 + capacity) % capacity;
            if (start == end || (end + 1) % capacity == start) {
                break;
            }
        }
    }

    bool contains(T data){
        if(isEmpty()) return false;
        int start = front, end = rear;
        while(start != end){
            if(queue[start] == data) return true;
            start = (start + 1) % capacity;
        }
        return false;
    }

    T* toArray(){
        if(isEmpty()){
            throw std::runtime_error("Queue is empty!");
        }
        T* arr = new T[size];
        int index = front;
        for(int i=0;i<size;i++){
            arr[i] = queue[index];
            index = (index + 1) % capacity;
        }

        return arr;
    }

    T getMidde(){
        if(isEmpty()){
            throw std::runtime_error("Queue is empty!");
        }
        int middle = (front + size/2) % capacity; //*middle = (front + size/2)% capacity
        return queue[middle];
    }

    T getFront() const{
        if(isEmpty() && !valid){
            throw std::runtime_error("Queue is empty!");
        }
        if(valid){
            return queue[front];
        }
    }

    T getRear() const{
        if(isEmpty() && !valid){
            throw std::runtime_error("Queue is empty!");
        }
        if(valid){
            return queue[rear];
        }
    }

    bool isEmpty() const{
        return size == 0;
    }

    void clear(){
        front = 0, rear = -1, size = 0;
        delete[] queue;
        queue = new T[capacity];
        valid = true;
    }

    bool isFull() const{
        return size == capacity;
    }

    int getSize() const{
        return size;
    }

    int getCapacity() const{
        return capacity;
    }

    ~Queue(){
        delete[] queue;
        valid = false;
    }
};