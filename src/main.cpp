// test file for debugging :)

#include <string>

#include <graph/graph.hpp>

int main(int argc, char *argv[]) {

  // INFO: at the moment, the programs accepts one parameter
  // domain_name: str -> the NAME - not the route - of the graph

  if (argc != 2) {
    printf("[graphite_main] :: The program needs one parameter: the name of "
           "the graph - not the route");
    exit(0);
  }

  std::string graph_name(argv[1]);

  // TODO: how do we know the weight is INT? it could be also float, or long, or
  // double
  // we are defining here the type of the weight. This should change
  graph_t<std::variant<std::string, int>, int> g;
  // INFO: "graph1" is considered a char[6], not a string. The
  // create_graph functions needs a const for this to be able to
  // compile. Otherwise, create an string
  g.create_graph(graph_name);
  return 0;
}
