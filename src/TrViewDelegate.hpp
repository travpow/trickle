
#ifndef TRVIEWDELEGATE_HPP
#define TRVIEWDELEGATE_HPP

#include "TrRow.hpp"

class TrViewDelegate
{
public:
    virtual ~TrViewDelegate()
    {
    }

    virtual void append(const TrRow& row) = 0;
};

#endif // TRVIEWDELEGATE_HPP
