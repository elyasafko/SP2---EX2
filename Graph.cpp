// Email: elyasafko@gmail.com

#include "Graph.hpp"

namespace ariel
{
    Graph::Graph()
    {
        // needed?
    }

    void Graph::loadGraph(vector<vector<int>> graph, bool directed)
    {
        int numRows = graph.size();
        for (const auto &row : graph) // Check if the matrix is square
        {
            if (row.size() != numRows)
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
        for (size_t i = 0; i < numRows; i++) // Check if the graph has a self loop
        {
            if (graph[i][i] != 0)
            {
                throw invalid_argument("Invalid graph: The graph has a self loop.");
            }
        }
        // Load the graph to the object
        adjacencyMatrix = graph;
        direct = directed; // set the direct flag
    }

    string Graph::printGraph() const
    {
        ostringstream oss;
        for (size_t i = 0; i < getVerticesCount(); i++)
        {
            oss << "[";
            for (size_t j = 0; j < getVerticesCount(); j++)
            {
                oss << getWeight(i, j) << (j < getVerticesCount() - 1 ? ", " : "");
            }
            oss << "]" << (i < getVerticesCount() - 1 ? "\n" : "");
        }
        return oss.str();
    }

    int Graph::getEdgesCount()
    {
        // Count the number of edges in the graph
        int count = 0;

        if (direct) // if directed need to check all the matrix
        {
            for (size_t i = 0; i < adjacencyMatrix.size(); i++)
            {
                for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
                {
                    if (adjacencyMatrix[i][j] != 0)
                    {
                        count++;
                    }
                }
            }
        }
        else // if not directed need to check only the upper triangle of the matrix
        {
            for (size_t i = 0; i < adjacencyMatrix.size(); i++)
            {
                for (size_t j = i; j < adjacencyMatrix[i].size(); j++)
                {
                    if (adjacencyMatrix[i][j] != 0)
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }
    const int Graph::getEdgesCount() const
    {
        // Count the number of edges in the graph
        int count = 0;

        if (direct) // if directed need to check all the matrix
        {
            for (size_t i = 0; i < adjacencyMatrix.size(); i++)
            {
                for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
                {
                    if (adjacencyMatrix[i][j] != 0)
                    {
                        count++;
                    }
                }
            }
        }
        else // if not directed need to check only the upper triangle of the matrix
        {
            for (size_t i = 0; i < adjacencyMatrix.size(); i++)
            {
                for (size_t j = i; j < adjacencyMatrix[i].size(); j++)
                {
                    if (adjacencyMatrix[i][j] != 0)
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }

    size_t Graph::getVerticesCount()
    {
        // Return the number of vertices in the graph
        return adjacencyMatrix.size();
    }
    const size_t Graph::getVerticesCount() const
    {
        // Return the number of vertices in the graph
        return adjacencyMatrix.size();
    }

    bool Graph::isWeighted()
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                if (adjacencyMatrix[i][j] > 1 || adjacencyMatrix[i][j] < -1)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool Graph::haveNegativeWeight()
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                if (adjacencyMatrix[i][j] < 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    vector<int> Graph::getNeighbors(size_t vertex)
    {
        vector<int> neighbors;
        for (size_t i = 0; i < adjacencyMatrix[vertex].size(); i++)
        {
            if (adjacencyMatrix[vertex][i] != 0)
            {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    bool Graph::isDirected()
    {
        return direct;
    }
    const bool Graph::isDirected() const
    {
        return direct;
    }

    int Graph::getWeight(size_t src, size_t dest)
    {
        if (src >= adjacencyMatrix.size() || dest >= adjacencyMatrix[src].size())
        {
            // Handle out-of-bounds access
            return INT_MAX;
        }
        return adjacencyMatrix[src][dest];
    }
    const int Graph::getWeight(size_t src, size_t dest) const
    {
        if (src >= adjacencyMatrix.size() || dest >= adjacencyMatrix[src].size())
        {
            // Handle out-of-bounds access
            return INT_MAX;
        }
        return adjacencyMatrix[src][dest];
    }

    void Graph::setDirect(bool directed)
    {
        direct = directed;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = i; j < adjacencyMatrix[i].size(); j++)
            {
                if (!directed) // if not directed need to make the matrix symmetric
                {
                    if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
                    {
                        if (adjacencyMatrix[i][j] == 0)
                        {
                            adjacencyMatrix[i][j] = adjacencyMatrix[j][i];
                        }
                        else if (adjacencyMatrix[j][i] == 0)
                        {
                            adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                        }
                        else
                        {
                            throw invalid_argument("Invalid graph: The graph is not symmetric.");
                        }
                    }
                }
            }
        }
    }

    // operator overloading

    Graph operator+(const Graph &g1, const Graph &g2) // Binary plus
    {
        if (g1.getVerticesCount() != g2.getVerticesCount()) // Check if the graphs have the same number of vertices
        {
            throw invalid_argument("Invalid graph: The graphs must have the same number of vertices.");
        }
        vector<vector<int>> newGraph;                      // Create a new graph
        for (size_t i = 0; i < g1.getVerticesCount(); i++) // Add the weights of the two graphs
        {
            vector<int> row;                                   // Create a new row
            for (size_t j = 0; j < g1.getVerticesCount(); j++) // Add the weights of the two graphs
            {
                row.push_back(g1.getWeight(i, j) + g2.getWeight(i, j)); // Add the weights of the two graphs
            }
            newGraph.push_back(row); // Add the row to the new graph
        }
        Graph g;
        g.loadGraph(newGraph, g1.isDirected()); // Load the new graph to the object
        return g;
    }

    Graph &Graph::operator+=(const Graph &g) // Add the weights of the two graphs
    {
        if (g.getVerticesCount() != getVerticesCount()) // Check if the graphs have the same number of vertices
        {
            throw invalid_argument("Invalid graph: The graphs must have the same number of vertices.");
        }
        for (size_t i = 0; i < g.getVerticesCount(); i++)
        {
            for (size_t j = 0; j < g.getVerticesCount(); j++)
            {
                adjacencyMatrix[i][j] += g.getWeight(i, j);
            }
        }
        return *this;
    }

    Graph operator+(const Graph &g1) // Unary plus
    {
        return g1;
    }

    Graph operator-(const Graph &g1, const Graph &g2) // Binary minus
    {
        if (g1.getVerticesCount() != g2.getVerticesCount())
        {
            throw invalid_argument("Invalid graph: The graphs must have the same number of vertices.");
        }
        vector<vector<int>> newGraph;
        for (size_t i = 0; i < g1.getVerticesCount(); i++)
        {
            vector<int> row;
            for (size_t j = 0; j < g1.getVerticesCount(); j++)
            {
                row.push_back(g1.getWeight(i, j) - g2.getWeight(i, j));
            }
            newGraph.push_back(row);
        }
        Graph g;
        g.loadGraph(newGraph, g1.isDirected());
        return g;
    }

    Graph &Graph::operator-=(const Graph &g) // Subtract the weights of the two graphs
    {
        if (g.getVerticesCount() != getVerticesCount())
        {
            throw invalid_argument("Invalid graph: The graphs must have the same number of vertices.");
        }
        for (size_t i = 0; i < g.getVerticesCount(); i++)
        {
            for (size_t j = 0; j < g.getVerticesCount(); j++)
            {
                adjacencyMatrix[i][j] -= g.getWeight(i, j);
            }
        }
        return *this;
    }

    Graph operator-(const Graph &g1) // Unary minus
    {
        Graph g = g1;
        return g * -1;
    }

    bool operator>(const Graph &g1, const Graph &g2)
    {

        size_t g1Size = g1.getVerticesCount();
        size_t g2Size = g2.getVerticesCount();
        size_t limit = g2Size - g1Size + 1;

        if (g1Size > g2Size) // Check if the first graph has more vertices than the second graph
        {
            return false;
        }

        for (size_t i = 0; i < limit; i++) // Check if the first graph is inside the second graph
        {
            bool flag = true;
            for (size_t j = 0; j < g1Size; j++)
            {
                for (size_t k = 0; k < g1Size; k++)
                {
                    if (g1.getWeight(j, k) != g2.getWeight(j + i, k + i))
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                {
                    break;
                }
            }
            if (flag)
                return true;
        }

        if (g1.getEdgesCount() > g2.getEdgesCount()) // Check if the first graph has more edges than the second graph
        {
            return true;
        }

        if (g1.getVerticesCount() > g2.getVerticesCount()) // Check if the first graph has more vertices than the second graph
        {
            return true;
        }

        return false;
    }

    bool operator>=(const Graph &g1, const Graph &g2)
    {
        if (g1 > g2 || g1 == g2)
        {
            return true;
        }
        return false;
    }

    bool operator<(const Graph &g1, const Graph &g2)
    {
        return g2 > g1;
    }

    bool operator<=(const Graph &g1, const Graph &g2)
    {
        if (g1 < g2 || g1 == g2)
        {
            return true;
        }
        return false;
    }

    bool operator==(const Graph &g1, const Graph &g2) // Check if the two graphs are equal
    {
        if (g1.getVerticesCount() != g2.getVerticesCount())
        {
            printf("The number of vertices in the two graphs is different\n");
            return false;
        }
        for (size_t i = 0; i < g1.getVerticesCount(); i++)
        {
            for (size_t j = 0; j < g1.getVerticesCount(); j++)
            {
                if (g1.getWeight(i, j) != g2.getWeight(i, j))
                {
                    printf("The weight of the edge (%zu, %zu) is different\n", i, j);
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Graph &g1, const Graph &g2) // Check if the two graphs are not equal
    {
        return !(g1 == g2);
    }

    Graph &Graph::operator++() // Prefix increment operator (++g)
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                if (i != j)
                    adjacencyMatrix[i][j]++;
            }
        }
        return *this;
    }

    Graph Graph::operator++(int dummy_variable) // Postfix increment operator (g++)
    {
        Graph temp = *this; // Save the current state
        ++(*this);          // Use the prefix increment to modify the current object
        return temp;        // Return the saved state
    }

    Graph &Graph::operator--() // Prefix increment operator (++g)
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                if (i != j)
                    adjacencyMatrix[i][j]--;
            }
        }
        return *this;
    }

    Graph Graph::operator--(int dummy_variable) // Postfix increment operator (g++)
    {
        Graph temp = *this; // Save the current state
        --(*this);          // Use the prefix increment to modify the current object
        return temp;        // Return the saved state
    }

    Graph Graph::operator*(int scalar) // Multiply the weights of the graph by a scalar
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    Graph Graph::operator/(int scalar) // Divide the weights of the graph by a scalar
    {
        if (scalar == 0)
        {
            throw invalid_argument("Invalid scalar: The scalar cannot be zero.");
        }
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] /= scalar;
            }
        }
        return *this;
    }

    Graph &Graph::operator*=(int scalar) // Multiply the weights of the graph by a scalar
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    Graph &Graph::operator/=(int scalar) // Divide the weights of the graph by a scalar
    {
        if (scalar == 0)
        {
            throw invalid_argument("Invalid scalar: The scalar cannot be zero.");
        }
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] /= scalar;
            }
        }
        return *this;
    }

    Graph Graph::operator*(const Graph &g) const // Multiply the weights of the two graphs
    {
        if (adjacencyMatrix[0].size() != g.getVerticesCount())
        {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }
        vector<vector<int>> newGraph;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            vector<int> row;
            for (size_t j = 0; j < g.getVerticesCount(); j++)
            {
                int sum = 0;
                for (size_t k = 0; k < adjacencyMatrix[i].size(); k++)
                {
                    sum += adjacencyMatrix[i][k] * g.getWeight(k, j);
                }
                row.push_back(sum);
            }
            newGraph.push_back(row);
        }
        for (size_t i = 0; i < newGraph.size(); i++)
        {
            newGraph[i][i] = 0;
        }
        Graph newG;
        newG.loadGraph(newGraph, direct);
        return newG;
    }

    ostream &operator<<(ostream &os, const Graph &g)
    {
        os << g.printGraph() << endl
           << endl;
        return os;
    }

}
