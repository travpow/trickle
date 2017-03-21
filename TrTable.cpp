
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "TrType.hpp"
#include "TrTable.hpp"
#include "TrCell.hpp"
#include "TrSchema.hpp"
#include "TrLog.hpp"

using std::find;
using std::set;
using std::string;
using std::vector;
using std::shared_ptr;
using std::endl;
using Tr::Cell;

TrTable::TrTable(const TrSchema& schema, const set<string>& indices)
    : schema_(schema), indiceNames_(indices)
{
    // Always need a primary key index, too.
    indiceNames_.insert(schema.primaryKey());
}

void TrTable::insert(const vector<Cell>& cells)
{
    shared_ptr<TrRow> row(new TrRow(cells));

    rows_[row->timestamp()].push_back(row);

    for (auto itr = indiceNames_.begin(); itr != indiceNames_.end(); ++itr)
    {
        const string& name = *itr;
        const Cell& cell = cells[schema_.pos(name)];

        indices_[name][cell].push_back(row);
    }
}

void TrTable::removeByPrimaryKey(const Cell& primaryKey)
{
    int primaryPos = schema_.pos(schema_.primaryKey());
    auto primaryIndex = indices_[schema_.primaryKey()];
    auto itr = primaryIndex.find(primaryKey);

    if (itr == primaryIndex.end())
    {
        TRERROR << "Asked to remove a row by primary key that could not be found [" << primaryKey
            << ']' <<  endl;

        return;
    }

    // Keep a ptr to the found row
    shared_ptr<TrRow> row = itr->second.front();
    primaryIndex.erase(itr);

    static const char* timeIndex = "(timestamp)";
    removeRowFromIndex(timeIndex, rows_, row, row->timestamp());

    for (auto itr = indiceNames_.begin(); itr != indiceNames_.end(); ++itr)
    {
        const string& indexName = *itr;
        int columnPos = schema_.pos(indexName);

        if (columnPos == primaryPos)
        {
            continue;
        }

        auto& index = indices_[indexName];

        removeRowFromIndex(indexName, index, row, row->get(columnPos));
    }
}

template <typename Key>
void TrTable::removeRowFromIndex(const string& indexName, TrTable::Index<Key, TrRow>& index, const shared_ptr<TrRow>& row, const Key& key)
{
    auto itr = index.find(key);
    if (itr == index.end())
    {
        TRERROR << "Could not find a bucket with index key [" << key << "] for index ["
            << indexName << ']' << endl;

        return;
    }

    auto bucket = itr->second;
    auto indexItr = find(bucket.begin(), bucket.end(), row);

    if (indexItr == bucket.end())
    {
        TRERROR << "Asked to remove a row by bucket that could not be found, index ["
            << indexName << ']' <<  endl;

        return;
    }

    bucket.erase(indexItr);

    if (bucket.empty())
    {
        index.erase(itr);
    }
}
