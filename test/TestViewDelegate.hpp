

#include <iostream>

class TestViewDelegate : public TrViewDelegate
{
    using Vec = std::vector<const std::shared_ptr<const TrRow> >;

public:
    TestViewDelegate()
        : rows_(100)
    {
    }

    virtual ~TestViewDelegate()
    {
    }

    virtual void append(const std::shared_ptr<const TrRow>& row)
    {
        std::cout << "Row " << *row << std::endl;
        rows_.push_back(row);
    }

    Vec::const_iterator begin() const
    {
        return rows_.begin();
    }

    Vec::const_iterator end() const
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
