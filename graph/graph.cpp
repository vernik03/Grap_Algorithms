//#define _USE_MATH_DEFINES 
//#include "../matplotlib-cpp_x86-windows/include/matplotlibcpp.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <map>
#include <string>
#include <stack>
#include <queue>

using namespace std;

void DepthFirstSearch(const int& count_elems, const vector<vector<int>>& graph) {
	int x;
	cout << "Depth-first search, enter node number: ";
	cin >> x;

	vector<int> nodes(count_elems, 0); // вершины графа
	stack<int> my_stack;
	my_stack.push(x - 1); // помещаем в очередь первую вершину
	while (!my_stack.empty())
	{ // пока стек не пуст
		int node = my_stack.top(); // извлекаем вершину
		my_stack.pop();
		if (nodes[node] == 2) continue;
		nodes[node] = 2; // отмечаем ее как посещенную
		for (int j = count_elems - 1; j >= 0; j--)
		{ // проверяем для нее все смежные вершины
			if (graph[node][j] && nodes[j] != 2)
			{ // если вершина смежная и не обнаружена
				my_stack.push(j); // добавляем ее в cтек
				nodes[j] = 1; // отмечаем вершину как обнаруженную
			}
		}
		cout << node + 1 << " "; // выводим номер вершины
	}
	cout << endl;
}


void BreadthFirstSearch(const int& count_elems, const vector<vector<int>>& graph) {
	int x;
	cout << "Breadth-first search, enter node number: ";
	cin >> x;

	vector<int> nodes(count_elems, 0); // вершины графа
	queue<int> my_queue;
	my_queue.push(x-1); // помещаем в очередь первую вершину
	while (!my_queue.empty())
	{ // пока очередь не пуста
		int node = my_queue.front(); // извлекаем вершину
		my_queue.pop();
		nodes[node] = 2; // отмечаем ее как посещенную
		for (int j = 0; j <= count_elems - 1; j++)
		{ // проверяем для нее все смежные вершины
			if (graph[node][j] && nodes[j] == 0)
			{ // если вершина смежная и не обнаружена
				my_queue.push(j); // добавляем ее в очередь
				nodes[j] = 1; // отмечаем вершину как обнаруженную
			}
		}
		cout << node + 1 << " "; // выводим номер вершины
	}
	cout << endl;
}

void PrimsAlgorithm(const int& count_elems, const vector<vector<int>>& graph) {
	int x;
	cout << "Prim's algorithm, enter node number: ";
	cin >> x;

	vector<int> weights(count_elems, INT_MAX);
	vector<int> ancestor(count_elems, NULL);
	vector<pair<int, int>> edges;
	weights[x - 1] = 0;
	queue<int> my_queue;
	for (int i = 0; i < count_elems; i++)
	{
		my_queue.push(i);
	}
	int v = my_queue.front();
	my_queue.pop();
	while (!my_queue.empty())
	{ // пока очередь не пуста
		
		for (int j = 0; j <= count_elems - 1; j++)
		{ // проверяем для нее все смежные вершины
			bool flag = false;
			queue<int> temp;
			while (!my_queue.empty())
			{
				temp.push(my_queue.front());
				if (my_queue.front() == j)
				{
					flag = true;
				}
				my_queue.pop();
			}
			while (!temp.empty())
			{
				my_queue.push(temp.front());
				temp.pop();
			}
			if (graph[v][j] && flag && graph[v][j] < weights[j])
			{ // если вершина смежная и не обнаружена
				weights[j] = graph[v][j];
				ancestor[j] = v;
			}
		}
		v = my_queue.front();
		my_queue.pop();
		edges.push_back(make_pair(ancestor[v], v));
	}
	for (auto pair : edges) {
		cout << pair.first + 1 << "-" << pair.second + 1 << " ";
	}	
	cout << endl;
}

void DijkstraAlgorithm(const int& count_elems, const vector<vector<int>>& graph)
{
	int x;
	cout << "Dijkstra's algorithm, enter node number: ";
	cin >> x;

	vector<int> distance(count_elems, INT_MAX);
	int count, v;
	vector<bool> visited(count_elems, 0);
	distance[x-1] = 0;
	for (int j = 0; j < count_elems - 1; j++)
	{
		int min = INT_MAX;
		for (int i = 0; i < count_elems; i++)
		{
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i];
				v = i;
			}
		}
		visited[v] = true;
		for (int i = 0; i < count_elems; i++)
		{
			if (!visited[i] && graph[v][i] && distance[v] + graph[v][i] < distance[i])
			{
				distance[i] = distance[v] + graph[v][i];
			}
		}
	}
	for (int i = 0; i < count_elems; i++)
	{
		if (distance[i] != INT_MAX)
		{
			cout << x - 1 << " > " << i + 1 << " = " << distance[i] << endl;
		}
		else
		{
			cout << x - 1 << " > " << i + 1 << " = " << "no path" << endl; 
		}
	}
}

int main()
{
    vector<vector<int>> graph;
	int count_elems = 0;
	bool elem;
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
	
	DepthFirstSearch(count_elems, graph);
	BreadthFirstSearch(count_elems, graph);
	PrimsAlgorithm(count_elems, graph);
	DijkstraAlgorithm(count_elems, graph);
}


//    1 - 2
//    | / |
//    3 - 4