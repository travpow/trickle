

#ifndef TRCELL_HPP
#define TRCELL_HPP

#include <iostream>

namespace Tr
{

class Cell
{
public:
    bool operator <(const Cell& rhs) const
    {
        return true;
    }

    bool operator ==(const Cell& rhs) const
    {
        return true;
    }
};

}; // Tr

std::ostream& operator <<(std::ostream& stream, const Tr::Cell& cell);

#endif // TRCELL_HPP
