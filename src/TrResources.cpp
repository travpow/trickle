

#include "TrResources.hpp"
#include "TrType.hpp"

using Tr::TypeFactory;

TrResources::TrResources()
    : typeFactory_(std::make_shared<Tr::TypeFactory>(*this))
{
}
