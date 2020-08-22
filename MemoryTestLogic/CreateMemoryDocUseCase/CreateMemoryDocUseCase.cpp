#include "CreateMemoryDocUseCase.h"

CreateMemoryDocUseCase::CreateMemoryDocUseCase()
{

}

CreateMemoryDocUseCase::~CreateMemoryDocUseCase()
{

}

void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{    
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();
    auto it = request.source.cbegin();
    auto end = request.source.cend();
    while(it != end)
    {        
        wchar_t c = *it;
        if(iswspace(c))
        {
            ++it;
            continue;
        }      

        std::vector<wchar_t> token;
        do
        {
            token.push_back(c);
            ++it;
            if(it != end)
            {
                c = *it;
            }
        } while(it != end && !iswspace(c) && iswalpha(c));

        std::wstring strToken(token.begin(), token.end());
        if(token.size() == 1 && request.punctuationChars.find(token.front()) != request.punctuationChars.end())
        {
            MemoryItem * punctuationItem = new MemoryItem();
            punctuationItem->type = Punctionation;
            punctuationItem->value = strToken;
            result->items.push_back(*punctuationItem);
        }
        else
        {
            MemoryItem * tokenItem = new MemoryItem();
            tokenItem->type = TestableToken;
            tokenItem->value = strToken;
            result->items.push_back(*tokenItem);
        }
    }

    outputBoundary.present(result);
}

