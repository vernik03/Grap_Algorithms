#pragma once
#include "Algorithms.h"

using namespace std;

Algorithms::Algorithms(const string& filename) {
	count_elems = 0;
	int elem;
	ifstream in(filename);
	while (!in.eof())
	{
		in >> elem;
		count_elems++;
	}
	in.close();
	count_elems = sqrt(count_elems);
	ifstream file(filename);
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
};

void Algorithms::DepthFirstSearchAlgorithm() {

	vector<int> nodes(count_elems, 0);
	stack<int> my_stack;
	vector<bool> visited_nodes(count_elems, false);

	my_stack.push(start);
	visited_nodes[start] = true;
	int node = my_stack.top();
	while (!my_stack.empty())
	{
		bool find_next = false;
		for (int j = 0; j < count_elems; j++)
		{

			if (graph[node][j] & !visited_nodes[j])
			{
				
				find_next = true;
				my_stack.push(j);
				result.push_back(make_pair(node, j));
				visited_nodes[j] = true;
				node = j;
				break;
			}

		}
		if (!find_next)
		{

			my_stack.pop();
			if (my_stack.empty()) {
				break;
			}
			node = my_stack.top();
		}

	}
}

void Algorithms::BreadthFirstSearchAlgorithm() {
	vector<int> nodes(count_elems, 0);
	queue<int> my_queue;
	my_queue.push(start);
	while (!my_queue.empty())
	{
		int node = my_queue.front();
		my_queue.pop();
		nodes[node] = 2;
		for (int j = 0; j <= count_elems - 1; j++)
		{
			if (graph[node][j] && nodes[j] == 0)
			{
				result.push_back(make_pair(node, j));
				my_queue.push(j);
				nodes[j] = 1;
			}
		}
	}
}

void Algorithms::PrimsAlgorithm() {
	vector<int> weights(count_elems, INT_MAX);
	vector<int> ancestor(count_elems, NULL);
	vector<pair<int, int>> edges;
	weights[start] = 0;
	queue<int> my_queue;
	for (int i = 0; i < count_elems; i++)
	{
		my_queue.push(i);
	}
	int v = my_queue.front();
	my_queue.pop();
	while (!my_queue.empty())
	{

		for (int j = 0; j <= count_elems - 1; j++)
		{
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
			{
				weights[j] = graph[v][j];
				ancestor[j] = v;
			}
		}
		v = my_queue.front();
		my_queue.pop();
		result.push_back(make_pair(ancestor[v], v));
	}
}

void Algorithms::DijkstraAlgorithm()
{
	vector<int> distance(count_elems, INT_MAX);
	int count, v;
	vector<bool> visited(count_elems, 0);
	distance[start] = 0;
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
			result.push_back(make_pair(i, distance[i]));
		}
		else
		{
			result.push_back(make_pair(i, 0));
		}
	}
}	

int Algorithms::h(int current, unordered_map<int, int> came_from) {
	int h = 0;
	for (auto node : came_from)
	{
		h += graph[node.first][node.second];
	}
	return h;
}

vector<int> Algorithms::AStarAlgorithm(string param) {
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
	f_score[start] = h(start, came_from);

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
					f_score[i] = tentative_g_score + h(i, came_from);
					if (!open_set.count(i))
					{
						open_set.insert(i);
					}
				}
			}
		}
	}
	vector<int> total_path = { current };
	while (current != start) {
		current = came_from[current];
		total_path.push_back(current);
	}
	reverse(total_path.begin(), total_path.end());
	if (param != "no_result")
	{
		for (int i = 0; i < total_path.size() - 1; i++)
		{
			result.push_back(make_pair(total_path[i], total_path[i + 1]));
		}
	}
	return total_path;
}

int Algorithms::FordFulkersonAlgorithm() {
	int pathCount = 0;
	vector<vector<int>> flow(count_elems, { 0, 0 });
	vector<vector<int>> graph_temp = graph;
	int max_flow = 0;
	set<int> visited_really;
	vector<int> visited;
	map<int, int> parent;
	while (true) {
		visited = AStarAlgorithm("no_result");
		for (int i = 0; i < visited.size() - 1; i++)
		{
			parent[visited[i + 1]] = visited[i];
		}
		int flag = 0;
		for (int i = 0; i < visited.size(); i++)
		{
			if (visited_really.count(visited[i]) > 0)
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
		while (s != start)
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
	}
	return max_flow;
}

void Algorithms::DijkstraBidirectionalAlgorithm() {
	vector<int> distance_start(count_elems, INT_MAX);
	int count_start, v_start;
	vector<bool> visited_start(count_elems, 0);
	distance_start[start] = 0;
	vector<int> parents_start(count_elems, 0);
	parents_start[start] = start;

	vector<int> distance_goal(count_elems, INT_MAX);
	int count_goal, v_goal;
	vector<bool> visited_goal(count_elems, 0);
	distance_goal[goal] = 0;
	vector<int> parents_goal(count_elems, 0);
	parents_goal[goal] = goal;

	vector<int> result_path;

	for (int j = 0; j < count_elems - 1; j++)
	{
		int min = INT_MAX;
		v_start = count_elems;
		for (int i = 0; i < count_elems; i++)
		{
			if (!visited_start[i] && distance_start[i] <= min)
			{
				if ((v_start != count_elems)) {
					if ((visited_goal[v_start] && (!visited_goal[i]))) {
						//std::cout << "new min" << i << std::endl;
						min = distance_start[i];
						v_start = i;
					}
				}
				else {
					//std::cout << "new min" << i << std::endl;
					min = distance_start[i];
					v_start = i;
				}
			}
		}
		visited_start[v_start] = true;
		for (int i = 0; i < count_elems; i++)
		{
			if (!visited_start[i] && graph[v_start][i] && distance_start[v_start] + graph[v_start][i] < distance_start[i])
			{
				parents_start[i] = v_start;
				distance_start[i] = distance_start[v_start] + graph[v_start][i];
			}
		}

		min = INT_MAX;
		for (int i = 0; i < count_elems; i++)
		{
			if (!visited_goal[i] && distance_goal[i] <= min)
			{
				min = distance_goal[i];
				v_goal = i;
			}
		}
		visited_goal[v_goal] = true;
		for (int i = 0; i < count_elems; i++)
		{
			if (!visited_goal[i] && graph[v_goal][i] && distance_goal[v_goal] + graph[v_goal][i] < distance_goal[i])
			{
				parents_goal[i] = v_goal;
				distance_goal[i] = distance_goal[v_goal] + graph[v_goal][i];
			}
		}

		//std::cout << v_start + 1 << " " << v_goal + 1 << std::endl;

		bool leave = false;
		for (int i = 0; i < visited_start.size() - 1; i++) {
			if (visited_start[i] && visited_goal[i]) {
				std::cout << "Connecting node: " << i + 1 << "\n";
				leave = true;

				int curr = i;
				result_path.push_back(curr);
				while (curr != parents_start[curr]) {
					curr = parents_start[curr];
					result_path.push_back(curr);
				}
				reverse(result_path.begin(), result_path.end());
				curr = i;
				while (curr != parents_goal[curr]) {
					curr = parents_goal[curr];
					result_path.push_back(curr);
				}
				break;
			}
		}
		if (leave) {
			break;
		}
	}
	for (int i = 0; i < result_path.size()-1; i++)
	{
		result.push_back(make_pair(result_path[i], result_path[i + 1]));
	}
}

void Algorithms::AStarBidirectionalAlgorithm() {
	unordered_set<int> open_set_start;
	unordered_set<int> open_set_goal;
	open_set_start.insert(start);
	open_set_goal.insert(goal);
	unordered_map<int, int> came_from_start;
	unordered_map<int, int> came_from_goal;
	map<int, int> g_score_start;
	map<int, int> g_score_goal;

	for (int i = 0; i < count_elems; i++)
	{
		g_score_start[i] = INT_MAX;
	}
	for (int i = count_elems - 1; i >= 0; i--)
	{
		g_score_goal[i] = INT_MAX;
	}
	g_score_start[start] = 0;
	g_score_goal[goal] = 0;
	map<int, double> f_score_start;
	map<int, double> f_score_goal;
	for (int i = 0; i < count_elems; i++)
	{
		f_score_start[i] = INT_MAX;
	}
	for (int i = count_elems - 1; i >= 0; i--)
	{
		f_score_goal[i] = INT_MAX;
	}
	f_score_start[start] = h(start, came_from_start);
	f_score_goal[goal] = h(goal, came_from_goal);

	int current_start = 0;
	int current_goal = 0;
	std::vector<bool> visited_start(count_elems, false);
	std::vector<bool> visited_goal(count_elems, false);
	visited_start[start] = true;
	visited_goal[goal] = true;
	while (!open_set_start.empty() || !open_set_goal.empty()) {
		current_start = *(--(open_set_start.end()));
		current_goal = *(--(open_set_goal.end()));

		if (current_start == current_goal) {
			break;
		}
		bool leave = false;

		for (auto elem : open_set_start)
		{
			if (f_score_start.at(elem) < f_score_start.at(current_start) && elem != start)
			{
				current_start = elem;
				visited_start[elem] = true;

				if (visited_goal[elem]) {
					std::cout << "Connecting node: " << elem + 1 << "\n";
					current_start = elem;
					current_goal = elem;
					leave = true;
					break;
				}
			}
		}
		if (leave)break;
		for (auto elem : open_set_goal)
		{
			if (f_score_goal.at(elem) < f_score_goal.at(current_goal) && elem != goal)
			{
				current_goal = elem;
				visited_goal[elem] = true;

				if (visited_start[elem]) {
					std::cout << "Connecting node: " << elem + 1 << "\n";
					leave = true;
					current_start = elem;
					current_goal = elem;
					break;
				}
			}
		}
		if (leave)break;

		leave = false;
		for (int i = 0; i < count_elems; i++) {
			if (visited_start[i] && visited_goal[i]) {
				leave = true;
				break;
			}
		}
		if (leave) {

			break;
		}

		if (current_start == current_goal) {
			break;
		}
		open_set_start.extract(current_start);
		open_set_goal.extract(current_goal);

		for (int i = 0; i < count_elems; i++) {
			if (graph[current_start][i])
			{
				int tentative_g_score = g_score_start[current_start] + graph[current_start][i];
				if (tentative_g_score < g_score_start[i]) {
					came_from_start[i] = current_start;
					g_score_start[i] = tentative_g_score;
					f_score_start[i] = tentative_g_score + h(i, came_from_start);
					if (!open_set_start.count(i))
					{
						open_set_start.insert(i);
					}
				}
			}
		}

		for (int i = 0; i < count_elems; i++) {
			if (graph[current_goal][i])
			{
				int tentative_g_score = g_score_goal[current_goal] + graph[current_goal][i];
				if (tentative_g_score < g_score_goal[i]) {
					came_from_goal[i] = current_goal;
					g_score_goal[i] = tentative_g_score;
					f_score_goal[i] = tentative_g_score + h(i, came_from_goal);
					if (!open_set_goal.count(i))
					{
						open_set_goal.insert(i);
					}
				}
			}
		}
	}
	std::vector<int> total_path_start = { current_start };
	while (current_start != start) {
		current_start = came_from_start[current_start];
		total_path_start.push_back(current_start);
	}
	reverse(total_path_start.begin(), total_path_start.end());

	if (current_goal != goal) {
		current_goal = came_from_goal[current_goal];
	}

	std::vector<int> total_path_goal = { current_goal };
	while (current_goal != goal) {
		current_goal = came_from_goal[current_goal];
		total_path_goal.push_back(current_goal);
	}
	if (came_from_start.size() == came_from_goal.size())
	{
		reverse(total_path_goal.begin(), total_path_goal.end());
		reverse(total_path_goal.begin(), total_path_goal.end());
	}

	for (int i = 0; i < total_path_goal.size(); i++)
	{
		total_path_start.push_back(total_path_goal[i]);
	}
	for (int i = 0; i < total_path_start.size() - 1; i++)
	{
		result.push_back(make_pair(total_path_start[i], total_path_start[i + 1]));
	}
}


void Algorithms::DepthFirstSearch() {
	do
	{
		ConsoleInput(1, "Depth-first search");
		result.clear();
		DepthFirstSearchAlgorithm();
		FileOutput("DepthFirstSearch");
		ConsoleOutput();
	} while (OneMoreTime());
}

void Algorithms::BreadthFirstSearch() {
	do {
		ConsoleInput(1, "Breadth-first search");
		result.clear();
		BreadthFirstSearchAlgorithm();
		FileOutput("BreadthFirstSearch");
		ConsoleOutput();
	} while (OneMoreTime());
}

void Algorithms::Prims() {
	do
	{
		ConsoleInput(1, "Prim's algorithm");
		result.clear();
		PrimsAlgorithm();
		FileOutput("Prims");
		ConsoleOutput("pairs");
	} while (OneMoreTime());
}

void Algorithms::Dijkstra() {
	do
	{
		ConsoleInput(1, "Dijkstra algorithm");
		result.clear();
		DijkstraAlgorithm();
		FileOutput("Dijkstra");
		ConsoleOutput("distance");
	} while (OneMoreTime());
}

void Algorithms::AStar() {
	do
	{
		ConsoleInput(2, "A* algorithm");
		result.clear();
		AStarAlgorithm();
		FileOutput("AStar");
		ConsoleOutput();
	} while (OneMoreTime());
}

void Algorithms::FordFulkerson() {
	do
	{
		ConsoleInput(2, "Ford-Fulkerson algorithm");
		result.clear();
		cout << "Max flow: " << FordFulkersonAlgorithm() << "\n\n";
		FileOutput("FordFulkerson");
	} while (OneMoreTime());
}

void Algorithms::DijkstraBidirectional() {
	do
	{
		ConsoleInput(2, "Dijkstra bidirectional algorithm");
		result.clear();
		DijkstraBidirectionalAlgorithm();
		FileOutput("DijkstraBidirectional");
		ConsoleOutput();
	} while (OneMoreTime());
}

void Algorithms::AStarBidirectional() {
	do
	{
		ConsoleInput(2, "A* bidirectional algorithm");
		result.clear();
		AStarBidirectionalAlgorithm();
		FileOutput("AStarBidirectional");
		ConsoleOutput();
	} while (OneMoreTime());
}


void Algorithms::ConsoleOutput(string type) {
	if (type == "path")
	{
		cout << start + 1 << " ";
		for (auto elem : result) {
			cout << elem.second + 1 << " ";
		}
		cout << endl;
	}
	else if (type == "pairs")
	{
		for (auto elem : result) {
			cout << elem.first + 1 << "-" << elem.second + 1 << " ";
		}
		cout << endl;
	}
	else if (type == "distance")
	{
		for (auto elem : result) {
			cout << start + 1 << " -> " << elem.first + 1 << " = " << elem.second + 1 << endl;
		}
	}
}

void Algorithms::FileOutput(string name) {
	ofstream out("command.txt");
	out << "new" << endl;
	out << name << endl;
	for (auto elem : result) {
		out << elem.first << " " << elem.second << " ";
	}
	out.close();
}

void Algorithms::ConsoleInput(int count, string name) {
	if (count == 1)
	{
		cout << name << ", enter node number: ";
		cin >> start;
		start--;
	}
	else if (count == 2)
	{
		cout << name << ", enter first node number: ";
		cin >> start;
		start--;
		cout << "Enter last node number: ";
		cin >> goal;
		goal--;
	}

}

bool Algorithms::OneMoreTime() {
	char y_or_n;
	cout << "One more time? (Y/N): ";
	cin >> y_or_n;
	if (y_or_n == 'y' || y_or_n == 'Y')
	{
		cout << endl;
		return true;
	}
	else
	{
		return false;
	}
}