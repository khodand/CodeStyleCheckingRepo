#include <iostream>
#include <set>

using namespace std;

class MySet {

public:
	MySet() = default;

	void insert(int value) {
		if (top == nullptr) {
			top = new Node(value);
			return;
		}

		Node *nodeToInsert = top->findClosestNode(value);

		if (value == nodeToInsert->value) {
			return;
		}

		if (value > nodeToInsert->value) {
			nodeToInsert->left = new Node(value);
		}
		else {
			nodeToInsert->right = new Node(value);
		}

	}

	void erase(int value) {
		if (value == top->value) {
			Node *left = top->left;
			Node *smallestLeftNode = left->smallestNode();
			smallestLeftNode->right = top->right;

			delete top;
			top = left;
			return;
		}

		Node *ancestor = nullptr;
		Node *current = top;
		Node *next = top;
		while (next != nullptr) {
			ancestor = current;
			current = next;
			if (value == current->value) {
				Node *leftToSave = current->left;
				Node *rightToSave = current->right;

				if (leftToSave == nullptr) {
					leftToSave = rightToSave;
					return;
				}

				Node *smallestNode = leftToSave->smallestNode();
				smallestNode->right = rightToSave;

				delete current;
				if (value > ancestor->value) {
					ancestor->left = leftToSave;
				}
				else {
					ancestor->right = leftToSave;
				}
			}

			next = value > current->value ? current->left : current->right;
		}

	}

	bool exists(int value) {
		Node *closestNode = top->findClosestNode(value);

		return value == closestNode->value;
	}

	~MySet() {
		top->clear();
		delete top;
	}

private:
	struct Node {
		int value;
		Node *left;
		Node *right;

		explicit Node(int value) {
			this->value = value;
			left = nullptr;
			right = nullptr;
		}

		Node *findClosestNode(int value) {
			Node *current = this;
			Node *next = this;
			while (next != nullptr) {
				current = next;
				if (value == current->value) {
					return current;
				}
				next = value > current->value ? current->left : current->right;
			}
			return current;
		}

		Node *smallestNode() {
			return right == nullptr ? this : right->smallestNode();
		}

		void clear() {
			if (left != nullptr) {
				left->clear();
				delete left;
			}

			if (right != nullptr) {
				right->clear();
				delete right;
			}
		};
	};

	Node *top;
};

int main()
{
	MySet mySet;
	mySet.insert(10);
	mySet.insert(15);
	mySet.insert(16);
	mySet.insert(14);
	mySet.insert(5);
	mySet.insert(4);
	mySet.insert(2);
	mySet.insert(7);
	mySet.insert(6);
	mySet.insert(2);
	mySet.insert(1);
	mySet.exists(2);
	mySet.erase(5);
	mySet.insert(5);
	mySet.erase(15);
	mySet.erase(10);

	cout << "ok";

	return 0;
}
