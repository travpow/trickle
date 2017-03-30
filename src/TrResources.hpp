
#ifndef TRRESOURCES_HPP
#define TRRESOURCES_HPP

namespace Tr {
    class TypeFactory;
}

class TrResources
{
public: 
    TrResources(); 

    const Tr::TypeFactory* typeFactory() const;

private:
    Tr::TypeFactory* typeFactory_;
};

#endif // TRRESOURCES_HPP
