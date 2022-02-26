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
	void DepthFirstSearch();
	void BreadthFirstSearch();
	void Prims();
	void Dijkstra();
	void AStar();
	void FordFulkerson();
	void DijkstraBidirectional();
	void AStarBidirectional();

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

	int h(int current, unordered_map<int, int> came_from);
	void ConsoleOutput(string type = "path");
	void FileOutput(string name);
	void ConsoleInput(int count, string name);
	bool OneMoreTime();
};