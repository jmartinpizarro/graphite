// test file for debugging :)

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

#include <algorithms/bfs.hpp>
#include <algorithms/dfs.hpp>
#include <graph/graph.hpp>
#include <variant>

int main(int argc, char *argv[]) {

  // INFO: at the moment, the programs accepts one parameter
  // domain_name: str -> the NAME - not the route - of the graph

  if (argc != 2) {
    printf("[graphite_main] :: The program needs one parameter: the name of "
           "the graph - not the route");
    exit(0);
  }

  graph_t<std::variant<std::string, int>, int> g;

  try {
    std::string graph_name(argv[1]);
    g.create_graph(graph_name);
  } catch (std::runtime_error error) {
    printf("[graphite_main] :: An error has ocurred when populating the graph: "
           "\n\t%s\n",
           error.what());
  }

  std::cout << "Executing the DFS algorithm\n";
  std::vector<std::variant<std::string, int>> dfs_result = dfs(g);

  for (const auto node : dfs_result) {
    std::visit([](const auto &value) { std::cout << value << "\n"; }, node);
  }

  std::cout << "Executing the BFS algorithm\n";
  std::vector<std::variant<std::string, int>> bfs_result = bfs(g);

  for (const auto node : bfs_result) {
    std::visit([](const auto &value) { std::cout << value << "\n"; }, node);
  }

  return 0;
}
