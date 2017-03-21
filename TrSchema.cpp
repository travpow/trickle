
#include <vector>
#include <utility>
#include <string>
#include "TrSchema.hpp"
#include "TrType.hpp"
#include "TrLog.hpp"

using std::vector;
using std::pair;
using std::string;
using std::endl;
using Tr::TypeDefinitions;

TrSchema::TrSchema(const TypeDefinitions& types, const vector<pair<string, string> >& columns)
{
    for (int i = 0; i < columns.size(); ++i)
    {
        const string& columnName = columns[i].first;

        auto typeItr = types.map.find(columns[i].second);
        if (typeItr == types.map.end())
        {
            TRERROR << "Could not find a type [" << columns[i].second << "] for column [" << columns[i].first << ']' << endl;
            continue;
        }

        columns_[columnName] = typeItr->second;
        pos_[columnName] = i;
    }
}

const Tr::Type* TrSchema::type(const string& column) const
{
    auto itr = columns_.find(column);
    if (itr == columns_.end())
    {
        return &Tr::NoneType;
    }

    return itr->second;
}

int TrSchema::pos(const string& column) const
{
    auto itr = pos_.find(column);
    if (itr == pos_.end())
    {
        return -1;
    }

    return itr->second;
}

const string& TrSchema::primaryKey() const
{
    return primaryKey_;
}
