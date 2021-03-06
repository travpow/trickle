
#include <string>
#include <iostream>
#include "TrLog.hpp"
#include "TrView.hpp"
#include "TrOp.hpp"

#define MIN_VIEW_SIZE 100

using std::string;
using std::endl;

TrView::TrView(const TrTable& table, const string& index)
    : table_(table), index_(index), viewDelegate_(nullptr), begin_(nullptr), end_(nullptr), beginIndex_(-1), endIndex_(-1)
{
    windowSize_ = MIN_VIEW_SIZE;
    keyPos_ = table_.schema_.pos(index_);
}

TrView::TrView(const TrTable& table, const string& index,
    const Tr::Cell& begin, int beginIndex, const Tr::Cell& end, int endIndex)
    : table_(table), index_(index), viewDelegate_(nullptr), begin_(begin), end_(end), beginIndex_(beginIndex), endIndex_(endIndex)
{
    windowSize_ = MIN_VIEW_SIZE;
    keyPos_ = table_.schema_.pos(index_);
}

TrView::~TrView()
{
}

int TrView::provideInRange(const TrRow& row, int keyIndex, Tr::Op::Value operation) const
{
    if (!viewDelegate_)
    {
        TRWARN << "No delegate for view on index [" << index_ << ']' << endl;
        return 0;
    }

    const auto& cell = row.get(keyPos_);
    bool beforeStart = cell < begin_ ||
            (cell == begin_ && keyIndex < beginIndex_);

    bool afterEnd = cell > end_ ||
            (cell == end_ && keyIndex > beginIndex_);

    if (beforeStart)
    {
        if (operation == Tr::Op::Append || operation == Tr::Op::Remove)
        {
            // TODO: View provider resize before
        }
    }
    else if (afterEnd)
    {
        if (operation == Tr::Op::Append || operation == Tr::Op::Remove)
        {
            // TODO: View provider resize after
        }
    }
    else
    {
        // TODO: splice in view
    }

    return 0; // todo
}

void TrView::snap()
{
    if (!viewDelegate_)
    {
        TRWARN << "No delegate for view on index [" << index_ << ']' << endl;
        return;
    }

    auto* index = table_.getIndex(index_);

    if (!index)
    {
        TRERROR << "Could not snap table on index name [" << index_ << ']' << endl;
        return;
    }

    int remaining = windowSize();

    auto outer = index->begin();
    if (begin_)
    {
        outer = index->find(begin_);
    }

    for (;
        outer != index->end();
        ++outer)
    {
        if (!begin_)
            begin_ = outer->first;

        int index = 0;
        auto inner = outer->second.begin();

        // Skip to the index
        for (; index < beginIndex_; ++inner, ++index)
            ;

        for (;
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
