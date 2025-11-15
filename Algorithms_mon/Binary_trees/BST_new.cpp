#include <iostream>
#include <stdexcept>
#include <climits>

using namespace std;

#define ll long long

template<class T> struct Node {
	T value;
	Node<T>* left, * right;
	Node(T value) {
		this->value = value;
		this->left = this->right = nullptr;
	}
};

template<class T> class BST {
private:
	Node<T>* root;//!root == Tree itself
	int size;
	Node<T>* insertNode(Node<T>* node, T data) {
		if (node == nullptr) {
			return new Node<T>(data);
		}
		if (node->value == data) throw std::runtime_error("Dublicated item!");
		if (data > node->value) {
			node->right = insertNode(node->right, data);
		}
		else if (data < node->value) {
			node->left = insertNode(node->left, data);
		}
		return node;
	}
	Node<T>* searchNode(Node<T>* node, T data) {
		if (node == nullptr) return nullptr;
		if (data == node->value) {
			return node;
		}
		else if (data > node->value) {
			return searchNode(node->right, data);
		}
		else if (data < node->value) {
			return searchNode(node->left, data);
		}
		return nullptr;
	}
	Node<T>* deleteNode(Node<T>* node, T data) {
		if (node == nullptr) return nullptr;
		if (data > node->value) {
			node->right = deleteNode(node->right, data);
		}
		else if (data < node->value) {
			node->left = deleteNode(node->left, data);
		}
		else {
			if (node->left == nullptr && node->right == nullptr) {
				delete node;
				return nullptr;
			}
			else if (node->right) {
				Node<T>* temp = node->left;
				delete node;
				return temp;
			}
			else if (node->left) {
				Node<T>* temp = node->right;
				delete node;
				return temp;
			}
			else {//!need to be revised!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				Node<T>* successor = node->right;
				while (successor->left) {
					successor = successor->left;
				}
				node->value = successor->value;//! Replace with the smallest vale in the rigth subtree
				node->right = deleteNode(successor->right, successor->value);//!delete the successor node (Last)
			}
		}
		return node;
	}
	Node<T>* findParent(Node<T>* node, T data) {
		if (node == nullptr) return nullptr;
		if ((node->left && node->left->value == data) || (node->right && node->right == data)) {
			return node;
		}
		if (data > node->value) {
			return findParent(node->right, data);
		}
		else if (data < node->value) {
			return findParent(node->left, data);
		}
		return nullptr;
	}
	Node<T>* minVal(Node<T>* node) {
		if (node == nullptr) return nullptr;
		while (node->left) {
			node = node->left;
		}
		return node;
	}
	Node<T>* maxVal(Node<T>* node) {
		if (node == nullptr) return nullptr;
		while (node->right) {
			node = node->right;
		}
		return node;
	}
	//!preOrder
	void preOrder(Node<T>* node) {
		if (node) {
			cout << node->value << " ";
			preOrder(node->left);
			preOrder(node->right);
		}
	}
	//!inOrder
	void inOrder(Node<T>* node) {
		if (node) {
			inOrder(node->left);
			cout << node->value << " ";
			inOrder(node->right);
		}
	}
	void postOrder(Node<T>* node) {
		if (node) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->value << endl;
		}
	}
	int countNodes(Node<T>* node) {
		if (node == nullptr) return 0;
		return 1 + countNodes(node->left) + countNodes(node->right);
	}
	int height(Node<T>* node) {
		if (node == nullptr) return 0;
		return 1 + max(height(node->left), height(node->right));
	}

public:
	BST() {
		root = nullptr;
		size = 0;
	}
	void insertNode(T data) {
		root = insertNode(root, data);
		size++;
	}
	void deleteNode(T data) {
		if (contains(data)) {
			root = deleteNode(root, data);
			size--;
		}
	}
	T findParent(T data) {
		if (root == nullptr) throw std::runtime_error("Tree is empty!");
		if (root->value == data) throw std::logic_error("This is the root itself, it has no parent!");
		Node<T>* node = findParent(root, data);
		if (node == nullptr) throw std::runtime_error("Element not found!");
		return node->value;
	}
	bool contains(T data) {
		return searchNode(root, data) != nullptr;
	}
	int countNodes() {
		return countNodes(root);
	}
	int height() {
		return height(root);
	}
	void preOrder() {
		preOrder(root);
		cout << "\n";
	}
	void inOrder() {
		inOrder(root);
		cout << "\n";
	}
	void postOrder() {
		postOrder(root);
		cout << "\n";
	}
	T maxVal() {
		Node<T>* node = maxVal(root);
		if (node == nullptr) throw std::runtime_error("Tree is empty!");
		return node->value;
	}
	T minVal() {
		Node<T>* node = minVal(root);
		if (node == nullptr) throw std::runtime_error("Tree is empty!");
		return node->value;
	}
	int countNode() {
		return countNodes(root);
	}
	int getSize() {
		return size;
	}
};
