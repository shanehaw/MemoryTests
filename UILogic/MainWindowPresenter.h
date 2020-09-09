#ifndef UILOGIC_H
#define UILOGIC_H

#include "CreateMemoryDocOutputBoundary.h"

class UILogic: public CreateMemoryDocOutputBoundary
{
public:
    UILogic();
    virtual ~UILogic();
    void present(CreateMemoryDocResultModel *result) override;
};

#endif // UILOGIC_H
