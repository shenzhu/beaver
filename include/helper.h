#pragma once

namespace beaver {

template<typename F, typename...Args>
using ResultOf = decltype(std::declval<F>()(std::declval<Args>()...));

}  // namespace beaver