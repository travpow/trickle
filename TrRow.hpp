

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
    TrRow(const std::vector<Tr::Cell>& cells);

    time_t timestamp() const;
    const Tr::Cell& primaryKey(const TrSchema& schema) const;
    const Tr::Cell& get(int pos) const;

private:
    friend std::ostream& operator <<(std::ostream& stream, const TrRow& row);

    time_t timestamp_;
    std::vector<Tr::Cell> cells_;
};

std::ostream& operator <<(std::ostream& stream, const TrRow& row);

#endif // TRROW_HPP
