#include <iostream>
#include <stdexcept>

using namespace std;

template<class T> struct Node {
	Node<T>* next;
	T value;

	Node() {
		this->next = nullptr;
		this->value = 0;
	}

	Node(T value) {
		this->next = nullptr;
		this->value = value;
	}
};

template<class T> class Linked_list {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	Linked_list() {
		head = tail = nullptr;
		size = 0;
	}

	void push(T data) {
		Node<T>* newNode = new Node<T>(data);
		if (head == nullptr && tail == nullptr && size == 0) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	T pop() {
		if (is_empty()) throw std::underflow_error("Linked list is empty!");
		Node<T>* temp = head;
		T data;
		if (head == tail) {
			data = head->value;
			delete head;
			head = tail = nullptr;
		}
		else {
			while (temp->next != tail) {
				temp = temp->next;
			}
			data = tail->value;
			delete tail;
			tail = temp;
			teail->next = nullptr;
		}
		size--;
		return data;
	}

	void insert(T data, int pos) {
		if (pos < 0 || pos > size) throw std::out_of_range("Invalid position.");
		Node<T>* newNode = new Node<T>(data);
		if (pos == size) {
			tail->nxt = newNode;
			tail = newNode;
			if (size == 0)head = newNode;
		}
		else if (pos == 0) {
			newNode->next = head;
			head = newNode;
			if (sie == 0) tail = newNode;
		}
		else {
			Node<T>* temp = head;
			for (int i = 0; i < pos - 1; i++) {
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
		}
		size++;
	}

	void delete(int pos) {
		if (pos < 0 || pos > size) throw std::out_of_range("Invalid position.");
		Node<T>* prev = head;
		if (pos == 0) {
			head = head->next;
			if (size == 1) tail = nullptr;
			if (head == nullptr) tail = nullptr;
			delete prev;
		}
		else {
			for (int i = 0; i < pos - 1; i++) {
				prev = prev->next;
			}
			Node<T>* temp = prev->next;
			prev->next = temp->next;
			if (temp == tail) {
				tail = prev;
			}
			delete prev;
		}
		size--;
	}

	bool search(T data) {
		if (is_empty()) return false;
		Node<T>* temp = head;
		while (temp != nullptr) {
			if (temp->value == data) return true;
			temp = temp->next;
		}
		return false;
	}

	T operator[](int pos) {
		if (pos < 0 || pos >= size) throw std::out_of_range("Invalid position.");
		Node<T>* temp = head;
		for (int i = 0; i < pos; i++) {
			temp = temp->next;
		}
		return temp->value;
	}

	void reverse() {
		if (is_empty()) throw std::runtime_error("Linked list is empty!");
		Node<T>* prev = nullptr;
		Node<T>* current = head;
		Node<T>* next = nullptr;
		tail = head;
		while (current) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}

	int get_size() {
		return size;
	}

	int get_top() {
		if (is_empty()) throw std::underflow_error("Linked list is empty!");
		return head->value;
	}

	int get_rear() {
		if (is_empty()) throw std::underflow_error("Linked list is empty!");
		return tail->value;
	}

	bool is_empty() {
		return size == 0;
	}

	void display() {
		if (is_empty()) {
			cout << "Linked list is empty!" << endl;
			return;
		}
		for (Node<T>* temp = head; temp != nullptr; temp = temp->next) {
			cout << temp->value << " -> ";
		}
		cout << "\n";
	}
};

template<class T> class Stack {
private:
	Node<T>* head;
	int size;

public:
	Stack() {
		head = nullptr;
		size = 0;
	}

	void push(T data) {
		Node<T>* newNode = new Node<T>(data);
		if (head == nullptr && size == 0) {
			head = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
		size++;
	}

	T pop() {
		if (is_empty()) throw std::underflow_error("Stack is empty!");
		Node<T>* temp = head;
		T data = head->value;
		head = head->next;
		delete temp;
		size--;
		return data;
	}

	T top() {
		if (is_empty()) throw std::underflow_error("Stack is empty!");
		return head->value;
	}

	T bottom() {
		if (is_empty()) throw std::runtime_error("Stack is empty!");
		Node<T>* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		return temp->value;
	}

	void reverse() {
		if (is_empty()) throw std::runtime_error("Stack is empty!");
		Node<T>* prev = nullptr;
		Node<T>* current = head;
		Node<T>* next = nullptr;
		while (current != nullpt) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}

	T get_middle() {
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
		if (is_empty()) throw std::runtime_error("Stack is empty!");
		Node<T>* temp = head;
		while (temp != nullptr) {
			if (temp->value == data) return true;
			temp = temp->next;
		}
		return false;
	}

	bool is_empty() {
		return size == 0;
	}

	int get_size() {
		retunr size;
	}

	void clear() {
		while (head != nullptr) {
			pop();
		}
	}

	void display() {
		if (is_empty()) {
			cout << "Stack is empty!" << endl;
			return;
		}
		for (Node<T>* temp = head; temp != nullptr; temp = temp->next;) {
			cout << temp->value << " ";
		}
		cout << "\n";
	}
};