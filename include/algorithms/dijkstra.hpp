/*
 * Dijkstra Algorithm
 */

#ifndef DIJKSTRA
#define DIJKSTRA

#include <limits>
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
 * @returns a tuple with the dist and prev maps
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
std::tuple<std::unordered_map<T, W>, std::unordered_map<T, T>>
dijkstra(const graph_t<T, W> &g) {

  std::vector<T> open, result;
  std::unordered_map<T, W> dist;
  std::unordered_map<T, T> prev;

  for (const auto &node : g.get_vertex()) {
    prev[node] = T{};
    dist[node] = std::numeric_limits<W>::infinity();
    open.push_back(node);
  }

  dist[g.get_origin()] = 0;

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
