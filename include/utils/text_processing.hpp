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
#include <system_error>
#include <vector>

#include "utils/concepts/node_concepts.hpp"
#include <utils/concepts/numerical_concepts.hpp>

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

    if constexpr (graphite_concepts::is_node_type<T>) {
      // try to transform the string into a numerical value
      int value;
      auto [ptr, ec] =
          std::from_chars(token.data(), token.data() + token.size(), value);
      // std::from_chars works like shit. It is needed no errors and also to
      // check that the pointer size is the same as the one from the token
      // (string). If the ptr is smaller, this means that the token has not
      // being consumed entirely ("9i" -> 9 + "i")
      if (ec == std::errc{} && ptr == token.data() + token.size()) {
        results.emplace_back(value);
      } else {
        // REMEMBER: string_view is temporal! it is necessary to transform it
        if constexpr (!std::is_arithmetic_v<T>) {
          results.emplace_back(std::string(token));
        } else {
          throw std::runtime_error("[text_processing] :: Node is configured as "
                                   "pure integer, but received text.");
        }
      }
    } else if constexpr (graphite_concepts::is_numeric<T>) {
      T value;
      auto [ptr, ec] =
          std::from_chars(token.data(), token.data() + token.size(), value);
      if (ec == std::errc{}) {
        results.emplace_back(value);
      } else {
        throw std::runtime_error(
            "[text_processing] :: split_line() has failed. The file .weight "
            "contains an error in the format.\n");
      }
    } else if constexpr (std::same_as<T, std::string>) {
      results.emplace_back(std::string(token));
    }
  }
  return results;
}

#endif // !TEXT_PROCESSING
