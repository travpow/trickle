
#ifndef TRTYPE_HPP
#define TRTYPE_HPP

#include <map>
#include <string>
#include <vector>

class TrResources;

namespace Tr
{

class Type
{
public:
    Type(const std::string& name)
        : name_(name)
    {
    }

private:
    const std::string name_;

};

using TypeMap = std::map<std::string, Type*>;
using TypeList = std::vector<Type*>;

struct TypeDefinitions
{
    TypeMap map;
    TypeList list;
};

static Type NoneType("none");

class TypeFactory
{
public:
    TypeFactory(TrResources* resources)
        : resources_(resources)
    {
    }

    TypeDefinitions* createTypes() const
    {
        int i = 0;
        TypeDefinitions* td = new TypeDefinitions();

        return td;
    }

private:
    TrResources* resources_;
};

} // Tr

#endif
