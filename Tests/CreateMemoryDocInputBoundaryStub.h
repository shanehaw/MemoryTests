#ifndef CREATEMEMORYDOCINPUTBOUNDARYSTUB_H
#define CREATEMEMORYDOCINPUTBOUNDARYSTUB_H

#include "CreateMemoryDocInputBoundary.h"
#include "CreateMemoryDocResultModel.h"

class CreateMemoryDocInputBoundaryStub: public CreateMemoryDocInputBoundary
{
public:
    CreateMemoryDocInputBoundaryStub(CreateMemoryDocResultModel* result)
    {
        this->result = result;
    }
    ~CreateMemoryDocInputBoundaryStub() {}
    void create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary) override {
        outputBoundary.present(result);
    }

private:
    CreateMemoryDocResultModel* result;
};

#endif // CREATEMEMORYDOCINPUTBOUNDARYSTUB_H
