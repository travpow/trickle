

#ifndef TRSCHEMA_HPP
#define TRSCHEMA_HPP

#include <string>
#include <utility>
#include <vector>
#include <map>
#include "TrType.hpp"

class TrSchema
{
public:
    TrSchema(const Tr::TypeMap& typeMap, const std::vector<std::pair<std::string, std::string> >& columns);

    const Tr::Type* type(const std::string& column) const;
    size_t pos(const std::string& column) const;
private:
    std::map<std::string, const Tr::Type*> columns_;
    std::map<std::string, size_t> pos_;
};

#endif // TRSCHEMA_HPP
