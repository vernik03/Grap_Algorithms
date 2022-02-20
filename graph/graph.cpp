#include <iostream>
#include <thread>

#include "Algorithms.h"

using namespace std;

int main()
{
	Algorithms graph_alg;
	vector<vector<int>> graph;
	int count_elems = 0;
	int elem;
	ifstream in("matrix.txt");
	while (!in.eof())
	{
		in >> elem;
		count_elems++;
	}
	in.close();
	count_elems = sqrt(count_elems);
	ifstream file("matrix.txt");
	for (int i = 0; i < count_elems; i++)
	{
		vector<int> temp;
		for (int j = 0; j < count_elems; j++)
		{
			file >> elem;
			temp.push_back(elem);
		}
		graph.push_back(temp);
		temp.clear();
	}

	thread t1([&]()
		{
			graph_alg.DepthFirstSearch(count_elems, graph);
			graph_alg.BreadthFirstSearch(count_elems, graph);
			graph_alg.PrimsAlgorithm(count_elems, graph);
			graph_alg.DijkstraAlgorithm(count_elems, graph);
			graph_alg.AStarAlgorithm(count_elems, graph);
			graph_alg.FordFulkersonAlgorithm(count_elems, graph);
			graph_alg.DijkstraBidirectionalAlgorithm(count_elems, graph);
			graph_alg.AStarBidirectionalAlgorithm(count_elems, graph);
		});

	thread t2([&]()
		{
			system("python visual.py");
		});

	t1.join();
	t2.join();


	return 0;
}