// test file for debugging :)

#include <cstdio>
#include <stdexcept>
#include <string>

#include <graph.hpp>

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

  return 0;
}
