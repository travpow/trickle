
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

    ~TypeDefinitions()
    {
        for (auto itr = list.begin(); itr != list.end(); ++itr)
        {
            delete *itr;
        }
    }

    void addType(const char* name)
    {
        Type* type = new Type(name);
        map[name] = type;
        list.push_back(type);
    }
};

static Type NoneType("none");

class TypeFactory
{
public:
    TypeFactory(TrResources* resources)
        : resources_(resources)
    {
    }

    TypeDefinitions createTypes() const
    {
        TypeDefinitions td;
        td.addType("int32");
        td.addType("int64");
        td.addType("double");
        td.addType("string");
        td.addType("date");
        td.addType("interval");

        return td;
    }

private:
    TrResources* resources_;
};

} // Tr

#endif // TRTYPE_HPP
