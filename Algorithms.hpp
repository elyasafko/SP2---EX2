// Email: elyasafko@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <queue>
#include <climits>
#include <unordered_set>

using namespace std;

namespace ariel
{
        namespace Algorithms
        {
                string isConnected(Graph graph);
                void dfs(Graph graph, size_t vertex, vector<bool> &visited);
                string isBipartite(Graph &graph);
                string shortestPath(Graph graph, size_t src, size_t dest);
                bool isContainsCycle(Graph &graph);
                string negativeCycle(Graph graph);
                int minDistance(vector<int> dist, vector<bool> sptSet, int numNodes);
                bool dfsCycle(Graph &graph, size_t vertex, vector<bool> &visited, vector<int> &path, vector<bool> &visiting);
        }
}

#endif // ALGORITHMS_HPP