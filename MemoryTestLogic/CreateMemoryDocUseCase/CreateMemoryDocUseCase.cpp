#include "CreateMemoryDocUseCase.h"


void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();    
    Parser parser(request.source, request.punctuationChars);    
    std::vector<MemoryItem*> * line = new std::vector<MemoryItem*>();
    result->lines.push_back(line);
    while(parser.hasNextToken())
    {
         line->push_back(parser.getNextToken());
    }
    outputBoundary.present(result);
}
