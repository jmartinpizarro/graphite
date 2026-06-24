// test file for debugging :)

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

#include <algorithms/bfs.hpp>
#include <algorithms/dfs.hpp>
#include <algorithms/dijkstra.hpp>
#include <graph/graph.hpp>
#include <variant>

int main(int argc, char *argv[]) {

  // INFO: at the moment, the programs accepts one parameter
  // domain_name: str -> the NAME - not the route - of the graph

  // helper lambda for printing variants variables
  auto print_variant = [](const auto &value) { std::cout << value; };

  if (argc != 2) {
    printf("[graphite_main] :: The program needs one parameter: the name of "
           "the graph - not the route");
    exit(0);
  }

  graph_t<std::variant<std::string, int>, double> g;

  try {
    std::string graph_name(argv[1]);
    g.create_graph(graph_name);
  } catch (std::runtime_error error) {
    printf("[graphite_main] :: An error has ocurred when populating the graph: "
           "\n\t%s\n",
           error.what());
  }

  // do something

  return 0;
}
