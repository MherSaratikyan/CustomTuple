#include <cstddef>
#include <print>

template <typename... Types> class Tuple;
template <> class Tuple<> {};

template <typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
public:
    Tuple() = default;

    Tuple(const Tuple&) = default;
    Tuple(Tuple&&) = default;

    Tuple& operator=(const Tuple&) = default;
    Tuple& operator=(Tuple&&) = default;
    
    Tuple(const Head& first, const Tail&... remaining) 
        : value(first)
        , rest(remaining...) {} 

    template<std::size_t Index, typename H, typename... Ts>
    friend decltype(auto) get(Tuple<H, Ts...>& tuple);

    template<std::size_t Index, typename H, typename... Ts>
    friend decltype(auto) get(const Tuple<H, Ts...>& tuple);

private:
    Head value{};
    Tuple<Tail...> rest;
};

template <std::size_t Index, typename Head, typename... Tail>
decltype(auto) get(Tuple<Head, Tail...>& tuple){
    static_assert(Index < sizeof...(Tail) + 1, "tuple element index out of range");
    if constexpr (Index == 0){
        return tuple.value;
    } else {
        return get<Index - 1>(tuple.rest);
    }
}

template<std::size_t Index, typename Head, typename... Tail>
decltype(auto) get(const Tuple<Head, Tail...>& tuple)
{
    static_assert(Index < sizeof...(Tail) + 1, "tuple element index out of range");
    if constexpr (Index == 0) {
        return tuple.value;
    } else {
        return get<Index - 1>(tuple.rest);
    }
}

int main() {
    auto t = Tuple<int, double, const char*>(42, 3.14, "Hello");
    std::println("{}, {}, {}", get<0>(t), get<1>(t), get<2>(t));
}
