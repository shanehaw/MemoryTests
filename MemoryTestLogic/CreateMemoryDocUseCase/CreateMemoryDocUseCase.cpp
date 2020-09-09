#include "CreateMemoryDocUseCase.h"


void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{    
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();
    LineExtractor lineExtractor(request.source, L'\n');
    for(std::wstring line : lineExtractor.extractLines())
    {        
        result->lines.push_back(parseLine(line, request.punctuationChars));
    }
    outputBoundary.present(result);
}

std::vector<MemoryItem*> CreateMemoryDocUseCase::parseLine(std::wstring line, std::set<wchar_t> punctuationChars)
{
    std::vector<MemoryItem*> result;
    LineParser parser(line, punctuationChars);
    while(parser.hasNextToken())
    {
        result.push_back(parser.getNextToken());
    }
    return result;
}
