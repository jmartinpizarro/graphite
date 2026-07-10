/*
 * Depth First Search - DFS algorithm
 */

#ifndef DFS
#define DFS

#pragma once

#include <deque>
#include <optional>
#include <ranges>
#include <unordered_map>
#include <vector>

#include <graph/graph.hpp>
#include <utils/concepts/node_concepts.hpp>
#include <utils/concepts/numerical_concepts.hpp>

template <graphite_concepts::is_node_type NodeType,
          graphite_concepts::is_numeric NumericalWeight>
/*
 * DFS algorithm
 * @param graph
 * @returns vector with the node path
 */
std::vector<NodeType> dfs(const graph_t<NodeType, NumericalWeight> &g,
                          std::optional<NodeType> origin = std::nullopt) {

  std::vector<NodeType> results;

  // create the visited dict for tracking the visited nodes
  std::vector<NodeType> t_vertex = g.get_vertex();
  std::deque<NodeType> open;
  std::unordered_map<NodeType, bool> visited;

  for (const NodeType &node : t_vertex) {
    visited.insert({node, false});
  }

  // when starting the algorithm, an origin node must be chosen. By default, no
  // origin node is given. In that case, the graph will retrieve the origin node
  // saved in its own instance
  NodeType origin_node;
  if (origin.has_value()) {
    origin_node = origin.value();
  } else {
    origin_node = g.get_origin();
  }

  open.push_back(origin_node);

  while (open.size() != 0) {

    // process the node
    NodeType current = open.front();
    open.pop_front();
    if (visited.at(current) == true) {
      continue;
    }

    visited.at(current) = true;
    results.push_back(current);

    // expand edges
    std::vector<edge_t<NodeType, NumericalWeight>> childs =
        g.get_edges(current);

    for (const auto &[edge, weight] : childs | std::views::reverse) {
      open.push_front(edge);
    }
  }

  return results;
}

#endif // !DFS
