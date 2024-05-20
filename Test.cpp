#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using namespace ariel;

// Addition-related tests
TEST_CASE("Test graph addition") // g1 = g2 + g3
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    g3 = g1 + g1;
    CHECK(g3.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");

    Graph g4;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph2, false);
    Graph g5 = g1 + g4;
    CHECK(g5.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    Graph g6;
    vector<vector<int>> graph3 = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g6.loadGraph(graph3, false);
    Graph g7 = g1 + g6;
    CHECK(g7.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test graph += operator") // g1 += g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    g1 += g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph addition of different sizes")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1, false);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, false);
    CHECK_THROWS(g1 + g2);
}

TEST_CASE("Test graph addition of weighted and unweighted graphs")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, false);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    g2.loadGraph(graph2, false);
    ariel::Graph g3 = g1 + g2;
    CHECK(g3.printGraph() == "[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]");
}

TEST_CASE("Test operations with single vertex graphs")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {{0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0]");
    g2 = g1 * g1;
    CHECK(g2.printGraph() == "[0]");
}

TEST_CASE("Test operations with disconnected graphs")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 + g1;
    vector<vector<int>> expectedGraph = {
        {0, 2, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 2, 0}};
    CHECK(g2.printGraph() == "[0, 2, 0, 0]\n[2, 0, 0, 0]\n[0, 0, 0, 2]\n[0, 0, 2, 0]");
}

TEST_CASE("Test graph self-addition and self-subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    ariel::Graph g3 = g1 - g1;
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

// Multiplication-related tests
TEST_CASE("Test graph multiplication") // g1 = g2 * g3
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {3, 0, 1, 0},
        {0, 0, 0, 4},
        {0, 0, 2, 0}};
    g5.loadGraph(graph2, false);
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 3, 0},
        {1, 0, 1, 2},
        {1, 1, 0, 1},
        {4, 0, 1, 0}};
    g6.loadGraph(graph3, false);
    ariel::Graph g7 = g5 * g6;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 1, 4},
        {1, 0, 9, 1},
        {16, 0, 0, 0},
        {2, 2, 0, 0}};
    CHECK(g7.printGraph() == "[0, 2, 1, 4]\n[1, 0, 9, 1]\n[16, 0, 0, 0]\n[2, 2, 0, 0]");
}

TEST_CASE("Test graph multiplication by scalar") // g1 = g2 * 2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    g2 *= 2;
    CHECK(g2.printGraph() == "[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]");

    ariel::Graph g3 = g1 * 0;
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test graph multiplication of different sizes")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1, false);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, false);
    CHECK_THROWS(g1 * g2);
}

TEST_CASE("Test graph scalar multiplication by zero")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 * 0;
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test operations with a complete graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]");
}

// Invalid operations
TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2, false);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3, false);
    CHECK_THROWS(g1 + g6);

    // Subtraction of two graphs with different dimensions
    ariel::Graph g7;
    vector<vector<int>> graph4 = {
        {0, 2, 0, 0},
        {2, 0, 2, 0},
        {0, 2, 0, 2},
        {0, 0, 2, 0}};
    g7.loadGraph(graph4, false);
    CHECK_THROWS(g1 - g7);
}

TEST_CASE("Test invalid graph arithmetic operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1, false);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2, false);
    CHECK_THROWS(g1 * g2);
}

// Increment and decrement operators
TEST_CASE("Test graph increment and decrement operators") // g1 = g2++
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3 = g2++;
    CHECK(g3.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    ariel::Graph g4 = g2--;
    CHECK(g4.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    CHECK(g2.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
}

TEST_CASE("Test graph ++g --g operators") // g1 = ++g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3 = ++g2;
    CHECK(g3.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    CHECK(g2.printGraph() == "[0, 2, 2]\n[2, 0, 3]\n[2, 3, 0]");
    ariel::Graph g4 = --g2;
    CHECK(g4.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
    CHECK(g2.printGraph() == "[0, 1, 1]\n[1, 0, 2]\n[1, 2, 0]");
}

// Scalar operations
TEST_CASE("Test graph division by scalar") // g1 = g2 / 2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 / 2;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    g2 /= 2;
    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
    CHECK_THROWS(g1 / 0);
    CHECK_THROWS(g2 /= 0);
}

TEST_CASE("Test graph division by negative scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 / -2;
    CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
}

TEST_CASE("Test operations with graphs containing negative weights")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
    ariel::Graph g3 = g1 * 2;
    CHECK(g3.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
}

TEST_CASE("Test operations with sparse graphs")
{
    ariel::Graph g1;
    vector<vector<int>> sparseGraph = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    g1.loadGraph(sparseGraph, false);
    ariel::Graph g2 = g1 + g1;
    CHECK(g2.printGraph() == "[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]");
}

// Unary operations
TEST_CASE("Test graph + unary") // g1 = +g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test graph - unary") // g1 = -g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = -g1;
    CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
}

// Comparison operations
TEST_CASE("Test graph comparison operators") // compare g1 and g2
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3;
    vector<vector<int>> weightedGraph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g3.loadGraph(weightedGraph2, false);
    CHECK(g1 == g1);
    CHECK(g2 == g3);
    CHECK(g1 != g2);
    CHECK(g1 < g2);
    CHECK(g1 <= g2);
    CHECK(g2 > g1);
    CHECK(g2 >= g1);
}

TEST_CASE("Test graph equality with different structures but same values")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, false);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, true);
    CHECK(g1 == g2);
}

// Miscellaneous
TEST_CASE("Test graph with directed edges")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g1.loadGraph(graph, true);
    CHECK(g1.printGraph() == "[0, 1, 0]\n[0, 0, 1]\n[0, 0, 0]");
}

TEST_CASE("Test graph with varying edge weights")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, -1},
        {1, 0, 2},
        {-1, 2, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 2, -2]\n[2, 0, 4]\n[-2, 4, 0]");
    g2 /= 2;
    CHECK(g2.printGraph() == "[0, 1, -1]\n[1, 0, 2]\n[-1, 2, 0]");
}

TEST_CASE("Test operations with weighted edges")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 3, 0},
        {3, 0, 4},
        {0, 4, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2 = g1 * 2;
    CHECK(g2.printGraph() == "[0, 6, 0]\n[6, 0, 8]\n[0, 8, 0]");
    g2 /= 2;
    CHECK(g2.printGraph() == "[0, 3, 0]\n[3, 0, 4]\n[0, 4, 0]");
}
