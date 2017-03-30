
#ifndef TRPIPELINE_HPP
#define TRPIPELINE_HPP

#include <TrRow.hpp>

class TrPipeline
{
public:
    TrPipeline();
    virtual ~TrPipeline();

    void provide(const TrRow& row);

private:
};

#endif // TRPIPELINE_HPP
