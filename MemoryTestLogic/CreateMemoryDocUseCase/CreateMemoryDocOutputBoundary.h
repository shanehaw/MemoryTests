#ifndef CREATEMEMORYDOCOUTPUTBOUNDARY_H
#define CREATEMEMORYDOCOUTPUTBOUNDARY_H

#include "CreateMemoryDocResultModel.h"

class CreateMemoryDocOutputBoundary {

public:
    CreateMemoryDocOutputBoundary() {}
    virtual ~CreateMemoryDocOutputBoundary() {}
    virtual void present(CreateMemoryDocResultModel * result) = 0;

};

#endif // CREATEMEMORYDOCOUTPUTBOUNDARY_H
