

#ifndef TRTABLE_HPP
#define TRTABLE_HPP

#include <vector>
#include <map>
#include <list>
#include <memory>
#include "TrRow.hpp"
#include "TrCell.hpp"

class TrPipeline;

class TrTable
{
public:
    TrTable(const TrSchema& schema, const std::set<std::string>& indices);

    void insert(const std::vector<Tr::Cell>& row);
    void removeByPrimaryKey(const Tr::Cell& primaryKey);

private:
    const TrSchema& schema_;
    std::set<std::string> indiceNames_;

    template<typename Value, typename Row>
    using Index = std::map<Value, std::list<std::shared_ptr<Row> > >;

    Index<time_t, TrRow> rows_;
    std::map<std::string, Index<Tr::Cell, TrRow> > indices_; 
    std::set<TrPipeline*> downstream_;

    template <typename Key>
    void removeRowFromIndex(const std::string& indexName, Index<Key, TrRow>& index, const std::shared_ptr<TrRow>& row, const Key& key);
};

#endif // TRTABLE_HPP
