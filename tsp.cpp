#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

void tsp (int start, int v, vector<pair<int, int> > graph[]) {
  vector<int> vertex; 
  for (int i = 0; i < v; i++) {
    if (i != start) {
      vertex.push_back(i);
    }
  }

  int min_cost = INT_MAX;
  vector<int> best_route;

  do {
      int current_cost = 0;
      vector<int> current_route;

      int k = start;

      for (int i = 0; i < vertex.size(); i++) {
        current_cost += graph[k][vertex[i]].first;
        current_route.push_back(graph[k][vertex[i]].second);
        k = vertex[i];
      }

      current_cost += graph[k][start].first;
      current_route.push_back(graph[k][start].second);

      if (current_cost < min_cost) {
          min_cost = current_cost;
          best_route = current_route;
      }
  } while (next_permutation(vertex.begin(), vertex.end()));

  cout << "Cost: " << min_cost << endl;
  cout << "Route: ";
  for (int i = 0; i < best_route.size(); i++) {
      cout << best_route[i] << " ";
  }
}

int main()
{
  int v, e, start;
  cin >> v >> e;

	vector<pair<int, int> > graph[v];
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      graph[i].push_back({INT_MAX, -1});
    }
  }
  
  for (int i = 0; i < e; i++) {
    int ver1, ver2, weight, name;
    cin >> name >> ver1 >> ver2 >> weight;

    graph[ver1-1][ver2-1].first = min (weight, graph[ver1-1][ver2-1].first);
    graph[ver2-1][ver1-1].first = min (weight, graph[ver2-1][ver1-1].first);
    graph[ver1-1][ver2-1].second = name;
    graph[ver2-1][ver1-1].second = name;
  }

  cin >> start;
  tsp(start-1, v, graph);
}
