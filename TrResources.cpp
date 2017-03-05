

#include "TrResources.hpp"
#include "TrType.hpp"

using Tr::TypeFactory;

TrResources::TrResources()
    : typeFactory_(new TypeFactory(this))
{
}


