
#include <string>
#include <iostream>
#include "TrLog.hpp"
#include "TrView.hpp"

#define MIN_VIEW_SIZE 100

using std::string;
using std::endl;

TrView::TrView(const TrTable& table, const string& index)
    : table_(table), index_(index), viewDelegate_(nullptr), begin_(nullptr), end_(nullptr), beginIndex_(-1), endIndex_(-1)
{
    windowSize_ = MIN_VIEW_SIZE;
}

TrView::TrView(const TrTable& table, const string& index,
    const Tr::Cell& begin, int beginIndex, const Tr::Cell& end, int endIndex)
    : table_(table), index_(index), viewDelegate_(nullptr), begin_(begin), end_(end), beginIndex_(beginIndex), endIndex_(endIndex)
{
    windowSize_ = MIN_VIEW_SIZE;
}

TrView::~TrView()
{
}

int TrView::provideInRange(const TrRow& row, int keyIndex) const
{
    return 0; // todo
}

void TrView::snap()
{
    if (!viewDelegate_)
    {
        TRINFO << "No delegate for view" << endl;
        return;
    }

    auto* index = table_.getIndex(index_);

    if (!index)
    {
        TRERROR << "Could not snap table on index name [" << index_ << ']' << endl;
        return;
    }

    int remaining = windowSize();

    if (!begin_)
    {
        for (auto outer = index->begin();
            outer != index->end();
            ++outer)
        {
            if (!begin_)
                begin_ = outer->first;

            int index = 0;

            for (auto inner = outer->second.begin();
                inner != outer->second.end();
                ++inner, ++index)
            {
                if (beginIndex_ < 0)
                    beginIndex_ = index;

                viewDelegate_->append(**inner); 
                remaining--;

                if (remaining == 0)
                {
                    end_ = outer->first;
                    endIndex_ = index;
                    return;
                }
            }
        }
    }
    else
    {
        TRINFO << "TODO: preset view sizes" << endl;        
    }
}

void TrView::setWindowSize(int windowSize)
{
    windowSize_ = windowSize;
}

void TrView::setDelegate(TrViewDelegate* viewDelegate)
{
    viewDelegate_ = viewDelegate;
}

int TrView::windowSize() const
{
    return windowSize_;
}
