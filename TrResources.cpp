

#include "TrResources.hpp"
#include "TrType.hpp"

using Tr::TypeFactory;

TrResources::TrResources()
    : typeFactory_(new TypeFactory(this))
{
}

const Tr::TypeFactory* TrResources::typeFactory() const
{
    return typeFactory_;
}
