/*
 * Prim algorithm for finding the Minimal Spanning Tree - MST.
 */

#ifndef PRIM
#define PRIM

#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <graph/graph.hpp>
#include <utils/concepts/node_concepts.hpp>
#include <utils/concepts/numerical_concepts.hpp>

/*
 * Implements the Prim algorithm for the MST.
 * @param graph<T, W> g
 * @returns unordered_map<vertex, edge_t>
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
std::unordered_map<T, edge_t<T, W>> prim(const graph_t<T, W> &g) {
  std::unordered_map<T, edge_t<T, W>> result;
  std::vector<T> visited = {g.get_origin()};

  while (visited.size() != g.get_size()) {
    bool found = false;
    W best_weight{};
    edge_t<T, W> best_edge;
    T best_from;

    for (const auto &node : visited) {
      std::vector<edge_t<T, W>> adjacents = g.get_edges(node);
      for (const auto &adj_edge : adjacents) {
        auto it = std::find(visited.begin(), visited.end(), adj_edge._to);
        if (it == visited.end()) {
          if (!found or adj_edge._weight < best_weight) {
            found = true;
            best_weight = adj_edge._weight;
            best_edge = adj_edge;
            best_from = node;
          }
        }
      }
    }

    if (!found) {
      // graph is not conex
      break;
    }

    result[best_from] = best_edge;
    visited.push_back(best_edge._to);
  }

  return result;
}

#endif // !PRIM
