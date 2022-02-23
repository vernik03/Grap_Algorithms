#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <fstream>
#include <cstdint>

using namespace std;

class Algorithms
{
public:
	Algorithms(const string& filename = "matrix.txt");
	~Algorithms() {};
	void DepthFirstSearch() {
		cout << "Depth-first search, enter node number: ";
		cin >> start;
		start--;
		result.clear();
		DepthFirstSearchAlgorithm();
		cout << start + 1 << " ";
		for (auto elem : result) {
			cout << elem.second + 1 << " ";
		}
		cout << endl;
	}
	void BreadthFirstSearch();
	void Prims();
	void Dijkstram();
	void AStar();
	void FordFulkerson();
	void DijkstraBidirectional();
	void AStarBidirectional();

	void DepthFirstSearchAlgorithm();
	void BreadthFirstSearchAlgorithm();
	void PrimsAlgorithm();
	void DijkstraAlgorithm();
	void AStarAlgorithm();
	void FordFulkersonAlgorithm();
	void DijkstraBidirectionalAlgorithm();
	void AStarBidirectionalAlgorithm();

private:
	int start, goal;
	int count_elems;
	multimap<int, int> result;
	vector<vector<int>> graph;
	int h(int current, unordered_map<int, int> came_from);
	vector<int> AStarAlgorithmVector();
};