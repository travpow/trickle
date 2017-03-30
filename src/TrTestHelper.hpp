
#ifndef TRTESTHELPER_HPP

#include <vector>
#include "TrRow.hpp"
#include "TypeImplementations.hpp"

template<typename T>
std::vector<Tr::Cell> TestRow(typename T::base_type t)
{
    return { Tr::Cell(new T(t)) };
}

template<typename T, typename U>
std::vector<Tr::Cell> TestRow(typename T::base_type t, typename U::base_type u)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)) };
}

template<typename T, typename U, typename V>
std::vector<Tr::Cell> TestRow(typename T::base_type t, typename U::base_type u, typename V::base_type v)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)), Tr::Cell(new V(v)) };
}

template<typename T, typename U, typename V, typename W>
std::vector<Tr::Cell> TestRow(typename T::base_type t, typename U::base_type u,
    typename V::base_type v, typename W::base_type w)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)), Tr::Cell(new V(v)), Tr::Cell(new W(w)) };
}

template<typename T, typename U, typename V, typename W, typename X>
std::vector<Tr::Cell> TestRow(typename T::base_type t, typename U::base_type u,
    typename V::base_type v, typename W::base_type w, typename X::base_type x)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)),
        Tr::Cell(new V(v)), Tr::Cell(new W(w)), Tr::Cell(new X(x)) };
}

#endif // TRTESTHELPER_HPP
