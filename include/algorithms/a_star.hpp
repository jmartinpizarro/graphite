/*
 * Search Algorithm: A Star
 * The goat.
 */

#ifndef A_STAR
#define A_STAR

#include <algorithm>
#pragma once

#include <limits>
#include <unordered_map>

#include <algorithms/dfs.hpp>
#include <algorithms/dijkstra.hpp>
#include <graph/graph.hpp>
#include <utils/concepts/node_concepts.hpp>
#include <utils/concepts/numerical_concepts.hpp>
#include <utils/str2int.hpp>

/*
 * A Star Solver Instance Definition
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
class Astar_Solver {
private:
  T _origin;
  T _goal;
  graph_t<T, W> _graph;
  std::string _heuristic;
  W WEIGHT_MIN_FACTOR = std::numeric_limits<W>::max();

public:
  // constructors
  Astar_Solver(T origin_node, T goal_node, graph_t<T, W> graph) {
    _origin = origin_node;
    _goal = goal_node;
    _graph = graph;
  }

  const T &get_origin() const { return _origin; }

  const T &get_goal() const { return _goal; }

  /*
   * A Star Algorithm
   * @param graph
   * @returns a vector<T> with the nodes needed for completing the path
   */
  std::vector<T> a_star() {
    std::unordered_map<T, double> open;
    std::unordered_map<T, W> accumulated_cost;
    // keeps track of the parent of each node, used to reconstruct the path
    std::unordered_map<T, T> came_from;
    // as closed is only going to be inserted, a vector is just enough
    std::vector<T> closed;
    T origin = _graph.get_origin();
    T goal = _graph.get_goal();
    if (origin == goal) {
      throw std::runtime_error(
          "[a_star] :: Origin node and goal node cannot be the same");
    }
    // accumulated cost of the origin node is always zero
    open[origin] = heuristic_function(origin);
    accumulated_cost[origin] = 0;
    while (!open.empty()) {
      // for expanding the node and obtaining the child, use the node with the
      // best heuristic value - the lowest -> shortest path
      auto it = std::min_element(
          open.begin(), open.end(),
          [](const auto &l, const auto &r) { return l.second < r.second; });
      T curr = it->first;
      if (curr == goal) {
        // reconstruct the path backwards, from goal to origin
        std::vector<T> path;
        T node = goal;
        while (node != origin) {
          path.push_back(node);
          node = came_from[node];
        }
        path.push_back(origin);
        // reverse it so it goes from origin to goal
        std::reverse(path.begin(), path.end());
        return path;
      }
      open.erase(curr);
      closed.push_back(curr);
      std::vector<edge_t<T, W>> children = generate_children(curr);
      // if node is in closed list, pass it
      for (const auto &child : children) {
        auto closed_it = std::find(closed.begin(), closed.end(), child._to);
        if (closed_it != closed.end()) {
          continue;
        }
        // f(n) = g(n) + h(n), where g(n) is the accumulated cost till that
        // node
        double tentative_cost = accumulated_cost[curr] + child._weight;
        auto cost_it = accumulated_cost.find(child._to);
        // only update if the node is new or the new path is better
        if (cost_it == accumulated_cost.end() ||
            tentative_cost < cost_it->second) {
          accumulated_cost[child._to] = tentative_cost;
          came_from[child._to] = curr;
          open[child._to] = tentative_cost + heuristic_function(child._to);
        }
      }
    }
    return std::vector<T>{}; // return empty vector - no solution was found
  }

  /*
   * Calculate the heuristic function of a node.
   * f(n) = g(n) + h(n) - this function only calculates h(n). Different
   * heuristics may be used:
   *    - Base: heuristic = 0; ain't doing shit. Greedy Search.
   *    - Relaxed Hop-Count heuristic: takes the W_min of the graph (the lower
   *      edge weight) and, using DFS, calculates the minimum number of edges to
   *      arrive to destination:
   *                    h(n) = W_min * DFS_min_JUMPS
   *
   * @param T curr: current node on which the heuristic is calculated
   *      */
  double heuristic_function(T curr) {
    double h;

    switch (str2int(_heuristic)) {
    case str2int("base"): // Astar is basically Dijkstra
      h = 0;
      return h;
    case str2int("relaxed-hop-count"): {
      // precompute the WEIGHT_MIN_FACTOR for the hop count heuristic if it is
      // the first time invoking the method
      if (WEIGHT_MIN_FACTOR == std::numeric_limits<W>::max()) {
        std::vector<T> nodes = _graph.get_vertex();
        for (auto &node : nodes) {
          std::vector<edge_t<T, W>> edges = _graph.get_edges(node);
          for (edge_t<T, W> edge : edges) {
            if (edge._weight <= WEIGHT_MIN_FACTOR) {
              WEIGHT_MIN_FACTOR = edge._weight;
            }
          }
        }
      }
      std::optional<T> opt_goal = _goal;
      // reverse dfs, from goal to current node
      std::vector<T> res = dfs(_graph, opt_goal);
      size_t counter = 0;
      for (T node : res) {
        if (node != curr) {
          counter++;
        }
      }
      h = WEIGHT_MIN_FACTOR * counter;
      return h;
    }
    // TODO
    case str2int("virtual-embedding"):
      h = 0;
      return h;
    case str2int("abstraction"):
      h = 0;
      return h;
    default:
      return 0.0;
    }
  }

  /*
   * Expands the current node, generating the children - adjacent nodes
   * @param T curr_node
   * @returns vector with all the adjacent edges
   */
  std::vector<edge_t<T, W>> generate_children(const T &curr_node) {
    const std::vector<edge_t<T, W>> children = _graph.get_edges(curr_node);
    return children;
  }

}; // Astar_Solver

#endif // !A_STAR
