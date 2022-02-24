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
		ConsoleInput(1, "Depth-first search");
		result.clear();
		DepthFirstSearchAlgorithm();
		FileOutput("DepthFirstSearch");
		ConsoleOutput();
	}
	void BreadthFirstSearch() {}
	void Prims() {}
	void Dijkstra() {}
	void AStar() {}
	void FordFulkerson() {}
	void DijkstraBidirectional() {}
	void AStarBidirectional() {}

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
	vector<pair<int, int>> result;
	vector<vector<int>> graph;
	vector<int> AStarAlgorithmVector();

	int h(int current, unordered_map<int, int> came_from);
	void ConsoleOutput() {

		cout << start + 1 << " ";
		for (auto elem : result) {
			cout << elem.second + 1 << " ";
		}
		cout << endl;
	}
	void FileOutput(string name) {
		ofstream out("command.txt");
		out << "new" << endl;
		out << name << endl;		
		for (auto elem : result) {
			out << elem.first << " " << elem.second << " ";
		}
		out.close();
	}
	void ConsoleInput(int count, string name) {
		if (count == 1)
		{
			cout << name << ", enter node number: ";
			cin >> start;
			start--;
		}
		else if (count == 2)
		{
			cout << name << ", enter first node number: ";
			cin >> start;
			start--;
			cout << "Enter last node number: ";
			cin >> goal;
			goal--;			
		}
		
	}
};