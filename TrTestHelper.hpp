
#ifndef TRTESTHELPER_HPP

#include <vector>
#include "TrRow.hpp"
#include "TypeImplementations.hpp"

template<typename T, typename TT>
std::vector<Tr::Cell> TestRow(TT t)
{
    return { Tr::Cell(new T(t)) }; 
}

template<
    typename T, typename U,
    typename TT, typename UU>
std::vector<Tr::Cell> TestRow(TT t, UU u)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)) }; 
}

template<
    typename T, typename U, typename V,
    typename TT, typename UU, typename VV>
std::vector<Tr::Cell> TestRow(TT t, UU u, VV v)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)), Tr::Cell(new V(v)) }; 
}

template<
    typename T, typename U, typename V, typename W,
    typename TT, typename UU, typename VV, typename WW>
std::vector<Tr::Cell> TestRow(TT t, UU u, VV v, WW w)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)), Tr::Cell(new V(v)), Tr::Cell(new W(w)) }; 
}

template<
    typename T, typename U, typename V, typename W, typename X,
    typename TT, typename UU, typename VV, typename WW, typename XX>
std::vector<Tr::Cell> TestRow(TT t, UU u, VV v, WW w, XX x)
{
    return { Tr::Cell(new T(t)), Tr::Cell(new U(u)), Tr::Cell(new V(v)), Tr::Cell(new W(w)), Tr::Cell(new X(x)) }; 
}

#endif // TRTESTHELPER_HPP
