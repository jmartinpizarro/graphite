/*
 * This script is used for testking the DFS implementation
 */

#include <algorithms/dfs.hpp>
#include <graph/graph.hpp>

#include <gtest/gtest.h>
#include <type_traits>

using namespace std;

// The graph contains only integers
TEST(DFS_SUITE, DFS_OUTPUT_TYPE_1) {
  const string GRAPH_NAME = "graph1";
  graph_t<int, int> g;
  g.create_graph(GRAPH_NAME);

  auto dfs_res = dfs(g);

  static_assert(
      is_same_v<decltype(dfs_res), vector<int>>,
      "With graph1.map file, the DFS nodes ids should be only integers");
}

// The graph contains only integers
TEST(DFS_SUITE, DFS_OUTPUT_TYPE_2) {
  const string GRAPH_NAME = "graph2";
  graph_t<variant<string, int>, int> g;
  g.create_graph(GRAPH_NAME);

  auto dfs_res = dfs(g);

  static_assert(is_same_v<decltype(dfs_res), vector<variant<string, int>>>,
                "With graph2.map file, the DFS nodes ids should be either "
                "strings or ints");
}

// DFS is executed correctly
TEST(DFS_SUITE, DFS_OUTPUT_VALUE) {
  const string GRAPH_NAME = "graph1";
  const vector<int> EXPECTED_OUTPUT = {1, 2, 4, 6, 8, 9, 7, 10, 3, 5};

  graph_t<int, int> g;
  g.create_graph(GRAPH_NAME);
  auto dfs_res = dfs(g);

  ASSERT_EQ(dfs_res, EXPECTED_OUTPUT);
}

// Reverse DFS is executed correctly
TEST(DFS_SUITE, REVERSE_DFS_OUTPUT_VALUE) {
  const string GRAPH_NAME = "graph4";
  const vector<int> EXPECTED_OUTPUT = {3, 2}; // node 1 is not accesible

  graph_t<int, int> g;
  g.create_graph(GRAPH_NAME);

  // for reverse-dfs, the alg starts on node 3
  optional<int> R_NODE = 3;
  auto dfs_res = dfs(g, R_NODE);

  ASSERT_EQ(dfs_res, EXPECTED_OUTPUT);
}
