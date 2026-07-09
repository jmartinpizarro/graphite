/*
 * Dijkstra Algorithm
 */

#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once

#include <limits>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <graph/graph.hpp>
#include <utils/concepts/node_concepts.hpp>
#include <utils/concepts/numerical_concepts.hpp>

/*
 * Dijkstra Algorithm for obtaining the minimum cost path from
 * an origin node
 * @param g Graph
 * @param T node. It is possible that it might be needed to execute the
 * algorithm from a different origin node wrt the graph origin node
 * @returns a tuple with the dist and prev maps
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
std::tuple<std::unordered_map<T, W>, std::unordered_map<T, T>>
dijkstra(const graph_t<T, W> &g,
         const std::optional<T> origin_node = std::nullopt) {

  std::vector<T> open, result;
  std::unordered_map<T, W> dist;
  std::unordered_map<T, T> prev;

  for (const auto &node : g.get_vertex()) {
    prev[node] = T{};
    // initially i used infinity() but it is only useful for doubles... For ints
    // and numbers with less precission, T{} = 0
    dist[node] = std::numeric_limits<W>::max();
    open.push_back(node);
  }

  T origin;
  if (origin_node.has_value()) {
    origin = origin_node.value();
  } else {
    origin = g.get_origin();
  }

  dist[origin] = 0;

  while (open.size() != 0) {

    // TODO: migrate this part of the code to a priority queue for optimality...
    // for all nodes in open, select the one with the minimum cost in the dist
    // map.
    T min_node = open[0];
    W min_value = dist[min_node];

    for (const auto &node : open) {
      if (dist[node] < min_value) {
        min_node = node;
        min_value = dist[node];
      }
    }

    // if there are non-recheable nodes, an error will leak in the next lines.
    // max() + X = overflow. So, if we arrive to a point where we are expanding
    // nodes whose min_value is infinity, we have to pass them
    if (min_value == std::numeric_limits<W>::max()) {
      break;
    }

    auto it = std::ranges::find(open, min_node);
    if (it != open.end()) {
      open.erase(it);
    }

    std::vector<edge_t<T, W>> edges = g.get_edges(min_node);
    for (const auto &[_to, _weight] : edges) {
      W alt = dist[min_node] + _weight;
      if (alt < dist[_to]) {
        dist[_to] = alt;
        prev[_to] = min_node;
      }
    }
  }

  return {dist, prev};
}

#endif // !DIJKSTRA
