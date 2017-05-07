
#ifndef TRRESOURCES_HPP
#define TRRESOURCES_HPP

#include <memory>

namespace Tr {
    class TypeFactory;
}

class TrResources
{
public:
    TrResources();

    std::shared_ptr<Tr::TypeFactory> typeFactory() const
    {
        return typeFactory_;
    }

private:
    std::shared_ptr<Tr::TypeFactory> typeFactory_;
};

#endif // TRRESOURCES_HPP
