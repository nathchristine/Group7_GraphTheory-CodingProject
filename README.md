# Group 7 Graph Theory Coding Project

| Name  | NRP |
| ------------- |:-------------:|
| Khairunnisa Rahmahdani Danang      | 5025231081     |
| Nathaniel Christine M S      | 5025231010     |
| Anindya Diany Putri      | 5025231007     |
| Arini Nur Azizah      | 5025231079     |

## Travelling Salesman Problem
### Main Function

```
  int v, e, start;
  cin >> v >> e;
```
* Make a variable for the number of vertices/nodes, edges, and the starting (and ending) point then scan vertices/nodes and edge.

```
vector<pair<int, int> > graph[v];
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      graph[i].push_back({INT_MAX, -1});
    }
  }
```
* Make an adjacency list for the graph and initialize the weight and name.

```
for (int i = 0; i < e; i++) {
    int ver1, ver2, weight, name;
    cin >> name >> ver1 >> ver2 >> weight;

    adj[u-1][v-1].first = min (wt, adj[u-1][v-1].first);
    adj[v-1][u-1].first = min (wt, adj[v-1][u-1].first);
    adj[u-1][v-1].second = name;
    adj[v-1][u-1].second = name;
  }
```
* Read the vertices, weight, name as many as the number of edges from the input and add them to the graph.
* Updates the graph to store the minimum weight for the edge between u and v and assigns the name to the edge.

```
cin >> start;
tsp(start-1, v, graph);
```
* Reads the starting vertex start and calls the tsp function to solve the Traveling Salesman Problem
<br>

### TSP Function
```
void tsp (int start, int v, vector<pair<int, int> > graph[])
```
* This function takes three parameters: the starting vertex start, the number of vertices v, and the adjacency list graph

```
vector<int> vertex; 
  for (int i = 0; i < v; i++) {
    if (i != start) {
      vertex.push_back(i);
    }
  }
```
* Store all vertex, except the starting vertex, in a new vector.


```
int min_cost = INT_MAX;
vector<int> best_route;
```
* Variables to store the smallest cost and its route.

```
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
```
* Generates all possible permutations of the vertices excluding the starting vertex.
* Store the cost and route of each permutation in `current_cost` and `current_route`.
* The inner for loop iterates through the vertices in the current permutation starting from `k` which was set to the starting vertex:
    * Adds the weight of the edge from the current vertex k to the next vertex in the permutation to `current_cost` adn the name of the edge to `current_route`.
    * Update `k` to the next vertex in the permutation.
* After the for loop completes, adds the weight of the edge from the last vertex in the permutation back to the starting vertex to `current_cos`t and adds the name of this edge to `current_route`.
* Check if the current permutation cost less `min_cost` found so far.
    *  If it is, update `min_cost` to `current_cost`, and `best_route` to `current_route`.
* Continue to generate the next permutation of the vertices using the `next_permutation`.

```
cout << "Cost: " << min_cost << endl;
  cout << "Route: ";
  for (int i = 0; i < best_route.size(); i++) {
      cout << best_route[i] << " ";
  }
```
* After all permutation have been evaluated, print the smallest cost and best route.
