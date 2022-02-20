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
	Algorithms() {};
	~Algorithms() {};
	void DepthFirstSearch(const int& count_elems, const vector<vector<int>>& graph);
	void BreadthFirstSearch(const int& count_elems, const vector<vector<int>>& graph);
	void PrimsAlgorithm(const int& count_elems, const vector<vector<int>>& graph);
	void DijkstraAlgorithm(const int& count_elems, const vector<vector<int>>& graph);
	void AStarAlgorithm(const int& count_elems, const vector<vector<int>>& graph);
	void FordFulkersonAlgorithm(const int& count_elems, const vector<vector<int>>& graph);
	void DijkstraBidirectionalAlgorithm(const int& count_elems, const vector<vector<int>>& graph);
	void AStarBidirectionalAlgorithm(const int& count_elems, const vector<vector<int>>& graph);

private:
	int h(int current, const vector<vector<int>>& graph, unordered_map<int, int> came_from);
	vector<int> AStarAlgorithmVector(const int& count_elems, const vector<vector<int>>& graph, int start, int goal);
};