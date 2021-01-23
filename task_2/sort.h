#pragma once

#include "utils.h"
#include <type_traits>

namespace top_sort {
template<typename Base, typename List>
struct SplitList;

template<typename Base, typename Head>
struct SplitList<Base, TypeList<Head>> {
    static constexpr bool is_based = std::is_base_of_v<Base, Head>;
    using Derived = std::conditional_t<is_based, TypeList<Head>, TypeList<>>;
    using NotDerived = std::conditional_t<is_based, TypeList<>, TypeList<Head>>;
};

template<typename Base, typename List>
using SplitListDerived = typename SplitList<Base, List>::Derived;

template<typename Base, typename List>
using SplitListNotDerived = typename SplitList<Base, List>::NotDerived;

template<typename Base, typename... Types>
struct SplitList<Base, TypeList<Types...>> {
    using Head = GetHeadT<TypeList<Types...>>;
    static constexpr bool is_based = std::is_base_of_v<Base, Head>;
    using Derived = MergeT<
            std::conditional_t<is_based, TypeList<Head>, TypeList<>>,
            SplitListDerived<Base, PopFrontT<TypeList<Types...>>>
    >;
    using NotDerived = MergeT<
            std::conditional_t<is_based, TypeList<>, TypeList<Head>>,
            SplitListNotDerived<Base, PopFrontT<TypeList<Types...>>>
    >;
};

template<typename List>
struct Sort;

template<typename List>
using SortT = typename Sort<List>::Type;

template<>
struct Sort<TypeList<>> {
    using Type = TypeList<>;
};

template<typename Head>
struct Sort<TypeList<Head>> {
    using Type = TypeList<Head>;
};

template<typename Head, typename... Tail>
struct Sort<TypeList<Head, Tail...>> {
    using Type = MergeT<
            MergeT<SortT<SplitListDerived<Head, TypeList<Tail...>>>, TypeList<Head>>,
            SortT<SplitListNotDerived<Head, TypeList<Tail...>>>
    >;
};
} // namespace top_sort
