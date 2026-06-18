#pragma once

#include <concepts>

namespace graphite_concepts {

// create a custom concept for integers and floats... but integral allows chars
// and bool!
template <typename W>
concept is_numeric = (std::integral<W> || std::floating_point<W>) &&
                     !std::same_as<W, bool> && !std::same_as<W, char>;

} // namespace graphite_concepts
