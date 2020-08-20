#include "CreateMemoryDocOutputBoundarySpy.h"

CreateMemoryDocOutputBoundarySpy::CreateMemoryDocOutputBoundarySpy()
{

}

CreateMemoryDocOutputBoundarySpy::~CreateMemoryDocOutputBoundarySpy()
{
    if(receivedModel != nullptr)
    {
        delete receivedModel;
    }
}

void CreateMemoryDocOutputBoundarySpy::present(CreateMemoryDocResultModel *result)
{
    receivedModel = result;
}

