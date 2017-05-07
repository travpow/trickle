
#ifndef TRTYPE_HPP
#define TRTYPE_HPP

#include <map>
#include <string>
#include <memory>
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

    const std::string& name() const
    {
        return name_;
    }

private:
    const std::string name_;
};

using TypeMap = std::map<std::string, std::shared_ptr<Type> >;
using TypeList = std::vector<std::shared_ptr<Type> >;

struct TypeDefinitions
{
    TypeMap map;
    TypeList list;

    ~TypeDefinitions()
    {
        map.clear();
        list.clear();
    }

    void addType(const char* name)
    {
        auto type = std::make_shared<Type>(name);
        map[name] = type;
        list.push_back(type);
    }
};

static Type NoneType("none");

class TypeFactory
{
public:
    TypeFactory(TrResources& resources)
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
    TrResources& resources_;
};

} // Tr

#endif // TRTYPE_HPP
