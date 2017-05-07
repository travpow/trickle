

#ifndef TRSCHEMA_HPP
#define TRSCHEMA_HPP

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <memory>
#include "TrType.hpp"

class TrSchema
{
using VectorOfPairs = std::vector<std::pair<std::string, std::string> >;

public:
    TrSchema(const Tr::TypeDefinitions& types, const VectorOfPairs& columns, const std::string& primaryKey);

    const Tr::Type* type(const std::string& column) const;
    int pos(const std::string& column) const;
    const std::string& primaryKey() const;
private:
    std::map<std::string, std::shared_ptr<const Tr::Type> > columns_;
    std::map<std::string, int> pos_;
    std::string primaryKey_;
};

#endif // TRSCHEMA_HPP
