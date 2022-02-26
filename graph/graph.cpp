#include <iostream>
#include <thread>
#include <windows.h>

#include "Algorithms.h"

using namespace std;

void Info() {
	cout << "Here is graph calculator" << endl;
	cout << "Enter 1 to Depth-first search" << endl
		<< "Enter 2 to Breadth-first search" << endl
		<< "Enter 3 to Prim's algorithm" << endl
		<< "Enter 4 to Dijkstra algorithm" << endl
		<< "Enter 5 to A* algorithm" << endl
		<< "Enter 6 to Ford-Fulkerson algorithm" << endl
		<< "Enter 7 to Dijkstra bidirectional algorithm" << endl
		<< "Enter 8 to A* bidirectional algorithm" << endl
		<< "Enter 0 to exit" << endl;
}

void StartAlgorithm(int number, Algorithms& graph) {
	ofstream out;
	switch (number)
	{
	case 1:
		graph.DepthFirstSearch();
		break;
	case 2:
		graph.BreadthFirstSearch();
		break;
	case 3:
		graph.Prims();
		break;
	case 4:
		graph.Dijkstra();
		break;
	case 5:
		graph.AStar();
		break;
	case 6:
		graph.FordFulkerson();
		break;
	case 7:
		graph.DijkstraBidirectional();
		break;
	case 8:
		graph.AStarBidirectional();
		break;
	case 0:
		cout << "See you soon!" << endl;
		out.open("command.txt");
		out << "end" << endl;
		out.close();
		break;
	default:
		break;
	}
}

void Interface(Algorithms& graph) {
	int number = -1;
	ofstream out;
	while (number!=0)
	{
		out.open("command.txt");
		out << "clear" << endl;
		out.close();
		system("cls");
		Info();
		cout << "Yor choice: ";
		cin >> number;

		while (number < 0 || number > 8)
		{
			cout << "Invalid number. Try again: ";
			cin >> number;
		};

		system("cls");

		StartAlgorithm(number, graph);		
	}	
}

int main()
{
	Algorithms graph;	

	thread t1([&]()
		{
			ofstream out("command.txt");
			out.close();
			Interface(graph);
		});

	thread t2([&]()
		{
			system("python visual.py");
		});
	
	t1.join();
	t2.join();

	return 0;
}