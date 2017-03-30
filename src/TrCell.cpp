
#include "TrCell.hpp"

std::ostream& operator <<(std::ostream& stream, const Tr::Cell& cell)
{
    return cell.write(stream);
}
