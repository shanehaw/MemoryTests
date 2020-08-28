#include "CreateMemoryDocUseCase.h"


void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();
    Parser parser(request.source, request.punctuationChars);
    std::vector<MemoryItem> pItems;
    while(parser.hasNextToken())
    {
         result->items.push_back(parser.getNextToken());
    }
    outputBoundary.present(result);
}
