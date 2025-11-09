#include <iostream>
#include <stdexcept>

using namespace std;

template <class T> struct Node {
    Node<T>* next;
    T value;

    Node() : next(nullptr), value(0) {}

    Node(T value) : next(nullptr), value(value) {}
};

template <class T> class stack {
private:
    Node<T>* head;
    int size;

public:
    stack() {
        head = nullptr;
        size = 0;
    }

    void push(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        size++;
    }

    T pop() {
        if (is_empty()) throw std::underflow_error("Stack is empty!");
        T data = head->value;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return data;
    }

    T top() {
        if (is_empty()) throw std::runtime_error("Stack is empty!");
        return head->value;
    }

    T bottom() {
        if (is_empty()) throw std::runtime_error("Stack is empty!");
        Node<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->value;
    }

    void reverse() {
        if (is_empty()) throw std::runtime_error("Stack is empty!");
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    T getMiddle() {
        if (is_empty()) throw std::runtime_error("Stack is empty!");
        Node<T>* slow = head;
        Node<T>* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->value;
    }

    bool contains(T data) {
        Node<T>* temp = head;
        while (temp) {
            if (temp->value == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool is_empty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void clear() {
        while (!is_empty()) {
            pop();
        }
    }

    void print() {
        if (is_empty()) throw std::runtime_error("Stack is empty!");
        Node<T>* temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    stack<int> st;
    for (int i = 0; i < 10; i++) {
        st.push(i + 1);
    }

    st.pop();
    st.print();

    return 0;
}
