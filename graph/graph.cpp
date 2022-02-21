#include <iostream>
#include <thread>

#include "Algorithms.h"

using namespace std;

int main()
{
	Algorithms graph;	

	thread t1([&]()
		{
			//graph.DepthFirstSearch();
			//graph.BreadthFirstSearch();
			//graph.PrimsAlgorithm();
			graph.DijkstraAlgorithm();
			graph.AStarAlgorithm();
			//graph.FordFulkersonAlgorithm();
			graph.DijkstraBidirectionalAlgorithm();
			graph.AStarBidirectionalAlgorithm();
		});

	thread t2([&]()
		{
			system("python visual.py");
		});

	t1.join();
	t2.join();

	return 0;
}