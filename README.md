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
* 

## Knight Tour

```
bool isValidMove(int x, int y, int rows, int cols, vector<vector<bool>> &visited) {
    //To ensure the moves are still inclusive of the chessboard area
    return (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y]);
}
```
This function verifies if the knight's move stays within the board boundaries (within the given rows and columns) and ensures the square hasn't been visited yet. If both conditions are met, it returns `true`.

## Chinese Postman Problem
  
  <img width="518" alt="Screenshot 2024-10-07 at 18 36 26" src="https://github.com/user-attachments/assets/2237a712-a1ee-4d43-95ff-e3b29020b87e">

  ### Steps
  * Step 1: At first, we will list all the odd-degree vertices of the graph.
  * Step 2: Now, we will list all the possible pairs of the odd vertices, which means all of them...
  * Step 3: For each odd pairing, find the edge that connects the vertices with the minimum or least weight.
  * Step 4: Then, we will find the pairings so that the sum of the weights of the edges is minimized.
  * Step 5: Now, On the original graph, we will add the edges that have been found in Step 4.
  * Step 6: The length of an optimal Chinese postman or route inspection path is the sum of all the edges of the graph added to the total   found in Step 4.
  * Step 7: Finally, we can find the route corresponding to this minimum sum path can then be easily found.

  1 - 2 = 10 <br>
  1 - 3 = 2 <br>
  1 - 3 = 7 <br>
  2 - 3 = 5 <br>
  
  hence the minimum, or least weight would be 1 - 3 (edge 3), with the cost of 2

  ### Code

  ```
  void dfs(int v) {
    if (mark[v]) return;
    mark[v] = true;
    for (int i = 0; i < n; i++) {
        if (a[v][i] < INF)
            dfs(i);
    }
  }
```

This DFS function checks whether the graph is connected by visiting all reachable nodes from a starting point.This will ensure that the graph is solvable becauuse eulerian circuit or path requires a connected graph

```
int rec(int mask) {
    int &res = mem[mask];
    if (res != -1) return res;
    if (mask == 0) return res = 0;
    res = INF;
    int i1;
    for (i1 = 0; (mask & (1 << i1)) == 0; i1++);
    for (int i2 = i1 + 1; i2 < n; i2++) {
        if (mask & (1 << i2)) {
            int newCost = d[i1][i2] + rec(mask ^ (1 << i1) ^ (1 << i2));
            if (newCost < res) {
                res = newCost;
            }
        }
    }
    return res;
}
```

This function's purpose is to match nodes with odd degrees in pairs to minimize the additional cost required to make all degrees even a necessary condition for an Eulerian path/circuit. As stated in step 6.

```
oid reconstructPath(int u, int v) {
    if (d[u][v] == a[u][v]) {
        for (auto &[cost, edgeId] : edgeMap[{min(u, v), max(u, v)}]) {
            if (cost == a[u][v]) {
                edgeSequence.push_back(edgeId);
                break;
            }
        }
    } else {
        for (int k = 0; k < n; k++) {
            if (d[u][v] == d[u][k] + d[k][v]) {
                reconstructPath(u, k);
                reconstructPath(k, v);
                return;
            }
        }
    }
}
```

Selects the shortest path between nodes u and v into direct edges and keeps track of their ids. This allows the program to determine the exact sequence of edges that make up the path, for the final output of the edges used in the optimal solution.

```
for (int i = 0; i < m; i++) {
    int edgeId, x, y, c;
    cin >> edgeId >> x >> y >> c;
    x--; y--;
    a[x][y] = min(a[x][y], c);
    a[y][x] = min(a[y][x], c);
    sum += c;
    deg[x]++, deg[y]++;
    edgeMap[{min(x, y), max(x, y)}].push_back({c, edgeId});
}
```

This is the user input section, the input will be amount of nodes, amount of edges, edge id, the nodes connected, and cost, lastly the starting and end node of the graph.

```
memcpy(d, a, sizeof a);
for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
}
```

this section computes all-pairs shortest paths using the Floyd-Warshall algorithm

```
cout << res << "\n";
edgeSequence.clear();
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        if ((deg[i] % 2 == 1) && (deg[j] % 2 == 1)) {
            reconstructPath(i, j);
        }
    }
}

cout << "Edges: ";
for (int edge : edgeSequence) {
    cout << edge << " ";
}
cout << "\n";
```

Lastly, the main function

