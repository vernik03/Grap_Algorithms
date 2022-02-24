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
	void BreadthFirstSearch() {
		ConsoleInput(1, "Breadth-first search");
		result.clear();
		BreadthFirstSearchAlgorithm();
		FileOutput("BreadthFirstSearch");
		ConsoleOutput();
	}
	void Prims() {
		ConsoleInput(1, "Prim's algorithm");
		result.clear();
		PrimsAlgorithm();
		FileOutput("Prims");
		ConsoleOutput("pairs");
	}
	void Dijkstra() {
		ConsoleInput(1, "Dijkstra algorithm");
		result.clear();
		DijkstraAlgorithm();
		FileOutput("Dijkstra");
		ConsoleOutput("distance");
	}
	void AStar() {
		ConsoleInput(2, "A* algorithm");
		result.clear();
		AStarAlgorithm();
		FileOutput("AStar");
		ConsoleOutput();
	}

	void FordFulkerson() {
		ConsoleInput(2, "Ford-Fulkerson algorithm");
		result.clear();
		cout << "Max flow: " << FordFulkersonAlgorithm() << "\n\n";
		FileOutput("FordFulkerson");
	}
	void DijkstraBidirectional() {
		ConsoleInput(2, "Dijkstra bidirectional algorithm");
		result.clear();
		DijkstraBidirectionalAlgorithm();
		//FileOutput("DijkstraBidirectional");
		//ConsoleOutput();
	}
	void AStarBidirectional() {
		ConsoleInput(2, "A* bidirectional algorithm");
		result.clear();
		AStarBidirectionalAlgorithm();
		//FileOutput("AStarBidirectional");
		//ConsoleOutput();
	}

	void DepthFirstSearchAlgorithm();
	void BreadthFirstSearchAlgorithm();
	void PrimsAlgorithm();
	void DijkstraAlgorithm();
	vector<int> AStarAlgorithm(string param = "no_param");
	int FordFulkersonAlgorithm();
	void DijkstraBidirectionalAlgorithm();
	void AStarBidirectionalAlgorithm();

private:
	int start, goal;
	int count_elems;
	vector<pair<int, int>> result;
	vector<vector<int>> graph;
	vector<int> AStarAlgorithmVector();

	int h(int current, unordered_map<int, int> came_from);
	void ConsoleOutput(string type = "path") {
		if (type == "path")
		{
			cout << start + 1 << " ";
			for (auto elem : result) {
				cout << elem.second + 1 << " ";
			}
			cout << "\n\n";
		}
		else if (type == "pairs")
		{
			for (auto elem : result) {
				cout << elem.first + 1 << "-" << elem.second + 1 << " ";
			}
			cout << "\n\n";
		}
		else if (type == "distance")
		{
			for (auto elem : result) {
				cout << start + 1 << " -> " << elem.first + 1 << " = " << elem.second + 1 << endl;
			}
			cout << endl;
		}
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