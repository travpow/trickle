

#ifndef TRVIEW_HPP
#define TRVIEW_HPP

#include "TrTable.hpp"
#include "TrRow.hpp"
#include "TrViewDelegate.hpp"
#include "TrOp.hpp"

class TrView
{
public:
    TrView(const TrTable& table, const std::string& index);
    TrView(const TrTable& table, const std::string& index,
        const Tr::Cell& begin, int beginIndex, const Tr::Cell& end, int endIndex);
    ~TrView();

    /**
     * @param row the row that was inserted into the table view
     * @param keyIndex for this particular row, the nth element in the index
     * @param type of operation, insertion, removal, or replacement
     * @return -1 if the row is prior to the beginning, 0 if the row is in the view,
               and 1 if the row is after the end of the view.
     */
    int provideInRange(const TrRow& row, int keyIndex, Tr::Op::Value operation) const;
    void snap();
    int size() const;

    int windowSize() const;
    void setWindowSize(int windowSize);
    void setDelegate(TrViewDelegate* viewDelegate);

private:
    const TrTable& table_;
    const std::string index_;
    TrViewDelegate* viewDelegate_;

    Tr::Cell begin_;
    Tr::Cell end_;
    int beginIndex_;
    int endIndex_; // can be greater than the end of the concrete table

    int keyPos_;
    int windowSize_;
};

#endif // TRVIEW_HPP
