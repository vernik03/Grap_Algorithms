#include <iostream>
#include <thread>

#include "Algorithms.h"

using namespace std;

int main()
{
	Algorithms graph;	

	thread t1([&]()
		{
			graph.DepthFirstSearch();
			graph.BreadthFirstSearch();
			graph.Prims();
			graph.Dijkstra();
			graph.AStar();
			graph.FordFulkerson();
			graph.DijkstraBidirectional();
			graph.AStarBidirectional();
		});

	thread t2([&]()
		{
			system("python visual.py");
		});

	t1.join();
	t2.join();

	return 0;
}