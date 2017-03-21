

#ifndef TRROW_HPP
#define TRROW_HPP

#include <vector>
#include "TrCell.hpp"
#include "TrSchema.hpp"

class TrRow
{
public:
    TrRow(const std::vector<Tr::Cell>& cells);

    time_t timestamp() const;
    const Tr::Cell& primaryKey(const TrSchema& schema) const;
    const Tr::Cell& get(int pos) const;

private:
    time_t timestamp_;
    std::vector<Tr::Cell> cells_;
};

#endif // TRROW_HPP
