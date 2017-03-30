

#ifndef TRCELL_HPP
#define TRCELL_HPP

#include <iostream>
#include <memory>

namespace Tr
{

class CellValue
{
public:
    virtual ~CellValue()
    {
    }

    virtual bool operator <(const CellValue& rhs) const = 0;
    virtual bool operator ==(const CellValue& rhs) const = 0;
    virtual std::ostream& write(std::ostream& stream) const = 0;
};

class Cell;

class Cell
{
public:
    Cell(CellValue* value)
        : value_(value)
    {
    }

    bool operator <(const Cell& rhs) const
    {
        return *value_ < *rhs.value_;
    }

    bool operator ==(const Cell& rhs) const
    {
        return value_ == rhs.value_ ||
            *value_ == *rhs.value_;
    }

    std::ostream& write(std::ostream& stream) const
    {
        return value_ ? value_->write(stream) : (stream << "(null)");
    }

private:
    std::shared_ptr<CellValue> value_;
};

}; // Tr

std::ostream& operator <<(std::ostream& stream, const Tr::Cell& cell);

#endif // TRCELL_HPP
