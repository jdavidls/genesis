#include <type_traits>

namespace gns::traits {

}

namespace gns {
  template <typename T>
    constexpr auto isVoid = std::is_void<T>::value;

  template <typename T, typename U>
    constexpr auto isSame = std::is_same<T, U>::value;


  template <typename T, bool V>
    using typeIf = typename std::enable_if<V, T>::type;
/*
  template <typename T, bool V>
    using disableIf = typename std::enable_if<!V, T>::type;
*/

  // GNS_OFFSET_OF(T1, ...): GNS_OFFET_OF(Class, type, accesor, reflector)
}
