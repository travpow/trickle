

#include <iostream>
#include <memory>
#include "TrRow.hpp"
#include "TrLog.hpp"

using std::endl;

class TestViewDelegate : public TrViewDelegate
{
    using Vec = std::vector<const TrRow>;

public:
    virtual ~TestViewDelegate()
    {
    }

    virtual void append(const TrRow& row)
    {
        TRDEBUG << "TestViewDelegate: " << row << endl;
        rows_.push_back(row);
    }

    Vec::const_iterator begin()
    {
        return rows_.begin();
    }

    Vec::const_iterator end()
    {
        return rows_.end();
    }

    int size() const
    {
        return rows_.size();
    }

private:
    Vec rows_;
};
