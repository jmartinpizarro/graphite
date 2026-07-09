/*
 * This script contains the code for the generic template class of a Graph
 * */

#ifndef GRAPH_T
#define GRAPH_T

#pragma once

#include "utils/concepts/node_concepts.hpp"
#include <format>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <utils/concepts/numerical_concepts.hpp>
#include <utils/text_processing.hpp>

template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
struct edge_t {
  T _to;
  W _weight;
}; // edge_t

template <graphite_concepts::is_node_type T, graphite_concepts::is_numeric W>
class graph_t {
private:
  /* A graph is defined as a:
   * dictionary with all [vertex, List[edges_t]] possible pairs
   *
   * All those vertex can be, theorically, be either a number of a generic name
   * (assume random city) so it is necessary to have some flexibility in the
   * class definition instead of doing preprocesing of the .txt files whe
   * importing the graphs
   */
  int _nnodes = 0; // number of nodes
  T _origin;
  T _goal;
  std::unordered_map<T, std::vector<edge_t<T, W>>> _data;

public:
  // About using & reference on functions, usually with small items is not
  // really THAT useful. However, here T can be numeric or string - for strings
  // is kind of recommendable. Thats why it is used here
  //
  // INFO: return values of some const functions are not being copied. This is
  // useful for time and computer resources, but it is dependant on the object
  // graph_t. If it disappears, ERROR. However, our program should never remove
  // the graph_t object instanciated during its execution - so theorically is
  // secure.

  /*
   * Returns the size - total number of nodes - from a graph
   */
  std::size_t get_size() const { return _data.size(); }

  /*
   * Returns the origin node saved in the graph instance
   */
  const T &get_origin() const { return _origin; }

  /*
   * Returns the goal node saved in the graph instance
   */
  const T &get_goal() const { return _goal; }

  /*
   * Returns all the vertex from the entire graph
   */
  std::vector<T> get_vertex() const {
    std::vector<T> keys;

    keys.reserve(_data.size());
    for (const auto &[vertex, edges] : _data) {
      keys.push_back(vertex);
    }

    return keys;
  }

  /*
   * Returns all the edges from a given vertex
   * @param vertex: T -> the idx of the corresponding vertex to get the data
   * from
   */
  std::vector<edge_t<T, W>> get_edges(const T &vertex_idx) const {
    return {_data.at(vertex_idx)};
  }

  /*
   * Sets the total number of nodes of the graph from the .map file
   * @param nnodes: int
   * @returns void
   */
  void set_nnodes(int nnodes) { _nnodes = nnodes; }

  /*
   * Sets the origin and goal destination for the graphs algorithms
   * @param origin: T
   * @param goal: T
   * @return void
   */
  void set_origin_goal_nodes(T &origin, T &goal) {
    _origin = origin;
    _goal = goal;
  }

  /*
   * Adds a node with its corresponding information to the graph
   * @param node: T -> the vertex
   * @param edges: std::vector<edge_t <T, W>> -> the edges of the node
   * @return bool: True if all went fine, false otherwise
   */
  bool add_node(T &node, std::vector<edge_t<T, W>> &edges) {
    auto [it, inserted] = _data.insert({node, edges});
    return inserted;
  }

  /*
   * Process the .txt file containing the information - given a predefined regex
   * - and populates the entire graph
   * @param graph_name: str -> the name of the graph file (.map) that will be
   * used. Do not include the .termination
   */
  void create_graph(const std::string &graph_name) {
    std::string fline, wline;
    const std::regex regex_weights(R"(^\d+(\.\d+)?(\s+\d+(\.\d+)?)*$)");
    const std::regex regex_simple_word(
        R"(^\S+$)"); // for processing single words in a line
    const std::regex regex_data(R"(^(\S+\s+){1,}\S+$)");
    const std::string MAP_ROUTE = "domains/graphs/";
    const std::string WEIGHTS_ROUTE = "domains/weights/";

    // generate a string for the original route string, and try to open the
    // .weights files corresponding to the .map file
    std::string map_file_route = MAP_ROUTE + graph_name + ".map";
    std::string weights_file_route = WEIGHTS_ROUTE + graph_name + ".weights";

    std::ifstream f(map_file_route);
    std::ifstream w(weights_file_route);

    // open the .map file
    if (!f.is_open()) {
      throw std::runtime_error(std::format(
          "[graph_t] :: The file {} could not be opened.", map_file_route));
    }
    // open the .weights file
    if (!w.is_open()) {
      throw std::runtime_error(std::format(
          "[graph_t] :: The file {} could not be opened.", weights_file_route));
    }
    int fcline = 1;
    bool match;
    T origin, goal;
    while (getline(f, fline)) {
      if (fcline <= 3) {
        bool match = std::regex_match(fline, regex_simple_word);
        if (!match) {
          throw std::runtime_error(std::format(
              "[graph_t] :: The file .map does not follow the defined "
              "convention in line: {}\n",
              fcline));
        }
        switch (fcline) {
        case 1:
          set_nnodes(std::stoi(fline));
          break;
        case 2:
          origin = split_line<T>(fline)[0];
          break;
        case 3:
          goal = split_line<T>(fline)[0];
          set_origin_goal_nodes(origin, goal);
          break;
        default:
          break;
        }
      } else {
        match = std::regex_match(fline, regex_data);
        if (!match) {
          throw std::runtime_error(std::format(
              "[graph_t] :: The file .map does not follow the defined "
              "convention in line: {}\n",
              fcline));
        }
        const std::vector<T> results = split_line<T>(fline.c_str());

        // it is known that the first pos of the vector is the node, and the
        // rest of them are the edges_t
        const int length = results.size();
        T node = results[0];

        // now it is necessary to process the .weights file
        getline(w, wline);
        match = std::regex_match(wline, regex_weights);
        if (!match) {
          throw std::runtime_error(std::format(
              "[graph_t] :: The file .weights does not follow the defined "
              "convention in line: {}\n",
              wline));
        }
        const std::vector<W> wresults = split_line<W>(wline.c_str());
        if (wresults.size() != static_cast<double>(length - 1)) {
          throw std::runtime_error(
              std::format("[graph_t] :: The .weights file contains an extra "
                          "not desired weight in line {}\n",
                          wline));
        }

        std::vector<edge_t<T, W>> edges;
        for (int i = 0; i < length - 1; i++) {
          W weight = wresults[i];
          edge_t<T, W> edge;
          edge._to = results[i + 1];
          edge._weight = weight;
          edges.push_back(edge);
        }

        add_node(node, edges);
      }
      fcline++;
    }
  }
};

#endif // graph_t
