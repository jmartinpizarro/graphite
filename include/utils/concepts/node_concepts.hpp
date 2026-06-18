#pragma once

#include <concepts>
#include <string>
#include <variant>

namespace graphite_concepts {

// a node can be either a string, a char - not empty string or symbol - or an
// int
template <typename T>
concept is_node_type = std::same_as<T, std::string> || std::same_as<T, int> ||
                       std::same_as<T, std::variant<std::string, int>>;

} // namespace graphite_concepts
