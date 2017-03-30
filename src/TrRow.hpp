
#ifndef TRROW_HPP
#define TRROW_HPP

#include <vector>
#include <iostream>
#include <set>
#include "TrCell.hpp"
#include "TrSchema.hpp"

class TrRow
{
public:
    using Time = int64_t;

    TrRow(const std::vector<Tr::Cell>& cells);

    Time timestamp() const;
    const Tr::Cell& primaryKey(const TrSchema& schema) const;
    const Tr::Cell& get(int pos) const;

private:
    friend std::ostream& operator <<(std::ostream& stream, const TrRow& row);

    Time timestamp_;
    std::vector<Tr::Cell> cells_;
};

std::ostream& operator <<(std::ostream& stream, const TrRow& row);

#endif // TRROW_HPP
