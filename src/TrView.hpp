

#ifndef TRVIEW_HPP
#define TRVIEW_HPP

#include "TrTable.hpp"
#include "TrRow.hpp"

class TrView
{
public:
    TrView(const TrTable& table);
    TrView(const TrTable& table, const Tr::Cell& begin, int beginIndex, const Tr::Cell& end, int endIndex);
    ~TrView();

    /**
     * @param row the row that was inserted into the table view
     * @param keyIndex
     * @return -1 if the row is prior to the beginning, 0 if the row is in the view,
               and 1 if the row is after the end of the view.
     */
    int provideInRange(const TrRow& row, int keyIndex) const;

private:
    const TrTable& table_;
    // TrViewDelegate* viewDelegate_;

    Tr::Cell begin_;
    Tr::Cell end_;
    int beginIndex_;
    int endIndex_; // can be greater than the end of the concrete table

    int keyPos_;
};

#endif // TRVIEW_HPP
