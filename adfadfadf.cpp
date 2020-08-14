#include <iostream>

using namespace std;

int nodesNumber = 0;
int edgesNumber = 0;
bool* checked = nullptr;

struct Edge {
	int start = 0;
	int end = 0;
	Edge *next = nullptr;

	Edge(int start, int end, Edge *next) {
		this->start = start;
		this->end = end;
		this->next = next;
	}
};

struct EdgeList {
	Edge* head = nullptr;

	void add(int a, int b) {
		Edge* newElement = new Edge(a, b, head);

		head = newElement;
	}

	void clear() {
		while (head != nullptr) {
			Edge* tmp = head->next;
			delete head;
			head = tmp;
		}
	}

	void isAvailable(int v, int &entersCounter) {
		checked[v] = true;
		entersCounter++;
		Edge* current = head;
		while (current != nullptr) {
			if(current->end == v && !checked[current->start]) {
				isAvailable(current->start, entersCounter);
			}
			current = current->next;
		}
	}

	bool hasAvailable() {
		for (int i = 0; i < nodesNumber; ++i) {
			int entersCounter = 0;
			for (int i = 0; i < nodesNumber; ++i) {
				checked[i] = false;
			}

			isAvailable(i, entersCounter);
			if (entersCounter == nodesNumber) {
				return true;
			}
		}
		return false;
	}
};

int main()
{
	cout << "Enter number of nodes:" << endl;
	cin >> nodesNumber;
	checked = new bool [nodesNumber];
	for (int i = 0; i < nodesNumber; ++i) {
		checked[i] = false;
	}

	cout << "Enter number of edges:" << endl;
	cin >> edgesNumber;
	EdgeList graph;
	int startV = 0;
	int endV = 0;
	cout << "Enter edges [start end]" << endl;
	for (int i = 0; i < edgesNumber; ++i) {
		cin >> startV >> endV;
		graph.add(startV - 1, endV - 1);
	}
	cout << graph.hasAvailable();
	graph.clear();
}
