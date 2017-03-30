

#ifndef TRTABLE_HPP
#define TRTABLE_HPP

#include <vector>
#include <map>
#include <list>
#include <memory>
#include "TrRow.hpp"
#include "TrCell.hpp"

class TrPipeline;
class TrView;

class TrTable
{
    template<typename Row>
    using RowList = std::list<std::shared_ptr<Row> >;

    template<typename Value, typename Row>
    using Index = std::map<Value, RowList<Row> >;

public:
    TrTable(const TrSchema& schema, const std::set<std::string>& indices);

    void insert(const std::vector<Tr::Cell>& row);
    void removeByPrimaryKey(const Tr::Cell& primaryKey);
    const std::list<std::shared_ptr<TrRow> >& getByIndex(const std::string& indexName, const Tr::Cell& value);

    void addView(TrView* view);

private:
    const TrSchema& schema_;
    std::set<std::string> indiceNames_;

    Index<TrRow::Time, TrRow> rows_;
    std::map<std::string, Index<Tr::Cell, TrRow> > indices_;

    std::set<TrPipeline*> downstream_;
    std::set<TrView*> views_;

    template <typename Key>
    void removeRowFromIndex(const std::string& indexName, Index<Key, TrRow>& index, const std::shared_ptr<TrRow>& row, const Key& key);
};

#endif // TRTABLE_HPP
