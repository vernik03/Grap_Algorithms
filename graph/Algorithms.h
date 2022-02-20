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
	void PrimsAlgorithm();
	void DijkstraAlgorithm();
	void AStarAlgorithm();
	void FordFulkersonAlgorithm();
	void DijkstraBidirectionalAlgorithm();
	void AStarBidirectionalAlgorithm();

private:
	int start, goal;
	int count_elems;
	vector<vector<int>> graph;
	int h(int current, unordered_map<int, int> came_from);
	vector<int> AStarAlgorithmVector();
};