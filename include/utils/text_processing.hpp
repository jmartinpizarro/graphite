/*
 * This script contains all code utils for processing strings, specially lines
 * and texts from the .map/.weights files
 */

#ifndef TEXT_PROCESSING
#define TEXT_PROCESSING

#include <charconv>
#include <concepts>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "utils/concepts/node_concepts.hpp"
#include <utils/concepts/numerical_concepts.hpp>

/*
 * Overloaded functions for processing in a way or another the value, depending
 * on its type
 * @param results: reference variable of the results vector in order to insert
 * elements
 * @param token: the current token being processed in that line
 * @returns void / error
 */
template <graphite_concepts::is_numeric T>
void process_line_token(std::vector<T> &results, std::string_view token) {
  T value;
  auto [ptr, ec] =
      std::from_chars(token.data(), token.data() + token.size(), value);
  // std::from_chars works like shit. It is needed no errors and also to
  // check that the pointer size is the same as the one from the token
  // (string). If the ptr is smaller, this means that the token has not
  // being consumed entirely ("9i" -> 9 + "i")
  if (ec == std::errc{} && ptr == token.data() + token.size()) {
    results.emplace_back(value);
  } else {
    throw std::runtime_error("[text_processing] :: Node is configured as "
                             "pure integer, but received text.");
  }
}

template <std::same_as<std::string> T>
void process_line_token(std::vector<T> &results, std::string_view token) {
  results.emplace_back(token);
}

template <graphite_concepts::is_node_type T>
  requires(!graphite_concepts::is_numeric<
           T>) // in case both: numeric and nodeType - are true
void process_line_token(std::vector<T> &results, std::string_view token) {
  int int_value;
  auto [ptr, ec] =
      std::from_chars(token.data(), token.data() + token.size(), int_value);

  if (ec == std::errc{} && ptr == token.data() + token.size()) {
    results.emplace_back(int_value);
  } else {
    if constexpr (!std::is_arithmetic_v<T>) {
      results.emplace_back(std::string(token));
    } else {
      throw std::runtime_error(
          "[text_processing] :: El Nodo es entero puro, pero recibió texto.");
    }
  }
}

/* A custom split_line function for spliting the line, avoiding all possible ' '
 * spaces using ranges and views
 *
 * @param line: string
 * @return vector with all the words;
 */
template <typename T> std::vector<T> split_line(const std::string &line) {
  std::vector<T> results;
  for (const auto &part : line | std::views::split(' ')) {
    std::string_view token(part.begin(), part.end());

    if (token.empty()) {
      continue;
    }

    if (token == "#" or token == "." or token == ",") {
      throw std::runtime_error(
          "[text_processing] :: split_line() has failed. The file cannot "
          "contain symbols such as '.' or ',' or '#'\n");
    }

    process_line_token(results, token);
  }
  return results;
}

#endif // !TEXT_PROCESSING
