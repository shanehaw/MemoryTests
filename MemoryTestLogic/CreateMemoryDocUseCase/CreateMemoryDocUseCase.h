#ifndef CREATEMEMORYDOCUSECASE_H
#define CREATEMEMORYDOCUSECASE_H

#include "CreateMemoryDocInputBoundary.h"
#include "../Utils/Parser.h"

class CreateMemoryDocUseCase : public CreateMemoryDocInputBoundary
{
public:
    CreateMemoryDocUseCase() { }
    ~CreateMemoryDocUseCase() { }
    void create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary) override;
};

#endif // CREATEMEMORYDOCUSECASE_H
