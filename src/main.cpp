// test file for debugging :)

#include "algorithms/floyd_warshall.hpp"
#include <cstdio>
#include <stdexcept>
#include <string>

#include <graph.hpp>
#include <unordered_map>

int main(int argc, char *argv[]) {

  // INFO: at the moment, the programs accepts one parameter
  // domain_name: str -> the NAME - not the route - of the graph

  if (argc != 2) {
    printf("[graphite_main] :: The program needs one parameter: the name of "
           "the graph - not the route");
    exit(0);
  }

  graph_t<int, int> g;

  try {
    std::string graph_name(argv[1]);
    g.create_graph(graph_name);
  } catch (const std::runtime_error &error) {
    printf("[graphite_main] :: An error has ocurred when populating the graph: "
           "\n\t%s\n",
           error.what());
  }

  // a_star
  Astar_Solver<int, int> solver{g.get_origin(), g.get_goal(), g};
  std::vector<int> path = solver.a_star();

  for (const auto &node : path) {
    std::printf("%d \n", node);
  }

  // prim
  std::unordered_map<int, edge_t<int, int>> prim_sol = prim(g);
  for (const auto &pair : prim_sol) {
    printf("%d - %d\n", pair.first, pair.second._weight);
  }

  auto warshall_res = warshall(g);
  for (int i = 0; i < static_cast<int>(g.get_size()); i++) {
    for (int j = 0; j < static_cast<int>(g.get_size()); j++) {
      printf("From %d to %d to optimal cost is: %d\n", i + 1, j + 1,
             warshall_res[i][j]);
    }
  }
  return 0;
}
