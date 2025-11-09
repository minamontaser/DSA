#include <iostream>
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
			return new Node(data);
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
		if ((node->left && node->left->value == data) || (node->right && node->right->value == data)) {
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
		if (node == nullptr) {
			return nullptr;
		}
		while (node->left) {
			node = node->left;
		}
		return node;
	}

	Node<T>* max_value(Node<T>* node) {
		if (node == nullptr) {
			return nullptr;
		}
		while (node->right) {
			node = node->right;
		}
		return node;
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
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(height(node->right), height(node->left));
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

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	BST<int> tree;

	// Inserting values
	tree.insertNode(50);
	tree.insertNode(30);
	tree.insertNode(70);
	tree.insertNode(20);
	tree.insertNode(40);
	tree.insertNode(60);
	tree.insertNode(80);

	// Print pre/in/post-order
	cout << "Pre-order Traversal: ";
	tree.printPreOrder();
	cout << "In-order Traversal(sorted): ";
	tree.printInOrder();
	cout << "Post-order Traversal: ";
	tree.printPostOrder();

	// Size
	cout << "Size of tree: " << tree.getSize() << endl;

	// Min and Max
	cout << "Min value: " << tree.getMin() << endl;
	cout << "Max value: " << tree.getMax() << endl;

	// Height of the tree
	cout << "Height: " << tree.getHeight() << endl;

	// Check if a value exists
	cout << "Contains 40? " << (tree.contains(40) ? "Yes" : "No") << endl;

	// Get parent
	try {
		cout << "Parent of 40: " << tree.getParent(40) << endl;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	// Try to get parent of root
	try {
		cout << "Parent of 50 (root): " << tree.getParent(50) << endl;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	// Try inserting a duplicate value
	try {
		tree.insertNode(50);  // Should throw an error
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	// Delete a node
	tree.deleteNode(30);
	cout << "In-order after deleting 30: ";
	tree.printInOrder();

	// Delete a node with one child (40)
	tree.deleteNode(40);
	cout << "In-order after deleting 40: ";
	tree.printInOrder();

	// Delete root node (50)
	tree.deleteNode(50);
	cout << "In-order after deleting root 50: ";
	tree.printInOrder();

	// Test height after deletions
	cout << "Height after deletions: " << tree.getHeight() << endl;

	// Test deleting a node that does not exist
	tree.deleteNode(100);  // Does nothing as 100 is not in the tree
	cout << "In-order after trying to delete 100: ";
	tree.printInOrder();

	// Final size of the tree
	cout << "Final size of tree: " << tree.getSize() << endl;

	return 0;
}