#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Node class (Single linked list)
template <typename T>
class Node {

public:
	T data{};
	Node<T>* next;
	Node() { next = nullptr; }	// Default constructor

	Node(T newData) {	// Parameterized constructor
		data = newData;
		next = nullptr;
	}
};

// List class (Single linked list)
template <typename T>
class SLList {

private:
	Node<T>* head;
	Node<T>* tail;

public:
	SLList() { head = tail = nullptr; }				// Default constructor
	bool isEmpty() { return head == nullptr; }		// Method to check if list is empty
	Node<T>* getHead() { return head; }			// Returns the head of list
	Node<T>* getTail() { return tail; }			// Returns the tail of list

	// Method to insert node at end of list
	void insertAtEnd(T newData) {

		if (isEmpty()) {
			head = tail = new Node<T>(newData);
		}

		else {
			tail->next = new Node<T>(newData);
			tail = tail->next;
		}
	}

	// Method to insert node in sorted order
	void insertSorted(T newData) {

		//Creating and initializing a new node
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		// If list is empty or data to is to be inserted at head
		if (isEmpty() || head->data >= newNode->data) {
			newNode->next = head;
			head = newNode;
		}

		else {	// If data is to be inserted after head

			// Locating node before which new node is to be inserted
			Node<T>* targetNode = head;

			while (targetNode->next != nullptr && targetNode->next->data < newNode->data) {
				targetNode = targetNode->next;
			}

			newNode->next = targetNode->next;
			targetNode->next = newNode;
		}
	}

	// Method to delete node from start of list
	void deleteFromStart() {

		if (isEmpty()) {
			cout << "List is empty!" << endl;
		}

		else {
			Node<T>* targetNode = head;
			head = head->next;
			delete targetNode;
			targetNode = nullptr;
		}
	}

	// Method to delete node from end of list
	void deleteFromEnd() {

		if (isEmpty()) {
			cout << "List is empty!" << endl;
		}

		else {

			// If list has only one node
			if (head == tail) {
				delete tail;
				head = tail = nullptr;
			}

			else {

				// Locating second last node in list
				Node<T>* secondLast = head;

				while (secondLast->next != tail) {
					secondLast = secondLast->next;
				}

				// Deleting last node in list
				secondLast->next = nullptr;
				delete tail;
				tail = secondLast;
			}
		}
	}

	// Method to return size of list
	int getSize() {
		int count = 0;
		Node<T>* tempNode = head;

		while (tempNode != nullptr) {
			count = count + 1;
			tempNode = tempNode->next;
		}

		return count;
	}

	// Method to display the list
	void displayList() {

		if (isEmpty()) {
			cout << "No edges!" << endl;
		}

		else {
			Node<T>* tempNode = head;

			while (tempNode != nullptr) {
				cout << tempNode->data << " ";
				tempNode = tempNode->next;
			}

			cout << endl;
		}
	}

	~SLList() {	// Destructor

		while (head != nullptr) {
			Node<T>* tempNode = head;
			head = head->next;
			delete tempNode;
			tempNode = nullptr;
		}

		tail = nullptr;
	}

	// Overloading operator == for list class
	template <typename U>
	friend bool operator==(SLList<U>& myList, SLList<U>& targetList);
};

// Overloading operator == for list class
template <typename T>
bool operator==(SLList<T>& myList, SLList<T>& targetList) {
	Node<T>* myHead = myList.head;
	Node<T>* targetHead = targetList.head;

	while (myHead != nullptr && targetHead != nullptr) {

		// If any data in lists is unequal
		if (myHead->data != targetHead->data) {
			return false;
		}

		myHead = myHead->next;
		targetHead = targetHead->next;
	}

	// If both lists are ended and all data is equal in them
	if (myHead == nullptr && targetHead == nullptr) {
		return true;
	}

	// If one list is ended and other is not
	return false;
}

// Graph class
template <typename T>
class Graph {

private:
	T* verticesList;		// Array of vertices of graph
	SLList<T>* adjList;		// Adjacency list of edges of vertices (Array of single linked lists)
	int* inDegrees;			// In degree distributions of all vertices
	int* outDegrees;		// Out degree distributions of all vertices
	int verticesCount;		// Total number of vertices in graph
	int edgesCount;			// Total number of edges in graph
	int maxSize;			// Max vertices a graph can have
	bool undirected;		// Set graph is undirected
	int countSCC;
	int countWCC;

public:
	Graph() {	// Default constructor
		verticesList = nullptr;
		adjList = nullptr;
		inDegrees = nullptr;
		outDegrees = nullptr;
		verticesCount = 0;
		edgesCount = 0;
		maxSize = 0;
		undirected = false;
		countSCC = 0;
		countWCC = 0;
	}

	Graph(int size, string graphType = "Directed") {	// Parameterized constructor
		maxSize = size;
		verticesList = new T[maxSize];
		adjList = new SLList<T>[maxSize];

		// If graph is undirected
		if (graphType == "Undirected") {
			undirected = true;
			inDegrees = outDegrees = nullptr;
		}

		// If graph is directed
		else {
			undirected = false;
			inDegrees = new int[maxSize];
			outDegrees = new int[maxSize];

			// Initializing degree arrays
			for (int i = 0; i < maxSize; i++) {
				inDegrees[i] = outDegrees[i] = 0;
			}
		}

		verticesCount = 0;
		edgesCount = 0;
		countSCC = 0;
		countWCC = 0;
	}

	bool isEmpty() { return verticesCount == 0; }		// Checks if graph is empty or not
	int getVerticesCount() { return verticesCount; }	// Return total number of vertices
	int getEdgesCount() { return edgesCount; }			// Return total number of edges
	T* getVerticesList() { return verticesList; }		// Returns vertices list
	SLList<T>* getAdjList() { return adjList; }			// Returns adjacency list

	// Method to insert a new vertex in graph
	void insertVertex(T newVertex) {

		if (verticesCount == maxSize) {
			cout << "Graph is full!" << endl;
		}

		else {
			verticesList[verticesCount] = newVertex;
			verticesCount = verticesCount + 1;
		}
	}

	// Method to insert a new edge in graph
	void insertEdge(T source, T destination) {

		for (int i = 0; i < verticesCount; i++) {	// Locating source vertex and its adjacency list

			if (verticesList[i] == source) {	// If source vertex is located

				for (int j = 0; j < verticesCount; j++) {	// Locating destination vertex and its adjacency list

					if (verticesList[j] == destination) {	// If destination vertex is located

						// If graph is undirected make two way relationship
						if (undirected) {
							adjList[i].insertAtEnd(destination);
							adjList[j].insertAtEnd(source);
						}

						else {	// If graph is undirected make one way relationship
							adjList[i].insertAtEnd(destination);
							outDegrees[i] = outDegrees[i] + 1;	// Incrementing out degree of source vertex
							inDegrees[j] = inDegrees[j] + 1;	// Incrementing in degree of destination vertex
						}

						edgesCount = edgesCount + 1;
						return;
					}
				}

				//cout << "Error finding destination ..." << endl;
				// If destination vertex is not found make it and then insert edge again
				insertVertex(destination);
				insertEdge(source, destination);
				return;
			}
		}

		//cout << "Error finding source ..." << endl;
		// If source vertex is not found make it and then insert edge again
		insertVertex(source);
		insertEdge(source, destination);
	}

	// Method to find degree of a vertex
	int getOutDegree(T targetVertex) {

		// If graph is undirected there is no in degree
		if (undirected) { return -1; }

		for (int i = 0; i < verticesCount; i++) {

			if (targetVertex == verticesList[i]) {
				return outDegrees[i];
			}
		}

		cout << "Error finding vertex ..." << endl;
		return -1;
	}

	// Method to find in degree of a vertex
	int getInDegree(T targetVertex) {

		// If graph is undirected there is no out degree
		if (undirected) { return -1; }

		for (int i = 0; i < verticesCount; i++) {

			if (targetVertex == verticesList[i]) {
				return inDegrees[i];
			}
		}

		cout << "Error finding vertex ..." << endl;
		return -1;
	}

	// Method to get number of source vertices
	int getSourceCount() {

		// If graph is undirected there is no source vertices
		if (undirected) { return -1; }

		int count = 0;

		for (int i = 0; i < verticesCount; i++) {

			// If in degree of a vertex is zero it is a source vertex
			if (inDegrees[i] == 0) { count = count + 1; }
		}

		return count;
	}

	// Method to get number of source vertices
	int getSinkCount() {

		// If graph is undirected there is no sink vertices
		if (undirected) { return -1; }

		int count = 0;

		for (int i = 0; i < verticesCount; i++) {

			// If out degree of a vertex is zero it is a sink vertex
			if (outDegrees[i] == 0) { count = count + 1; }
		}

		return count;
	}

	// Method to get number of isolated vertices
	int getIsolatedCount() {
		int count = 0;

		for (int i = 0; i < verticesCount; i++) {

			// If out and in degree of a vertex is zero it is an isolated vertex
			if (outDegrees[i] == 0 && inDegrees[i] == 0) {
				count = count + 1;
			}
		}

		return count;
	}

	// Method to get number of bridges in graph
	int getBridgesCount() {
		bool* visited = new bool[verticesCount];		// To keep track of visited nodes
		int* discoveryTime = new int[verticesCount];	// To keep discovery time of vertices
		int* lowValue = new int[verticesCount];			// Each vertex consists of a low value (Vertex other than ancestor)
		int* parent = new int[verticesCount];			// Parent of current vertex
		int count = 0;									// Count of total bridges in graph

		// Initializing parent and visited array
		for (int i = 0; i < verticesCount; i++) {
			parent[i] = -1;
			visited[i] = false;
		}

		// Checking for bridge edges
		for (int i = 0; i < verticesCount; i++) {

			if (!visited[i]) {
				simulationBridge(i, visited, discoveryTime, lowValue, parent, count);
			}
		}

		delete[] visited; visited = nullptr;
		delete[] discoveryTime; discoveryTime = nullptr;
		delete[] lowValue; lowValue = nullptr;
		delete[] parent; parent = nullptr;

		return count;
	}

	// Recursive method to simulate bridges in graph
	void simulationBridge(int vertexIndex, bool* visited, int* dTime, int* lValue, int* parent, int& count) {
		static int time = 0;											// Static time variable for comparison
		visited[vertexIndex] = true;									// Marking current vertex as visited
		dTime[vertexIndex] = lValue[vertexIndex] = ++time;				// Initializing discovery time and low value

		// Transversing through adjacency list of current vertex
		Node<T>* currentAdjHead = adjList[vertexIndex].getHead();

		while (currentAdjHead != nullptr) {

			// Locating index of current vertex
			for (int i = 0; i < verticesCount; i++) {

				if (currentAdjHead->data == verticesList[i]) {

					if (!visited[i]) {
						parent[i] = vertexIndex;
						simulationBridge(i, visited, dTime, lValue, parent, count);

						// If subtree with root verticesList[i] is connected to any ancestor of verticesList[vertexIndex]
						if (lValue[vertexIndex] > lValue[i]) {
							lValue[vertexIndex] = lValue[i];
						}

						/*If lowest vertex of subtree under verticesList[i] is below verticesList[vertexIndex]
						in DFS, then edge between verticesList[i] and verticesList[vertexIndex] is a bridge*/
						if (lValue[i] > dTime[vertexIndex]) {
							//cout << verticesList[vertexIndex] << "\t" << verticesList[i] << endl;
							count = count + 1;
						}
					}

					// Updating low value of verticesList[vertexIndex] for parent calls
					else if (verticesList[i] != verticesList[parent[vertexIndex]]) {

						if (lValue[vertexIndex] > dTime[i]) {
							lValue[vertexIndex] = dTime[i];
						}
					}

					break;
				}
			}

			currentAdjHead = currentAdjHead->next;
		}
	}

	// Method to get number of articulation points in graph
	int getArticulationCount() {
		bool* visited = new bool[verticesCount];				// To keep track of visited nodes
		int* discoveryTime = new int[verticesCount];			// To keep discovery time of vertices
		int* lowValue = new int[verticesCount];					// Each vertex consists of a low value (Vertex other than ancestor)
		int* parent = new int[verticesCount];					// Parent of current vertex
		bool* articulationPoints = new bool[verticesCount];		// If a vertex is articulation point its index will be true
		int count = 0;											// Count of total articulation points in graph

		// Initializing parent and visited array
		for (int i = 0; i < verticesCount; i++) {
			parent[i] = -1;
			visited[i] = false;
			articulationPoints[i] = false;
		}

		// Checking for articulation points
		for (int i = 0; i < verticesCount; i++) {

			if (!visited[i]) {
				simulateArticulation(i, visited, discoveryTime, lowValue, parent, articulationPoints, count);
			}
		}

		// Counting total articulation points
		for (int i = 0; i < verticesCount; i++) {

			if (articulationPoints[i] == true) {
				count = count + 1;
			}
		}

		delete[] visited; visited = nullptr;
		delete[] discoveryTime; discoveryTime = nullptr;
		delete[] lowValue; lowValue = nullptr;
		delete[] parent; parent = nullptr;

		return count;
	}

	// Recursive method to simulate articulation points in graph
	void simulateArticulation(int vertexIndex, bool* visited, int* dTime, int* lValue, int* parent, bool* aPoints, int& count) {
		static int time = 0;											// Static time variable for comparison
		int children = 0;												// To keep count of children of current vertex
		visited[vertexIndex] = true;									// Marking current vertex as visited
		dTime[vertexIndex] = lValue[vertexIndex] = ++time;				// Initializing discovery time and low value

		// Transversing through adjacency list of current vertex
		Node<T>* currentAdjHead = adjList[vertexIndex].getHead();

		while (currentAdjHead != nullptr) {

			// Locating index of current vertex
			for (int i = 0; i < verticesCount; i++) {

				if (currentAdjHead->data == verticesList[i]) {

					if (!visited[i]) {
						children = children + 1;
						parent[i] = vertexIndex;
						simulateArticulation(i, visited, dTime, lValue, parent, aPoints, count);

						// If subtree with root verticesList[i] is connected to any ancestor of verticesList[vertexIndex]
						if (lValue[vertexIndex] > lValue[i]) {
							lValue[vertexIndex] = lValue[i];
						}

						// verticesList[vertexIndex] is root of tree and has 2 or more children 
						if (parent[vertexIndex] == -1 && children > 1) {
							aPoints[vertexIndex] = true;
						}

						// verticesList[vertexIndex] is not root and low value of one of its child is more than its time
						else if (parent[vertexIndex] != -1 && lValue[i] >= dTime[vertexIndex]) {
							aPoints[vertexIndex] = true;
						}
					}

					// Updating low value of verticesList[vertexIndex] for parent calls
					else if (verticesList[i] != verticesList[parent[vertexIndex]]) {

						if (lValue[vertexIndex] > dTime[i]) {
							lValue[vertexIndex] = dTime[i];
						}
					}

					break;
				}
			}

			currentAdjHead = currentAdjHead->next;
		}
	}

	// Shortest path length distribution
	void shortestPathDistribution(int start, int end, int n) {
		int size = (end - start) + 1;					// Calculating size from given range
		int* lengths = new int[size];					// Lengths array of size given range
		int* distributions = new int[size];				// Contains number of paths of current length
		int* distances = new int[verticesCount];		// To keep distances of specific vertex with all other

		// Initializing lengths array
		for (int i = 0; i < size; i++) {
			lengths[i] = start++;
			distributions[i] = 0;
		}

		// Calculating shortest paths for first n vertices
		for (int i = 0; i < n; i++) {

			// Getting distances of current vertex from all other
			getShortestPath(verticesList[i], distances);

			// Setting number of paths lengths accordingly
			for (int j = 0; j < verticesCount; j++) {

				for (int k = 0; k < size; k++) {

					if (distances[j] == lengths[k]) {
						distributions[k]++;
					}
				}
			}
		}

		for (int i = 0; i < size; i++) {
			cout << "Paths of length " << lengths[i] << ": " << distributions[i] << endl;
		}

		delete[] lengths; lengths = nullptr;
		delete[] distributions; distributions = nullptr;
		delete[] distances; distances = nullptr;
	}

	// Method for shortest distances of given vertex with all other
	void getShortestPath(T source, int* distances) {

		if (isEmpty()) {
			cout << "Graph is empty!" << endl;
		}

		else {
			bool sourceFound = false;

			// Making a visited array for tracking each vertex
			bool* visited = new bool[verticesCount];

			// Initializing visited, distances, and previouses arrays
			for (int i = 0; i < verticesCount; i++) {

				if (verticesList[i] == source) {
					visited[i] = sourceFound = true;	// Setting the source vertex as visited
					distances[i] = 0;					// Setting the source vertex distance to itself as zero
					continue;
				}

				visited[i] = false;
				distances[i] = -1;
			}

			// If source is not found
			if (!sourceFound) {
				cout << "Error finding source ..." << endl;
				delete[] visited; visited = nullptr;
				return;
			}

			// Creating a queue for BFS
			SLList<T> q;
			q.insertAtEnd(source);

			while (!q.isEmpty()) {
				T currentVertex = q.getHead()->data; q.deleteFromStart();

				for (int i = 0; i < verticesCount; i++) {	// Locating adjacency list of current vertex

					if (currentVertex == verticesList[i]) {	// If current vertex is located
						Node<T>* currentAdjHead = adjList[i].getHead();

						// Traversing through current vertex adjacency list
						// Checking if edges of current vertex are visited
						while (currentAdjHead != nullptr) {

							for (int j = 0; j < verticesCount; j++) {

								if (currentAdjHead->data == verticesList[j]) {

									if (!visited[j]) {
										visited[j] = true;
										q.insertAtEnd(currentAdjHead->data);

										// Filling distances array accordingly
										distances[j] = distances[i] + 1;
									}

									break;
								}
							}

							currentAdjHead = currentAdjHead->next;
						}

						break;
					}
				}
			}

			delete[] visited; visited = nullptr;
		}
	}

	// Method to get diameter of graph
	int getGraphDiameter() {
		int* distances = new int[verticesCount];		// To keep distances of specific vertex with all other
		int diameter = 0;

		for (int i = 0; i < verticesCount; i++) {

			// Getting distances of current vertex from all other
			getShortestPath(verticesList[i], distances);

			// Setting number of paths lengths accordingly
			for (int j = 0; j < verticesCount; j++) {

				// Diameter will be larget shortest distance between vertices
				if (distances[j] > diameter) { diameter = distances[j]; }
			}
		}

		delete[] distances; distances = nullptr;
		return diameter;
	}

	// Method to display size of larget SCC
	int largetSCC() {
		SLList<T>* arraySCC = SCC();
		int max = 0;

		for (int i = 0; i < countSCC; i++) {

			if (arraySCC[i].getSize() > max) {
				max = arraySCC[i].getSize();
			}
		}

		return max;
	}

	// Method to calculate SCCs
	SLList<T>* SCC() {
		SLList<T>* arraySCC = new SLList<T>[verticesCount];

		// SCC algorithm implementation
		for (int i = 0; i < verticesCount; i++) {
			Node<T>* commonListHead = COMMON(IN(verticesList[i]), OUT(verticesList[i]))->getHead();

			while (commonListHead != nullptr) {
				arraySCC[i].insertSorted(commonListHead->data);
				commonListHead = commonListHead->next;
			}
		}

		// Removing duplications in SCC array
		countSCC = verticesCount;

		for (int i = 0; i < countSCC; i++) {

			for (int j = i + 1; j < countSCC; j++) {

				if (arraySCC[i] == arraySCC[j]) {

					for (int k = j; k < countSCC; k++) {
						arraySCC[k] = arraySCC[k + 1];
					}

					countSCC = countSCC - 1;
					j = j - 1;
				}
			}
		}

		return arraySCC;
	}

	// BFS for SCC returns a reachable list
	SLList<T>* SCC_BFS(T source) {
		SLList<T>* reachable = new SLList<T>();

		if (isEmpty()) {
			cout << "Graph is empty!" << endl;
			return nullptr;
		}

		else {
			bool sourceFound = false;

			// Making a visited array for tracking each vertex
			bool* visited = new bool[verticesCount];
			for (int i = 0; i < verticesCount; i++) {

				// Setting the source vertex as visited
				if (verticesList[i] == source) {
					visited[i] = sourceFound = true;
					continue;
				}

				visited[i] = false;
			}

			// If source is not found
			if (!sourceFound) {
				cout << "Error finding source ..." << endl;
				delete[] visited; visited = nullptr;
				return nullptr;
			}

			// Creating a queue for BFS
			SLList<T> q;
			q.insertAtEnd(source);
			reachable->insertAtEnd(source);

			while (!q.isEmpty()) {
				T currentVertex = q.getHead()->data; q.deleteFromStart();

				for (int i = 0; i < verticesCount; i++) {	// Locating adjacency list of current vertex

					if (currentVertex == verticesList[i]) {	// If current vertex is located
						Node<T>* currentAdjHead = adjList[i].getHead();

						// Traversing through current vertex adjacency list
						// Checking if edges of current vertex are visited
						while (currentAdjHead != nullptr) {

							for (int j = 0; j < verticesCount; j++) {

								if (currentAdjHead->data == verticesList[j]) {

									if (!visited[j]) {
										visited[j] = true;
										q.insertAtEnd(currentAdjHead->data);
										reachable->insertAtEnd(currentAdjHead->data);
									}

									break;
								}
							}

							currentAdjHead = currentAdjHead->next;
						}

						break;
					}
				}
			}

			delete[] visited; visited = nullptr;
			return reachable;
		}
	}

	// Method to get IN list for SCC
	SLList<T>* IN(T source) {
		SLList<T>* inList = new SLList<T>();

		for (int i = 0; i < verticesCount; i++) {
			Node<T>* reachableHead = SCC_BFS(verticesList[i])->getHead();

			while (reachableHead != nullptr) {

				if (source == reachableHead->data) {
					inList->insertAtEnd(verticesList[i]);
					break;
				}

				reachableHead = reachableHead->next;
			}
		}

		return inList;
	}

	// Method to get OUT list for SCC
	SLList<T>* OUT(T source) {
		SLList<T>* outList = SCC_BFS(source);
		return outList;
	}

	// Method to get common elements of IN and OUT lists for SCC
	SLList<T>* COMMON(SLList<T>* inList, SLList<T>* outList) {
		SLList<T>* commonList = new SLList<T>();
		Node<T>* inHead = inList->getHead();

		while (inHead != nullptr) {
			Node<T>* outHead = outList->getHead();

			while (outHead != nullptr) {

				if (inHead->data == outHead->data) {
					commonList->insertAtEnd(inHead->data);
				}

				outHead = outHead->next;
			}

			inHead = inHead->next;
		}

		return commonList;
	}

	// Method to display size distribution of SCCs
	void displayDistributionSCC(int start, int end) {
		int size = (end - start) + 1;					// Calculating size from given range
		int* lengths = new int[size];					// Lengths array of size given range
		int* distributions = new int[size];				// Contains number of paths of current length

		// Initializing lengths array
		for (int i = 0; i < size; i++) {
			lengths[i] = start++;
			distributions[i] = 0;
		}

		SLList<T>* arraySCC = SCC();

		for (int i = 0; i < countSCC; i++) {

			for (int j = 0; j < size; j++) {

				if (arraySCC[i].getSize() == lengths[j]) {
					distributions[j] = distributions[j] + 1;
				}
			}
		}

		for (int i = 0; i < size; i++) {
			cout << "SCCs of size " << lengths[i] << ": " << distributions[i] << endl;
		}

		delete[] lengths; lengths = nullptr;
		delete[] distributions; distributions = nullptr;
	}

	// Method to display size of larget WCC
	int largetWCC() {
		SLList<T>* arrayWCC = WCC();
		int max = 0;

		for (int i = 0; i < countWCC; i++) {

			if (arrayWCC[i].getSize() > max) {
				max = arrayWCC[i].getSize();
			}
		}

		return max;
	}

	// Method to calculate WCCs
	SLList<T>* WCC() {
		SLList<T>* arrayWCC = new SLList<T>[verticesCount];

		// WCC algorithm implementation
		for (int i = 0; i < verticesCount; i++) {
			Node<T>* reachableHead = SCC_BFS(verticesList[i])->getHead();

			while (reachableHead != nullptr) {
				arrayWCC[i].insertSorted(reachableHead->data);
				reachableHead = reachableHead->next;
			}
		}

		// Removing duplications in SCC array
		countWCC = verticesCount;

		for (int i = 0; i < countWCC; i++) {

			for (int j = i + 1; j < countWCC; j++) {

				if (arrayWCC[i] == arrayWCC[j]) {

					for (int k = j; k < countWCC; k++) {
						arrayWCC[k] = arrayWCC[k + 1];
					}

					countWCC = countWCC - 1;
					j = j - 1;
				}
			}
		}

		return arrayWCC;
	}

	// Method to display size distribution of SCCs
	void displayDistributionWCC(int start, int end) {
		int size = (end - start) + 1;					// Calculating size from given range
		int* lengths = new int[size];					// Lengths array of size given range
		int* distributions = new int[size];				// Contains number of paths of current length

		// Initializing lengths array
		for (int i = 0; i < size; i++) {
			lengths[i] = start++;
			distributions[i] = 0;
		}

		SLList<T>* arrayWCC = WCC();

		for (int i = 0; i < countWCC; i++) {

			for (int j = 0; j < size; j++) {

				if (arrayWCC[i].getSize() == lengths[j]) {
					distributions[j] = distributions[j] + 1;
				}
			}
		}

		for (int i = 0; i < size; i++) {
			cout << "WCCs of size " << lengths[i] << ": " << distributions[i] << endl;
		}

		delete[] lengths; lengths = nullptr;
		delete[] distributions; distributions = nullptr;
	}

	// Method to display indegree distribution table
	void displayInDegreeDistribution(int start, int end) {
		int size = (end - start) + 1;					// Calculating size from given range
		int* lengths = new int[size];					// Lengths array of size given range
		int* distributions = new int[size];				// Contains number of paths of current length

		// Initializing lengths array
		for (int i = 0; i < size; i++) {
			lengths[i] = start++;
			distributions[i] = 0;
		}

		for (int i = 0; i < verticesCount; i++) {
			int currentDegree = getInDegree(verticesList[i]);

			for (int j = 0; j < size; j++) {

				if (currentDegree == lengths[j]) {
					distributions[j] = distributions[j] + 1;
				}
			}
		}

		cout << "In-Degree\tDistribution" << endl;
		for (int i = 0; i < size; i++) {
			cout << i + 1 << "\t\t" << distributions[i] / (float)verticesCount << endl;
		}

		delete[] lengths; lengths = nullptr;
		delete[] distributions; distributions = nullptr;
	}

	// Method to display outdegree distribution table
	void displayOutDegreeDistribution(int start, int end) {
		int size = (end - start) + 1;					// Calculating size from given range
		int* lengths = new int[size];					// Lengths array of size given range
		int* distributions = new int[size];				// Contains number of paths of current length

		// Initializing lengths array
		for (int i = 0; i < size; i++) {
			lengths[i] = start++;
			distributions[i] = 0;
		}

		for (int i = 0; i < verticesCount; i++) {
			int currentDegree = getOutDegree(verticesList[i]);

			for (int j = 0; j < size; j++) {

				if (currentDegree == lengths[j]) {
					distributions[j] = distributions[j] + 1;
				}
			}
		}

		cout << "Out-Degree\tDistribution" << endl;
		for (int i = 0; i < size; i++) {
			cout << i + 1 << "\t\t" << distributions[i] / (float)verticesCount << endl;
		}

		delete[] lengths; lengths = nullptr;
		delete[] distributions; distributions = nullptr;
	}

	~Graph() {	// Destructor

		if (verticesList != nullptr) {
			delete[] verticesList;
			delete[] adjList;
		}

		if (inDegrees != nullptr) {
			delete[] inDegrees;
			delete[] outDegrees;
		}

		// Dynamic allocations of SCC are not being removed
	}
};

// Method to load data from file
template <typename T>
void loadData(string fileName, Graph<T>& g) {
	ifstream ifile(fileName);

	if (ifile) {
		string input = "";						// To take input from file as string
		T previousVertex{};						// To keep the track of previous vertex
		SLList<T> vertices;						// To store all the vertices from file
		SLList<SLList<T>*> edges;				// To store list of edges of all vertices
		SLList<T>* currentEdges = nullptr;		// To make and store current list of edges

		// Ignoring first 4 lines in input file
		getline(ifile, input);
		getline(ifile, input);
		getline(ifile, input);
		getline(ifile, input);

		while (getline(ifile, input)) {
			T vertex{};
			T edge{};
			bool tab = false;

			// Tokenizing and saving input string
			for (int i = 0; input[i] != '\0'; i++) {

				if (input[i] == '\t') { tab = true; continue; }
				if (tab) { edge = (edge * 10) + (input[i] - 48); }
				else { vertex = (vertex * 10) + (input[i] - 48); }
			}

			// If next vertex in file is located
			if (previousVertex != vertex) {
				g.insertVertex(vertex);				// Inserting current vertex in graph
				vertices.insertAtEnd(vertex);		// Making a list of vertices to insert edges afterwards

				// Saving edges list of current vertex
				if (currentEdges != nullptr) { edges.insertAtEnd(currentEdges); }

				currentEdges = new SLList<T>();		// Making new edges list for next vertex
				previousVertex = vertex;
			}

			currentEdges->insertAtEnd(edge);
		}

		// Saving edges list of current vertex (Last in file)
		if (currentEdges != nullptr) { edges.insertAtEnd(currentEdges); }

		// Inserting edges in graph
		Node<T>* verticesHead = vertices.getHead();
		Node<SLList<T>*>* edgesHead = edges.getHead();

		while (verticesHead != nullptr) {
			Node<T>* currentList = edgesHead->data->getHead();

			while (currentList != nullptr) {

				// If data is not 0 means there is an edge
				if (currentList->data != 0) {
					g.insertEdge(verticesHead->data, currentList->data);
				}

				currentList = currentList->next;
			}

			verticesHead = verticesHead->next;
			edgesHead = edgesHead->next;
		}

		// Deleting edges lists of all vertices (Deallocating memory)
		edgesHead = edges.getHead();

		while (edgesHead != nullptr) {
			currentEdges = edgesHead->data;
			delete currentEdges;
			edgesHead = edgesHead->next;
		}

		ifile.close();
	}

	else {
		cout << "Error opening file ..." << endl;
	}
}

int main() {

	// Test on Data Set 1

	Graph<int> g1(5500);
	Graph<int> g2(5500, "Undirected");	// For WCCs

	// Loading data from files
	loadData<int>("CA-GrQc.txt", g1);
	loadData<int>("CA-GrQc.txt", g2);

	// loadData<int>("temp.txt", g);

	int input = -1;

	while (input != 16) {
		cout << "\n1 - Display number of nodes." << endl;
		cout << "2 - Display number of edges." << endl;
		cout << "3 - Display number of source nodes." << endl;
		cout << "4 - Display number of sink nodes." << endl;
		cout << "5 - Display number of isolated nodes." << endl;
		cout << "6 - Display number of bridge edges." << endl;
		cout << "7 - Display number of articulation nodes." << endl;
		cout << "8 - Display shortest path length distribution." << endl;
		cout << "9 - Display the diameter of the graph." << endl;
		cout << "10 - Display in-degree distribution table." << endl;
		cout << "11 - Display out-degree distribution table." << endl;
		cout << "12 - Display the size of the largest SCC." << endl;
		cout << "13 - Display the size distribution of all SCCs." << endl;
		cout << "14 - Display the size of the largest WCC." << endl;
		cout << "15 - Display the size distribution of all WCCs." << endl;
		cout << "16 - Quit." << endl;
		cout << "\nEnter choice: "; cin >> input;

		if (input == 1)
		{
			cout << "\nNumber of nodes: " << g1.getVerticesCount() << endl;
		}

		else if (input == 2)
		{
			cout << "\nNumber of edges: " << g1.getEdgesCount() << endl;
		}

		else if (input == 3)
		{
			cout << "\nNumber of source nodes: " << g1.getSourceCount() << endl;
		}

		else if (input == 4)
		{
			cout << "\nNumber of sink nodes: " << g1.getSinkCount() << endl;
		}

		else if (input == 5)
		{
			cout << "\nNumber of isolated nodes: " << g1.getIsolatedCount() << endl;
		}

		else if (input == 6)
		{
			cout << "\nNumber of bridge edges: " << g1.getBridgesCount() << endl;
		}

		else if (input == 7)
		{
			cout << "\nNumber of articulation nodes: " << g1.getArticulationCount() << endl;
		}

		else if (input == 8)
		{
			cout << "\nShortest path length distribution (Length range 1 - 40, First 10 nodes):\n\n";
			g1.shortestPathDistribution(1, 40, 10);
		}

		else if (input == 9)
		{
			cout << "\nDiameter of graph: " << g1.getGraphDiameter() << endl;
		}

		else if (input == 10)
		{
			cout << "\nIn degree distribution table (First 50):\n\n";
			g1.displayInDegreeDistribution(1, 50);
		}

		else if (input == 11)
		{
			cout << "\nOut degree distribution table (First 50):\n\n";
			g1.displayOutDegreeDistribution(1, 50);
		}

		else if (input == 12)
		{
			cout << "\nSize of larget SCC: " << g1.largetSCC() << endl;
		}

		else if (input == 13)
		{
			cout << "\nSize distribution of all SCCs (First 50):\n\n";
			g1.displayDistributionSCC(1, 50);
		}

		else if (input == 14)
		{
			cout << "\nSize of larget WCC: " << g2.largetWCC() << endl;
		}

		else if (input == 15)
		{
			cout << "\nSize distribution of all WCCs (First 50):\n\n";
			g2.displayDistributionWCC(1, 50);
		}

		else if (input == 16)
		{
			continue;
		}

		else {
			cout << "\nInvalid input!" << endl;
		}
	}

	cout << "\nExiting ..." << endl;
	return 0;
}