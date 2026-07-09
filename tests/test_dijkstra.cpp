/* This script constains the tests used for checking that the
 * Dijkstra algorithm is working as it should :)
 */

#include <string>

#include <algorithms/dijkstra.hpp>
#include <graph/graph.hpp>

#include <gtest/gtest.h>

using namespace std;

// Compile-time tests for checking the type of the
// Dijkstra returns value. This is done in order to know if the
// graph changes - by error - a node type during the graph population
// that can lead to error when populating thw dijkstra result
TEST(DIJKSTRA_SUITE, DIJKSTRA_RETURN_TYPES) {
  string GRAPH_NAME = "graph1";
  graph_t<int, int> g;

  g.create_graph(GRAPH_NAME);
  auto res = dijkstra(g);

  static_assert(
      std::is_same_v<decltype(res), std::tuple<std::unordered_map<int, int>,
                                               std::unordered_map<int, int>>>,
      "Dijkstra must return a tuple with (dist, prev) unordered maps");

  ASSERT_EQ(get<0>(res).size(), 10); // dist size == 10, one per node
  ASSERT_EQ(get<1>(res).size(), 10); // prev size == 10, one per node
}

// Check the execution of Dijkstra for a simple graph of three node
TEST(DIJKSTRA_SUITE, DIJKSTRA_OUTPUT_VALUES) {
  string GRAPH_NAME = "graph4";
  graph_t<int, int> g;

  g.create_graph(GRAPH_NAME);
  auto res = dijkstra(g);

  // It has been computed - handmade - that taking the ORIGIN node 1 and the
  // GOAL node 3 takes either 6 or 7 cost. Obviously, it must return 6
  const int goal = g.get_goal();
  ASSERT_EQ(get<0>(res).at(goal), 6);

  // aditionally we know that 1 -> 2 real cost is going to be = 4. Also test it
  ASSERT_EQ(get<0>(res).at(2), 4);
}

// This Dijkstra implementation allows the usage of a parameter for defining the
// goal node
TEST(DIJKSTRA_SUITE, DIJKSTRA_OUTPUT_VALUES_2) {
  string GRAPH_NAME = "graph4";
  graph_t<int, int> g;

  g.create_graph(GRAPH_NAME);
  // now we start from the node 2, with a real cost of 2
  // defining it as an int will leave us non-deductive context because of
  // the fucking compiler. So yeah. You need to define it as an optional
  const optional<int> NEW_ORIGIN_NODE = 2;
  auto res = dijkstra(g, NEW_ORIGIN_NODE);
  const int goal = g.get_goal();
  ASSERT_EQ(get<0>(res).at(goal), 2);
}
