#include "CreateMemoryDocUseCase.h"


void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{    
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();    
    Parser parser(request.source, request.punctuationChars);    
    std::vector<MemoryItem*> line;
    while(parser.hasNextToken())
    {
        line.push_back(parser.getNextToken());
    }
    result->lines.push_back(line);
    outputBoundary.present(result);
}
