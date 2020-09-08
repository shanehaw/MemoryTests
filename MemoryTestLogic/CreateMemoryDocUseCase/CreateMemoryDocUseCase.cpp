#include "CreateMemoryDocUseCase.h"


void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{    
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();    
    std::vector<std::wstring> lines = breakIntoLines(request.source, L'\n');
    for(std::wstring line : lines)
    {
        std::vector<MemoryItem*> resultLine;
        Parser parser(line, request.punctuationChars);
        while(parser.hasNextToken())
        {
            resultLine.push_back(parser.getNextToken());
        }
        result->lines.push_back(resultLine);
    }
    outputBoundary.present(result);
}

std::vector<std::wstring> CreateMemoryDocUseCase::breakIntoLines(std::wstring source, wchar_t newLineChar)
{
    std::vector<std::wstring> result;
    std::vector<wchar_t> lineBuffer;
    for(size_t i = 0; i < source.length(); i++)
    {
        wchar_t current = source[i];
        if(current != newLineChar)
        {
            lineBuffer.push_back(current);
        }
        else
        {
            result.push_back(std::wstring(lineBuffer.begin(), lineBuffer.end()));
            lineBuffer.clear();
        }
    }
    result.push_back(std::wstring(lineBuffer.begin(), lineBuffer.end()));
    lineBuffer.clear();

    return result;
}
