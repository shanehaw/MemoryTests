#include "CreateMemoryDocOutputBoundarySpy.h"

CreateMemoryDocOutputBoundarySpy::CreateMemoryDocOutputBoundarySpy()
{

}

CreateMemoryDocOutputBoundarySpy::~CreateMemoryDocOutputBoundarySpy()
{
    if(receivedModel != nullptr)
    {
        for(MemoryItem * item : receivedModel->items)
        {
            delete item;
        }
        delete receivedModel;
        receivedModel = nullptr;
    }
}

void CreateMemoryDocOutputBoundarySpy::present(CreateMemoryDocResultModel *result)
{
    receivedModel = result;
}

