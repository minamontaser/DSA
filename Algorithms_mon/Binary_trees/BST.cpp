#include <iostream>
#include <queue>
#include <stdexcept>
#include <climits>

using namespace std;

#define ll long long
#define ld long double

inline void set_fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

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

	Node<T>* insertNode2(Node<T>* node, T data) {//! Alternative version of insertNode
		if (!node) return new Node<T>(data);
		if (node->value == data) throw runtime_error("Duplicated value!");
		(data < node->value ? node->left : node->right) = insertNode2(data < node->value ? node->left : node->right, data);
		return node;
	}

	Node<T>* searchNode(Node<T>* node, T data) {
		if (node == nullptr) {
			return nullptr;
		}
		if (node->value == data) {
			return node;
		}
		return (node->value > data ? searchNode(node->left, data) : searchNode(node->right, data));
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
		if (!node) {
			return nullptr;
		}
		return (node->left ? min_value(node->left) : node);
	}

	Node<T>* max_value(Node<T>* node) {
		if (!node) {
			return nullptr;
		}
		return (node->right ? max_value(node->right) : node);
	}

	int countNodes(Node<T>* node) {
		return (node == nullptr ? 0 : 1 + countNodes(node->left) + countNodes(node->right));
	}

	auto sumNodes(Node<T>* node) -> T {
		return (node == nullptr ? T{} : node->value + sumNodes(node->left) + sumNodes(node->right));
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

	Node<T>* deleteMax(Node<T>* node) {
		if (node == nullptr) return nullptr;
		if (node->right == nullptr) {
			Node<T>* temp = node->left;
			delete node;
			return temp;
		}
		node->right = deleteMax(node->right);
		return node;
	}

	Node<T>* deleteMin(Node<T>* node) {
		if (node == nullptr) return nullptr;
		if (node->left == nullptr) {
			Node<T>* temp = node->right;
			delete node;
			return temp;
		}
		node->left = deleteMin(node->left);
		return node;
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

	void insertNode2(T data) {
		root = insertNode2(root, data);
		size++;
	}

	void deleteNode(T data) {
		if (contains(data)) {
			root = deleteNode(root, data);
			size--;
		}
	}

	void deleteMax() {
		root = deleteMax(root);
		size--;
	}

	void deleteMin() {
		root = deleteMin(root);
		size--;
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

signed main() {

	set_fast_io();

	BST<int> tree;

	cout << "--- Testing insertNode and BFS ---\n";
	ll vals[]{ 50, 30, 70, 20, 40, 60, 80 };
	for (ll& v : vals) tree.insertNode(v);
	tree.BFS(); // Should print 50 30 70 20 40 60 80

	cout << "\n--- Testing insertNode2 ---\n";
	tree.insertNode2(10);
	tree.insertNode2(5);
	tree.insertNode2(15);
	tree.BFS(); // Should print 10 5 15

	cout << "\n--- Testing searchNode ---\n";
	cout << "Searching 40: " << (tree.contains(40) ? "Found" : "Not Found") << endl;
	cout << "Searching 100: " << (tree.contains(100) ? "Found" : "Not Found") << endl;

	cout << "\n--- Testing getMin and getMax ---\n";
	cout << "Min: " << tree.getMin() << endl; // 20
	cout << "Max: " << tree.getMax() << endl; // 80

	cout << "\n--- Testing sumNodes ---\n";
	cout << "Sum of nodes: " << tree.sumNodes() << endl;

	cout << "\n--- Testing countNodes ---\n";
	cout << "Count of nodes: " << tree.countNodes() << endl;

	cout << "\n--- Testing getParent ---\n";
	cout << "Parent of 20: " << tree.getParent(20) << endl;
	cout << "Parent of 70: " << tree.getParent(70) << endl;

	cout << "\n--- Testing deleteNode ---\n";
	tree.deleteNode(20); // Leaf
	tree.deleteNode(30); // Node with one child
	tree.deleteNode(50); // Node with two children (root)
	tree.BFS();

	cout << "\n--- Testing deleteMax and deleteMin ---\n";
	tree.deleteMax();
	tree.deleteMin();
	tree.BFS();

	cout << "\n--- Testing traversals ---\n";
	cout << "In-order: "; tree.printInOrder();
	cout << "Pre-order: "; tree.printPreOrder();
	cout << "Post-order: "; tree.printPostOrder();

	cout << "\n--- Testing getSize and getHeight ---\n";
	cout << "Size: " << tree.getSize() << endl;
	cout << "Height: " << tree.getHeight() << endl;

	cout << "\n--- Edge cases ---\n";
	BST<int> emptyTree;
	try { emptyTree.getMin(); }
	catch (runtime_error& e) { cout << e.what() << endl; }
	try { emptyTree.getParent(1); }
	catch (runtime_error& e) { cout << e.what() << endl; }

	return 0;
}