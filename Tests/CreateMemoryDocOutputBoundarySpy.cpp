#include "CreateMemoryDocOutputBoundarySpy.h"

CreateMemoryDocOutputBoundarySpy::CreateMemoryDocOutputBoundarySpy()
{

}

CreateMemoryDocOutputBoundarySpy::~CreateMemoryDocOutputBoundarySpy()
{
    if(receivedModel != nullptr)
    {
        for(std::vector<MemoryItem*>* line : receivedModel->lines)
        {
            for(MemoryItem* item : *line)
            {
                delete item;
            }
            delete line;
        }
        //std::wcout << L"starting struct delete" << std::endl;
        delete receivedModel;
        receivedModel = nullptr;
    }
}

void CreateMemoryDocOutputBoundarySpy::present(CreateMemoryDocResultModel *result)
{
    receivedModel = result;
}

