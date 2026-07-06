/*
 * Search Algorithm: A Star
 * The goat.
 */

#ifndef A_STAR
#define A_STAR

#include <stdexcept>
#pragma once

#include <unordered_map>

#include <algorithms/dijkstra.hpp>
#include <graph/graph.hpp>
#include <utils/concepts/node_concepts.hpp>
#include <utils/concepts/numerical_concepts.hpp>

/*
 * Calculate the heuristic function of a node.
 * f(n) = g(n) + h(n), where g(n) is the accumulated cost and h(n) is the
dijkstra distance from that node to the goal node
 * @param node<T>
 * @param weight<T>
 * @returns weight: double
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
double calculate_heuristic(const T &node, const W &weight) {
  double heuristic_value;

  // calculations...

  return heuristic_value;
}

/*
 * A Star Algorithm function definition
 * @param graph
 * @returns a vector<T> with the nodes needed for completing the path
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
std::vector<T> a_star(const graph_t<T, W> &g) {
  std::vector<T> path;
  std::unordered_map<T, double> open;
  // as closed is only going to be inserted, a vector is just enough
  std::vector<T> closed;

  T origin = g.get_origin();
  T goal = g.get_goal();

  if (origin == goal) {
    throw std::runtime_error(
        "[a_star] :: Origin node and goal node cannot be the same");
  }

  open.push_back(origin);

  while (open.size() != 0) {

    // for expanding the node and obtaining the child
  }

  return path;
}

#endif // !A_STAR
