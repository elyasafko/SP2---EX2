// Email: elyasafko@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <limits.h>
#include <sstream>

using namespace std;

namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> adjacencyMatrix;
        bool direct = false;

    public:
        Graph();
        void loadGraph(vector<vector<int>> matrix, bool directed);
        bool isDirected();
        const bool isDirected() const;
        string printGraph() const;
        int getEdgesCount();
        const int getEdgesCount() const;
        size_t getVerticesCount();
        const size_t getVerticesCount() const;
        bool isWeighted();
        bool haveNegativeWeight();
        vector<int> getNeighbors(size_t vertex);
        int getWeight(size_t src, size_t dest);
        const int getWeight(size_t src, size_t dest) const;
        void setDirect(bool directed);

        // Non-member operator friends
        friend Graph operator+(const Graph &g1, const Graph &g2); // Binary plus
        Graph &operator+=(const Graph &g);
        friend Graph operator+(const Graph &g1);                  // Unary plus
        friend Graph operator-(const Graph &g1, const Graph &g2); // Binary minus
        Graph &operator-=(const Graph &g);
        friend Graph operator-(const Graph &g1); // Unary minus

        // Comparison operators
        friend bool operator>(const Graph &g, const Graph &g2);
        friend bool operator>=(const Graph &g, const Graph &g2);
        friend bool operator<(const Graph &g, const Graph &g2);
        friend bool operator<=(const Graph &g, const Graph &g2);
        friend bool operator==(const Graph &g, const Graph &g2);
        friend bool operator!=(const Graph &g, const Graph &g2);

        // Member operator functions
        Graph &operator++();                  // prefix
        Graph operator++(int dummy_variable); // postfix
        Graph &operator--();                  // prefix
        Graph operator--(int dummy_variable); // postfix
        Graph operator*(int scalar);
        Graph operator/(int scalar);
        Graph &operator*=(int scalar);
        Graph &operator/=(int scalar);
        Graph operator*(const Graph &g) const;

        // Stream insertion operator
        friend ostream &operator<<(ostream &os, const Graph &g); // Stream insertion
    };
}

#endif // GRAPH_HPP
