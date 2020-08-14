// Example program
#include <iostream>

using namespace std;

int nodes_n = 0;
int edges_n = 0;
bool* checked = NULL;

struct Edge {
	int start = 0;
	int end = 0;
	Edge* next = NULL;
};

struct EdgeList {
	Edge* head = NULL;

	void add(int a, int b) {
		Edge* newElement = new Edge;
		newElement->start = a;
		newElement->end = b;
		newElement->next = head;

		head = newElement;
	}

	void clear() {
		while (head != NULL) {
			Edge* tmp = head->next;
			delete head;
			head = tmp;
		}
	}

	void isAvailable(int v, int &e_counter) {
		checked[v] = true;
		e_counter++;
		cout << "E_counter " << e_counter << endl;
		Edge* cur = head;
		while (cur != NULL) {
			if(cur->end == v && !checked[cur->start]) {
				isAvailable(cur->start, e_counter);
			}
			cur = cur->next;
		}
	}

	bool hasAvailable() {
		for (int i = 0; i < nodes_n; ++i) {
			int e_counter = 0;
			for (int i = 0; i < nodes_n; ++i) {
				checked[i] = false;
			}
			isAvailable(i, e_counter);
			if (e_counter == nodes_n) {
				return true;
			}
		}
		return false;
	}
};

int main()
{
	cin >> nodes_n;
	checked = new bool [nodes_n];
	for (int i = 0; i < nodes_n; ++i) {
		checked[i] = false;
	}

	cin >> edges_n;
	EdgeList graph;
	int a = 0;
	int b = 0;
	cout << "Enter edges" << endl;
	for (int i = 0; i < edges_n; ++i) {
		cin >> a >> b;
		graph.add(a - 1, b - 1);
	}
	cout << "started" << endl;
	cout << graph.hasAvailable();
	graph.clear();
}
