// Email: elyasafko@gmail.com

#include "Algorithms.hpp"

namespace ariel
{
    namespace Algorithms
    {
        string isConnected(Graph graph)
        {
            // Get the number of vertices in the graph
            size_t numVertices = graph.getVerticesCount();

            if (!graph.isDirected())
            {
                // Create a visited array to keep track of visited vertices
                vector<bool> visited(numVertices, false);

                // Perform DFS starting from the first vertex
                dfs(graph, 0, visited);

                // Check if all vertices have been visited
                for (bool v : visited)
                {
                    if (!v)
                        return "The graph is not connected.";
                }

                return "The graph is connected.";
            }
            else
            {
                // Create a visited array to keep track of visited vertices
                vector<bool> visited(numVertices, false);

                // Perform DFS on all vertices
                for (size_t i = 0; i < numVertices; i++)
                {
                    dfs(graph, i, visited);
                    for (bool v : visited)
                    {
                        if (!v)
                        {
                            // maybe its weakly connected
                            graph.setDirect(false);
                            if (isConnected(graph) == "The graph is not connected.")
                            {
                                return "The graph is not connected.";
                            }
                            return "The graph is weakly connected.";
                        }
                    }
                    visited.assign(numVertices, false);
                }
                return "The graph is strongly connected.";
            }
        }

        void dfs(Graph graph, size_t vertex, vector<bool> &visited)
        {
            // Mark the current vertex as visited
            visited[vertex] = true;

            // Get the neighbors of the current vertex
            vector<int> neighbors = graph.getNeighbors(vertex);

            // Recursively visit all unvisited neighbors
            for (int neighbor : neighbors)
            {
                if (!visited[(size_t)neighbor])
                {
                    dfs(graph, (size_t)neighbor, visited);
                }
            }
        }

        string isBipartite(Graph &graph)
        {
            if (graph.getVerticesCount() == 0)
            {
                return "The graph is bipartite: A={}, B={}";
            }
            // Perform BFS starting from the first vertex
            queue<int> q;                                    // Queue to store vertices
            vector<int> color(graph.getVerticesCount(), -1); // Color array to mark the vertices

            // Vectors to store the two groups
            vector<int> groupA, groupB;
            color[0] = 0;
            groupA.push_back(0); // Start vertex 0 in group A
            q.push(0);

            while (!q.empty())
            {
                size_t u = (size_t)q.front();
                q.pop();

                // Fetch neighbors of vertex u
                vector<int> neighbors = graph.getNeighbors(u);
                for (int neighbor : neighbors) // Iterate over the neighbors of the current vertex
                {
                    if (color[(size_t)neighbor] == -1) // If the neighbor has not been visited
                    {
                        // Assign the opposite color to the neighbor
                        color[(size_t)neighbor] = 1 - color[u];
                        q.push(neighbor); // Add the neighbor to the queue

                        // Add the vertex to the appropriate group
                        if (color[(size_t)neighbor] == 0)
                            groupA.push_back(neighbor);
                        else
                            groupB.push_back(neighbor);
                    }
                    else if (color[(size_t)neighbor] == color[u]) // If the neighbor has the same color as the current vertex
                    {
                        return "The graph is not bipartite";
                    }
                }
            }

            // Build the output string showing the two groups
            string result = "The graph is bipartite: A={";
            for (size_t i = 0; i < groupA.size(); ++i)
                result += to_string(groupA[i]) + (i < groupA.size() - 1 ? ", " : "}, B={");
            for (size_t i = 0; i < groupB.size(); ++i)
                result += to_string(groupB[i]) + (i < groupB.size() - 1 ? ", " : "}");

            return result;
        }

        string shortestPath(Graph graph, size_t src, size_t dest)
        {
            if (src == dest)
            {
                return to_string(src);
            }
            size_t numNodes = graph.getVerticesCount();
            if (numNodes == 0)
            {
                return "";
            }
            if (src < 0 || src >= numNodes || dest < 0 || dest >= numNodes)
            {
                return "";
            }

            if (graph.haveNegativeWeight() && graph.isWeighted()) // Bellman-Ford algorithm
            {
                // cout << "Bellman-Ford algorithm" << endl;
                if (negativeCycle(graph) == "The graph contains a negative cycle.") // Check for negative cycles
                {
                    return "The graph contains a negative cycle.";
                }
                vector<int> dist(numNodes, INT_MAX);
                dist[src] = 0;

                for (int i = 0; i < numNodes - 1; i++) // Relax all edges V-1 times
                {
                    for (size_t u = 0; u < numNodes; u++)
                    {
                        vector<int> neighbors = graph.getNeighbors(u);
                        for (int neighbor : neighbors)
                        {
                            int weight = graph.getWeight(u, (size_t)neighbor);
                            if (dist[u] != INT_MAX && dist[u] + weight < dist[(size_t)neighbor]) // Relax the edge
                            {
                                dist[(size_t)neighbor] = dist[u] + weight;
                            }
                        }
                    }
                }

                for (size_t u = 0; u < numNodes; u++) // Check for negative cycles - if any distance can be further relaxed, then there is a negative cycle
                {
                    vector<int> neighbors = graph.getNeighbors(u);
                    for (int neighbor : neighbors)
                    {
                        int weight = graph.getWeight(u, (size_t)neighbor);
                        if (dist[u] != INT_MAX && dist[u] + weight < dist[(size_t)neighbor])
                        {
                            return "The graph contains a negative cycle.";
                        }
                    }
                }

                if (dist[dest] == INT_MAX)
                {
                    return "There is no path from " + to_string(src) + " to " + to_string(dest);
                }
                else
                {
                    string answer = "";
                    queue<int> q;
                    size_t current = dest;
                    while (current != src)
                    {
                        q.push(current); // Push the current node into the queue
                        vector<int> neighbors = graph.getNeighbors(current);
                        for (int neighbor : neighbors)
                        {
                            if (dist[(size_t)neighbor] + graph.getWeight(current, (size_t)neighbor) == dist[current])
                            {
                                current = (size_t)neighbor;
                                break;
                            }
                        }
                    }
                    q.push(src); // Push the source node into the queue
                    while (!q.empty())
                    {
                        answer = to_string(q.front()) + "->" + answer;
                        q.pop();
                    }
                    return answer;
                }
            }
            else if (graph.isWeighted()) // Dijkstra's algorithm
            {
                // cout << "Dijkstra's algorithm" << endl;
                vector<int> dist(numNodes, INT_MAX);
                vector<int> pred(numNodes, -1); // To keep track of the path

                // Create a priority queue to store vertices that are being preprocessed
                priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

                // Distance of source vertex from itself is always 0
                dist[src] = 0;

                // Insert source itself in priority queue and initialize its distance as 0
                pq.push(make_pair(0, src));

                while (!pq.empty())
                {
                    size_t u = (size_t)pq.top().second;
                    pq.pop();

                    // If the distance to u is finalized, skip processing
                    if (dist[u] != pq.top().first)
                        continue;

                    // Iterate over all adjacent vertices
                    for (size_t v = 0; v < numNodes; ++v)
                    {
                        int weight = graph.getWeight(u, v);
                        // Skip processing if no edge exists
                        if (weight == 0)
                            continue;

                        // Check for safer weight addition
                        if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
                        {
                            dist[v] = dist[u] + weight;
                            pq.push(make_pair(dist[v], v));
                            pred[v] = u;
                        }
                    }
                }

                if (dist[dest] == INT_MAX)
                {
                    return "There is no path from " + to_string(src) + " to " + to_string(dest);
                }
                else
                {
                    string path = to_string(dest);
                    int current = pred[dest];

                    // Build the path string from destination to source
                    while (current != -1)
                    {
                        path = to_string(current) + "->" + path;
                        if (current == src)
                            break;                       // Once we reach the source, stop.
                        current = pred[(size_t)current]; // Move to the predecessor
                    }

                    // Print the constructed path
                    return path;
                }
            }
            else // bfs
            {
                // cout << "BFS algorithm" << endl;
                vector<int> dist(graph.getVerticesCount(), INT_MAX); // To keep track of the distance
                vector<int> pred(graph.getVerticesCount(), -1);      // To keep track of the path
                dist[src] = 0;
                queue<int> q;
                q.push(src);
                while (!q.empty()) // Perform BFS
                {
                    size_t u = (size_t)q.front();
                    q.pop();
                    vector<int> neighbors = graph.getNeighbors(u);
                    for (int neighbor : neighbors) // Iterate over the neighbors of the current vertex
                    {
                        if (dist[(size_t)neighbor] == INT_MAX) // If the neighbor has not been visited
                        {
                            dist[(size_t)neighbor] = dist[u] + 1;
                            q.push((size_t)neighbor);
                            pred[(size_t)neighbor] = u; // Keep track of the path
                        }
                    }
                }

                if (dist[dest] == INT_MAX) // If the destination vertex has not been reached
                {
                    return "There is no path from " + to_string(src) + " to " + to_string(dest);
                }
                else
                {
                    int current = dest;
                    string answer = to_string(current);
                    current = pred[(size_t)current]; // Move to the predecessor
                    while (current != src)
                    {
                        answer = to_string(current) + "->" + answer;
                        current = pred[(size_t)current]; // Move to the predecessor
                    }
                    answer = to_string(src) + "->" + answer;
                    return answer;
                }
            }
        }

        int minDistance(vector<int> dist, vector<bool> sptSet, int numNodes)
        { // A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
            int min = INT_MAX, min_index;

            for (size_t v = 0; v < numNodes; v++)
                if (sptSet[v] == false && dist[v] <= min)
                    min = dist[v], min_index = v;

            return min_index;
        }

        bool dfsCycle(Graph &graph, size_t vertex, vector<bool> &visited, vector<int> &path, vector<bool> &visiting, int parent)
        {
            visited[vertex] = true;
            visiting[vertex] = true; // Mark the current vertex as visiting
            path.push_back(vertex);

            vector<int> neighbors = graph.getNeighbors(vertex);
            for (int neighbor : neighbors)
            {
                if (!visited[(size_t)neighbor])
                {
                    if (dfsCycle(graph, (size_t)neighbor, visited, path, visiting, vertex))
                    {
                        return true;
                    }
                }
                else if (visiting[(size_t)neighbor] && neighbor != parent)
                { // Check if not revisiting the parent in an undirected graph
                    return true;
                }
            }

            visiting[(size_t)vertex] = false; // Unmark the current vertex
            path.pop_back();                  // Remove the current vertex from the path
            return false;
        }

        bool isContainsCycle(Graph &graph)
        {
            size_t numVertices = graph.getVerticesCount();
            vector<bool> visited(numVertices, false);
            vector<int> path;
            bool hasCycle = false;

            for (int i = 0; i < numVertices; i++)
            {
                if (!visited[(size_t)i])
                {
                    vector<bool> visiting(numVertices, false); // Reset for each connected component
                    if (dfsCycle(graph, (size_t)i, visited, path, visiting, -1))
                    { // Pass -1 as the parent of the root node
                        hasCycle = true;
                        break;
                    }
                }
            }

            if (hasCycle)
            {
                string cyclePath = "";
                for (int vertex : path)
                {
                    cyclePath += to_string(vertex) + "->";
                }
                cyclePath.pop_back();
                cyclePath.pop_back();                   // Remove the last " -> "
                cyclePath += "->" + to_string(path[0]); // Optionally close the cycle visually
                cout << "The graph contains a cycle: " + cyclePath << endl;
                return true;
            }
            else
            {
                cout << "The graph does not contain a cycle." << endl;
                return false;
            }
        }

        string negativeCycle(Graph graph)
        {
            size_t V = graph.getVerticesCount();
            if (V == 0)
                return "The graph is empty.";

            int E = graph.getEdgesCount();
            if (E == 0)
                return "The graph does not contain any edges.";

            if (!graph.haveNegativeWeight())
                return "The graph does not contain any negative weights.";

            vector<int> dist(V, INT_MAX);
            dist[0] = 0; // Starting vertex

            // Relax all edges V-1 times
            for (int i = 0; i < V - 1; i++)
            {
                for (size_t u = 0; u < V; u++)
                {
                    for (size_t v = 0; v < V; v++)
                    {
                        int weight = graph.getWeight(u, v);
                        if (dist[u] != INT_MAX && (weight != 0 || u == v) && dist[u] + weight < dist[v])
                        {
                            dist[v] = dist[u] + weight;
                        }
                    }
                }
            }

            // Check for negative weight cycle
            for (size_t u = 0; u < V; u++)
            {
                for (size_t v = 0; v < V; v++)
                {
                    int weight = graph.getWeight(u, v);
                    if (dist[u] != INT_MAX && (weight != 0 || u == v) && dist[u] + weight < dist[v])
                    {
                        return "The graph contains a negative cycle.";
                    }
                }
            }

            return "The graph does not contain a negative cycle.";
        }
    }
}