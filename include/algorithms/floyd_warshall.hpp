/*
 * Implementation of the Floyd Warshall algorithm - used for calculating the
 * optimial path between two points
 *
 * Shotout to my heuristics and optimization notes - i had a beatiful pseudocode
 * from this algorithm
 */

#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL

#include "utils/concepts/numerical_concepts.hpp"
#include <algorithm>
#include <cstdint>
#include <graph/graph.hpp>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <utils/concepts/node_concepts.hpp>

/*
 * Floyd Warshall algorithm definition
 * @param graph
 * @returns a matrix with the optimal cost for every pair of vertex
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
std::vector<std::vector<W>> warshall(const graph_t<T, W> &g) {
  const int64_t n = g.get_size();

  // initialize the adjacency matrix with infinity
  std::vector<std::vector<W>> matrix(
      n, std::vector<W>(n, std::numeric_limits<W>::max()));

  // map every node to an unique identifier (an integer)
  std::unordered_map<T, int64_t> id_map;
  std::vector<T> nodes = g.get_vertex();
  std::sort(nodes.begin(), nodes.end());
  for (int64_t i = 0; i < n; ++i)
    id_map[nodes[i]] = i;

  // update the matrix with the A -> B direct weights
  for (const auto &node : nodes) {
    int64_t origin = id_map[node];
    std::vector<edge_t<T, W>> edges = g.get_edges(node);

    for (const auto &edge : edges) {
      matrix[origin][id_map[edge._to]] = edge._weight;
    }
  }

  // Floyd Warshall main logic - O(V³) complexity aaaah moment
  for (int64_t k = 0; k < n; ++k) {
    for (int64_t i = 0; i < n; ++i) {
      for (int64_t j = 0; j < n; ++j) {
        W ij = matrix[i][j];
        W ik = matrix[i][k];
        W kj = matrix[k][j];

        // careful with infinity!
        if (ik != std::numeric_limits<W>::max() &&
            kj != std::numeric_limits<W>::max()) {
          matrix[i][j] = std::min(ij, ik + kj);
        }
      }
    }
  }

  return matrix;
}

#endif // !FLOYD_WARSHALL
