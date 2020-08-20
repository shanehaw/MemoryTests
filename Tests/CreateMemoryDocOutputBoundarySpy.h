#ifndef CREATEMEMORYDOCOUTPUTBOUNDARYSPY_H
#define CREATEMEMORYDOCOUTPUTBOUNDARYSPY_H

#include "CreateMemoryDocOutputBoundary.h"

class CreateMemoryDocOutputBoundarySpy: public CreateMemoryDocOutputBoundary
{
public:
    CreateMemoryDocOutputBoundarySpy();
    virtual ~CreateMemoryDocOutputBoundarySpy();

    void present(CreateMemoryDocResultModel *result) override;
    CreateMemoryDocResultModel * receivedModel;
};

#endif // CREATEMEMORYDOCOUTPUTBOUNDARYSPY_H
