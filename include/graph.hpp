/*
 * This script contains the code for the generic template class of a Graph
 * */

#ifndef GRAPH_T
#define GRAPH_T

#include <concepts>
#include <format>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// create a custom concept for integers and floats... but integral allows chars
// and bool!
template <typename W>
concept is_numeric = (std::integral<W> || std::floating_point<W>) &&
                     !std::same_as<W, bool> && !std::same_as<W, char>;

template <typename T, is_numeric W> struct edge_t {
  T _to;
  W _weight;
}; // edge_t

template <typename T, is_numeric W> class graph_t {
private:
  /* A graph is defined as a:
   * dictionary with all [vertex, List[edges_t]] possible pairs
   *
   * All those vertex can be, theorically, be either a number of a generic name
   * (assume random city) so it is necessary to have some flexibility in the
   * class definition instead of doing preprocesing of the .txt files whe
   * importing the graphs
   */
  std::unordered_map<T, std::vector<edge_t<T, W>>> _data;

public:
  /*
   * Returns the size - total number of nodes - from a graph
   */
  int get_size() { return _data.size(); }

  /*
   * Returns all the vertex from the entire graph
   */
  std::vector<T> get_vertex() {
    std::vector<T> keys;

    keys.reserve(_data.size());
    for (auto key : _data) {
      keys.push_back(key);
    }

    return keys;
  }

  /*
   * Returns all the edges from a given vertex
   * @param vertex: T -> the idx of the corresponding vertex to get the data
   * from
   */
  std::vector<edge_t<T, W>> get_edges(T vertex_idx) {
    return {_data[vertex_idx]};
  }

  /*
   * Process the .txt file containing the information - given a predefined regex
   * - and populates the entire graph
   * @param route: str -> route to the file that contains the graph information
   */
  void create_graph(std::string route) {
    std::string line;
    std::ifstream f(route);

    std::regex regex_data(R"(^(\S+\s+){2,}\S+$)");

    if (!f.is_open()) {
      throw std::runtime_error(
          std::format("[graph_t] :: The file {} could not be opened.", route));
    }

    while (getline(f, line)) {
    }
  }
};

#endif // graph_t
