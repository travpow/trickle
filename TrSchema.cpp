
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
using Tr::TypeMap;

TrSchema::TrSchema(const TypeMap& typeMap, const vector<pair<string, string> >& columns)
{
    for (int i = 0; i < columns.size(); ++i)
    {
        const string& columnName = columns[i].first;

        auto typeItr = typeMap.find(columns[i].second);
        if (typeItr == typeMap.end())
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

size_t TrSchema::pos(const string& column) const
{
    auto itr = pos_.find(column);
    if (itr == pos_.end())
    {
        return -1;
    }

    return itr->second;
}
