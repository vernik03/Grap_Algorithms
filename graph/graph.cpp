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
#include <thread>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

void DepthFirstSearch(const int& count_elems, const vector<vector<int>>& graph) {
	int x;
	cout << "Depth-first search, enter node number: ";
	cin >> x;

	ofstream out("command.txt");
	out << "new" << endl;
	out << "DepthFirstSearch" << endl;

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
		out << node + 1 << " ";
	}
	cout << endl;
	out.close();
}


void BreadthFirstSearch(const int& count_elems, const vector<vector<int>>& graph) {
	int x;
	cout << "Breadth-first search, enter node number: ";
	cin >> x;

	ofstream out("command.txt");
	out << "new" << endl;
	out << "BreadthFirstSearch" << endl;

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
		out << node + 1 << " ";
	}
	cout << endl;	
	out.close();
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
	ofstream out("command.txt");
	out << "new" << endl;
	out << "PrimsAlgorithm" << endl;
	out.close();
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
	ofstream out("command.txt");
	out << "new" << endl;
	out << "DijkstraAlgorithm" << endl;
	out.close();
}

int h(int current, const vector<vector<int>>& graph, unordered_map<int, int> came_from) {
	int h=0;
	for (auto node : came_from)
	{
		h += graph[node.first][node.second];
	}
	return h;
}

void AStarAlgorithm(const int& count_elems, const vector<vector<int>>& graph) {

	int start, goal;
	cout << "A-star algorithm, enter first node number: ";
	cin >> start;
	start--;
	cout << "Enter last node number: ";
	cin >> goal;
	goal--;

	unordered_set<int> open_set;
	open_set.insert(start);
	unordered_map<int, int> came_from;
	map<int, int> g_score;
	for (int i = 0; i < count_elems; i++)
	{
		g_score[i] = INT_MAX;
	}
	g_score[start] = 0;
	map<int, double> f_score;
	for (int i = 0; i < count_elems; i++)
	{
		f_score[i] = INT_MAX;
	}
	f_score[start] = h(start, graph, came_from);

	int current = 0;
	while (!open_set.empty()) {
		current = *(--(open_set.end()));
		for (auto elem : open_set)
		{
			if (f_score.at(elem) < f_score.at(current) && elem != start)
			{
				current = elem;
			}
		}
		if (current == goal) {
			break;
		}
		open_set.extract(current);
		for (int i = 0; i < count_elems; i++) {
			if (graph[current][i])
			{
				int tentative_g_score = g_score[current] + graph[current][i];
				if (tentative_g_score < g_score[i]) {
					came_from[i] = current;
					g_score[i] = tentative_g_score;
					f_score[i] = tentative_g_score + h(i, graph, came_from);
					if (!open_set.count(i))
					{
						open_set.insert(i);
					}
				}
			}
		}
	}
	std::vector<int> total_path = { current };
	while (current != start) {
		current = came_from[current];
		total_path.push_back(current);
	}
	reverse(total_path.begin(), total_path.end());
	for (auto elem : total_path) {
		std::cout << elem + 1 << " ";
	}
	std::cout << std::endl;
	cout << endl;
}

vector<int> AStarAlgorithmVector(const int& count_elems, const vector<vector<int>>& graph, int start, int goal) {
	unordered_set<int> open_set;
	open_set.insert(start);
	unordered_map<int, int> came_from;
	map<int, int> g_score;
	for (int i = 0; i < count_elems; i++)
	{
		g_score[i] = INT_MAX;
	}
	g_score[start] = 0;
	map<int, double> f_score;
	for (int i = 0; i < count_elems; i++)
	{
		f_score[i] = INT_MAX;
	}
	f_score[start] = h(start, graph, came_from);

	int current = 0;
	while (!open_set.empty()) {
		current = *(--(open_set.end()));
		for (auto elem : open_set)
		{
			if (f_score.at(elem) < f_score.at(current) && elem != start)
			{
				current = elem;
			}
		}
		if (current == goal) {
			break;
		}
		open_set.extract(current);
		for (int i = 0; i < count_elems; i++) {
			if (graph[current][i])
			{
				int tentative_g_score = g_score[current] + graph[current][i];
				if (tentative_g_score < g_score[i]) {
					came_from[i] = current;
					g_score[i] = tentative_g_score;
					f_score[i] = tentative_g_score + h(i, graph, came_from);
					if (!open_set.count(i))
					{
						open_set.insert(i);
					}
				}
			}
		}
	}
	std::vector<int> total_path = { current };
	while (current != start) {
		current = came_from[current];
		total_path.push_back(current);
	}
	reverse(total_path.begin(), total_path.end());
	return total_path;
}


void FordFulkersonAlgorithm(const int& count_elems, const vector<vector<int>>& graph) {
	int pathCount = 0;
	int start, goal;
	cout << "Ford-Fulkerson algorithm, enter first node number: ";
	cin >> start;
	start--;
	cout << "Enter last node number: ";
	cin >> goal;
	goal--;
	vector<vector<int>> flow(count_elems, { 0, 0 });
	vector<vector<int>> graph_temp = graph;
	int max_flow = 0;
	set<int> visited_really;
	vector<int> visited;
	map<int, int> parent;
	while (true) {
		visited = AStarAlgorithmVector(count_elems, graph, start, goal);
		for (int i = 0; i < visited.size()-1; i++)
		{
			parent[visited[i + 1]] = visited[i];
		}
		int flag = 0;
		for (int i = 0; i < visited.size(); i++)
		{
			if (visited_really.count(visited[i])>0)
			{
				flag++;
			}
			else
			{
				visited_really.insert(visited[i]);
			}			
		}
		if (flag == visited.size())
		{
			break;
		}

		int path_flow = INT_MAX;
		int s = goal;
		while (s!=start)
		{
			path_flow = min(path_flow, graph_temp[parent[s]][s]);
			s = parent[s];
		}
		max_flow += path_flow;
		int v = goal;
		while (v != start)
		{
			int u = parent[v];
			graph_temp[u][v] -= path_flow;
			graph_temp[v][u] += path_flow;
			v = parent[v];
		}
		/*
		int delta = 10000;
		for (int u = 0; u < visited.size(); u++) // Найти минимальный поток в сети
		{
			delta = min(delta, (graph[visited[u]][u] - flow[visited[u]][u]));
		}
		pathCount++;
		for (int u = 0; u < visited.size(); u++) // По алгоритму Форда-Фалкерсона 
		{
			u--;
			flow[visited[u]][u] += delta;
			flow[u][visited[u]] -= delta;
		}
		max_flow += delta;
		*/
	}
	cout << max_flow << endl;
}

int main()
{
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
			DepthFirstSearch(count_elems, graph);
			BreadthFirstSearch(count_elems, graph);
			PrimsAlgorithm(count_elems, graph);
			DijkstraAlgorithm(count_elems, graph);
			AStarAlgorithm(count_elems, graph);
			FordFulkersonAlgorithm(count_elems, graph);
		});

	thread t2([&]()
		{
			//system("python visual.py");			
		});

	t1.join();
	t2.join();

	
	
}

//    1 - 2
//    | / |
//    3 - 4