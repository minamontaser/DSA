#include <iostream>
#include <queue>
#include <stdexcept>
#include <climits>

using namespace std;

template<class T> struct Node {
	T value;
	Node<T>* right, * left;

	Node(T value) {
		this->value = value;
		right = left = nullptr;
	}
};

template<class T> class BST {
private:
	Node<T>* root;
	int size;

	Node<T>* insertNode(Node<T>* node, T data) {
		if (node == nullptr) {
			return new Node<T>(data);
		}
		if (node->value == data) {
			throw runtime_error("Duplicated value!");
		}
		if (data > node->value) {
			node->right = insertNode(node->right, data);
		}
		else if (data < node->value) {
			node->left = insertNode(node->left, data);
		}
		return node;
	}

	Node<T>* searchNode(Node<T>* node, T data) {
		if (node == nullptr) {
			return nullptr;
		}
		if (node->value == data) {
			return node;
		}
		else if (node->value < data) {
			return searchNode(node->right, data);
		}
		else if (node->value > data) {
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
		else {//! I'm totally cooked successfully ;)
			if (node->left == nullptr && node->right == nullptr) {
				delete node;
				return nullptr;
			}
			else if (node->right == nullptr) {
				Node<T>* temp = node->left;
				delete node;
				return temp;
			}
			else if (node->left == nullptr) {
				Node<T>* temp = node->right;
				delete node;
				return temp;
			}
			else {
				Node<T>* successor = node->right;
				while (successor->left) {
					successor = successor->left;
				}
				node->value = successor->value;
				node->right = deleteNode(node->right, successor->value);
			}
		}
		return node;
	}

	Node<T>* findParent(Node<T>* node, T data) {
		if (node == nullptr || node->value == data) return nullptr;
		if ((node->left && node->left->value == data) || 
			(node->right && node->right->value == data)) {
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

	Node<T>* min_value(Node<T>* node) {
		if (node == nullptr) return nullptr;
		if (node->left == nullptr) return node;
		return min_value(node->left);
	}

	Node<T>* max_value(Node<T>* node) {
		if (node == nullptr) return nullptr;
		if (node->right == nullptr) return node;
		return max_value(node->right);
	}

	int countNodes(Node<T>* node) {
		if (node == nullptr) return 0;
		return 1 + countNodes(node->left) + countNodes(node->right);
	}

	int sumNodes(Node<T>* node) {
		if (node == nullptr) return 0;
		return node->value + sumNodes(node->right) + sumNodes(node->left);
	}

	int height(Node<T>* node) {
		if (node == nullptr) return 0;
		return 1 + max(height(node->left), height(node->right));
	}

	void BFS(Node<T>* node) {
		if (node == nullptr) return;
		queue<Node<T>*> que;
		que.push(node);
		while (!que.empty()) {
			Node<T>* temp = que.front();
			que.pop();
			cout << temp->value << " ";
			if (temp->left) que.push(temp->left);
			if (temp->right) que.push(temp->right);
		}
	}

	void preorder(Node<T>* node) {
		if (node) {
			cout << node->value << " ";
			preorder(node->left);
			preorder(node->right);
		}
	}

	void inorder(Node<T>* node) {
		if (node) {
			inorder(node->left);
			cout << node->value << " ";
			inorder(node->right);
		}
	}

	void postorder(Node<T>* node) {
		if (node) {
			postorder(node->left);
			postorder(node->right);
			cout << node->value << " ";
		}
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

	bool contains(T data) {
		return searchNode(root, data) != nullptr;
	}

	void BFS() {
		BFS(root);
		cout << endl;
	}

	void printInOrder() {
		inorder(root);
		cout << endl;
	}

	void printPreOrder() {
		preorder(root);
		cout << endl;
	}

	void printPostOrder() {
		postorder(root);
		cout << endl;
	}

	int getSize() {
		return size;
	}

	int getHeight() {
		return height(root);
	}

	T getMin() {
		Node<T>* node = min_value(root);
		if (node == nullptr) throw runtime_error("Tree is empty!");
		return node->value;
	}

	T getMax() {
		Node<T>* node = max_value(root);
		if (node == nullptr) throw runtime_error("Tree is empty!");
		return node->value;
	}

	int countNodes() {
		return countNodes(root);
	}

	int sumNodes() {
		return sumNodes(root);
	}

	T getParent(T data) {
		if (root == nullptr) {
			throw std::runtime_error("Tree si Empty!");
		}
		if (root->value == data) {
			throw std::runtime_error("This node is the root; it has no parent.");
		}
		Node<T>* temp = findParent(root, data);
		if (temp == nullptr) {
			throw std::runtime_error("Node not found in the tree.");
		}
		return temp->value;
	}
};

int main() {
	BST<int> tree;

	cout << "===== INSERTING NODES =====" << endl;
	int values[] = { 50, 30, 70, 20, 40, 60, 80 };
	for (int v : values) {
		cout << "Inserting: " << v << endl;
		tree.insertNode(v);
	}
	cout << endl;

	cout << "===== BFS TRAVERSAL =====" << endl;
	tree.BFS();

	cout << "===== INORDER (sorted) =====" << endl;
	tree.printInOrder();

	cout << "===== PREORDER =====" << endl;
	tree.printPreOrder();

	cout << "===== POSTORDER =====" << endl;
	tree.printPostOrder();

	cout << "===== TREE PROPERTIES =====" << endl;
	cout << "Size: " << tree.getSize() << endl;
	cout << "Height: " << tree.getHeight() << endl;
	cout << "Min value: " << tree.getMin() << endl;
	cout << "Max value: " << tree.getMax() << endl;
	cout << "Count nodes: " << tree.countNodes() << endl;
	cout << "Sum of nodes: " << tree.sumNodes() << endl;
	cout << endl;

	cout << "===== SEARCH TESTS =====" << endl;
	cout << "Contains 40? " << (tree.contains(40) ? "Yes" : "No") << endl;
	cout << "Contains 99? " << (tree.contains(99) ? "Yes" : "No") << endl;
	cout << endl;

	cout << "===== PARENT TESTS =====" << endl;
	try {
		cout << "Parent of 40: " << tree.getParent(40) << endl;
		cout << "Parent of 20: " << tree.getParent(20) << endl;
		cout << "Parent of 50 (root): " << tree.getParent(50) << endl;
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}
	cout << endl;

	cout << "===== DELETE TESTS =====" << endl;
	cout << "Deleting 20 (leaf)" << endl;
	tree.deleteNode(20);
	tree.printInOrder();

	cout << "Deleting 30 (one child)" << endl;
	tree.deleteNode(30);
	tree.printInOrder();

	cout << "Deleting 50 (root, two children)" << endl;
	tree.deleteNode(50);
	tree.printInOrder();

	cout << "===== FINAL TREE (BFS) =====" << endl;
	tree.BFS();

	return 0;
}
