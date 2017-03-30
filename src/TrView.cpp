

#include "TrView.hpp"

#define MIN_VIEW_SIZE 100

TrView::TrView(const TrTable& table)
    : table_(table), begin_(nullptr), end_(nullptr), beginIndex_(0), endIndex_(MIN_VIEW_SIZE)
{
    // todo: set keyPos_
}

TrView::~TrView()
{
}

int TrView::provideInRange(const TrRow& row, int keyIndex) const
{
    return 0;
}
