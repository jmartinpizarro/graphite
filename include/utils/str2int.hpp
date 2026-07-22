/*
 * This script contains the code for transforming a string into an int so it can
 * be used in a switch-case statement
 */

#include <string_view>

constexpr unsigned int str2int(std::string_view str) {
  unsigned int hash = 2166136261u;
  for (char c : str) {
    hash ^= static_cast<unsigned int>(c);
    hash *= 16777619u;
  }
  return hash;
}
