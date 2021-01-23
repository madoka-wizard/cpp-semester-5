#pragma once

namespace top_sort {
template<typename...>
struct TypeList {
};

template<typename List>
struct GetHead;

template<typename List>
using GetHeadT = typename GetHead<List>::Type;

template<typename Head, typename... Tail>
struct GetHead<TypeList<Head, Tail...>> {
    using Type = Head;
};

template<typename List>
struct PopFront;

template<typename List>
using PopFrontT = typename PopFront<List>::Type;

template<typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> {
    using Type = TypeList<Tail...>;
};

template<typename List1, typename List2>
struct Merge;

template<typename List1, typename List2>
using MergeT = typename Merge<List1, List2>::Type;

template<typename... Elements1, typename... Elements2>
struct Merge<TypeList<Elements1...>, TypeList<Elements2...>> {
    using Type = TypeList<Elements1..., Elements2...>;
};
} // namespace top_sort
