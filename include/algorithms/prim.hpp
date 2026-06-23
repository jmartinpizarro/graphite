/*
 * Prim algorithm for finding the Minimal Spanning Tree - MST.
 */

#ifndef PRIM
#define PRIM

#include <unordered_map>
#include <vector>

#include <graph/graph.hpp>
#include <utils/concepts/node_concepts.hpp>
#include <utils/concepts/numerical_concepts.hpp>

namespace algorithms {

/*
 * Implements the Prim algorithm for the MST.
 * @param graph<T, W> g
 * @returns unordered_map<vertex, vector<edge_t>>
 */
template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
std::unordered_map<T, std::vector<edge_t<T, W>>> prim(const graph_t<T, W> &g) {}

} // namespace algorithms
#endif // !PRIM
