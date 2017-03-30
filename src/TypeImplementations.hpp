
#ifndef TYPEIMPLEMENTATIONS_HPP
#define TYPEIMPLEMENTATIONS_HPP

#include "TrCell.hpp"

namespace Tr
{

template<typename T>
class BasicValue : public CellValue
{
public:
    using base_type = T;

    BasicValue(const T& value)
        : value_(value)
    {
    }

    virtual ~BasicValue()
    {
    }

    virtual bool operator <(const CellValue& rhs) const
    {
        return
            typeid(*this) == typeid(rhs) &&
            value_ < static_cast<const BasicValue<T>&>(rhs).value_;
    }

    virtual bool operator ==(const CellValue& rhs) const
    {
        return
            typeid(*this) == typeid(rhs) &&
            value_ == static_cast<const BasicValue<T>&>(rhs).value_;
    }

    virtual std::ostream& write(std::ostream& stream) const
    {
        stream << value_;
        return stream;
    }

private:
    T value_;
};

using String = BasicValue<std::string>;
using Int32  = BasicValue<int32_t>;
using Int64  = BasicValue<int64_t>;
using Double = BasicValue<double>;

};

#endif // TYPEIMPLEMENTATIONS_HPP
