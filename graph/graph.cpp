#include <iostream>
#include <thread>

#include "Algorithms.h"

using namespace std;

int main()
{
	Algorithms graph;	

	thread t1([&]()
		{
			bool flag = true;
			while (flag)
			{
				graph.DepthFirstSearch();
				graph.BreadthFirstSearch();
				graph.Prims();
				graph.Dijkstra();
				graph.AStar();
				graph.FordFulkerson();
				graph.DijkstraBidirectional();
				graph.AStarBidirectional();
				cout << "Again? ";
				cin >> flag;
				cout << endl;
			}
			return 0;
		});

	thread t2([&]()
		{
			system("python visual.py");
		});

	t1.join();
	t2.join();

	return 0;
}