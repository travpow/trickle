

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

std::ostream& operator <<(std::ostream& stream, const TrRow& row)
{
    bool hasPrinted = false;

    stream << "Row[";

    for (auto itr = row.cells_.begin();
        itr != row.cells_.end(); ++itr)
    {
        if (hasPrinted)
            stream << ',';

        stream << *itr;
        hasPrinted = true;
    }

    stream << ']';

    return stream;
}
