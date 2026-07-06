/*
 * This script contains the tests used for checking that the graphs are
 * correctly created in runtime execution of the program
 */

#include <stdexcept>
#include <string>
#include <variant>

#include <graph/graph.hpp>
#include <gtest/gtest.h>

using namespace std;

// Inserts a wrong graph name during the graph population process, which will
// lead into an error
TEST(GRAPH_POPULATION, FILE_NOT_FOUND) {
  string GRAPH_NAME = "RANDOM_GRAPH_NAME_1234";
  graph_t<std::variant<string, int>, int> g;

  EXPECT_THROW(g.create_graph(GRAPH_NAME), runtime_error);
}

// Insert nodes in the graph whose id is an integer
TEST(GRAPH_POPULATION, NODES_INT) {
  string GRAPH_NAME = "graph1";
  int NODES_TO_INSERTED =
      10; // this number can be obtained from the graph1.map file - first row
  graph_t<int, int> g;
  g.create_graph(GRAPH_NAME);

  const int GRAPH_SIZE = g.get_size();
  EXPECT_EQ(NODES_TO_INSERTED, GRAPH_SIZE);
}

// Insert nodes in the graph whose id can be either an int or an string
TEST(GRAPH_POPULATION, NODES_VARIANT) {
  string GRAPH_NAME = "graph2";
  int NODES_TO_INSERTED = 10;
  graph_t<variant<string, int>, int> g;
  g.create_graph(GRAPH_NAME);

  const int GRAPH_SIZE = g.get_size();
  EXPECT_EQ(NODES_TO_INSERTED, GRAPH_SIZE);
}

// Insertes nodes in the graph whose id is an int but their weights can be
// either int or float - double
TEST(GRAPH_POPULATION, WEIGHTS_VARIANT) {
  string GRAPH_NAME = "graph3";
  int NODES_TO_INSERTED = 10;
  graph_t<int, double> g;
  g.create_graph(GRAPH_NAME);

  const int GRAPH_SIZE = g.get_size();
  EXPECT_EQ(NODES_TO_INSERTED, GRAPH_SIZE);
}
