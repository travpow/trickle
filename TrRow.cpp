

#include <vector>
#include "TrRow.hpp"

using std::vector;
using Tr::Cell;

TrRow::TrRow(const vector<Cell>& cells)
    : cells_(cells)
{
}

time_t TrRow::timestamp() const
{
    return timestamp_;
}

const Cell& TrRow::primaryKey(const TrSchema& schema) const
{
    int pos = schema.pos(schema.primaryKey());
    return cells_[pos];
}

const Cell& TrRow::get(int pos) const
{
    return cells_[pos];
}
