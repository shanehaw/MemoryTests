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
        //handle white space
        if(iswspace(c))
        {
            ++it;
            continue;
        }      

        //handle punctuation
        if(request.punctuationChars.find(c) != request.punctuationChars.end()) {
            MemoryItem * punctuationItem = new MemoryItem();
            punctuationItem->type = Punctionation;
            punctuationItem->value = c;
            result->items.push_back(*punctuationItem);
            ++it;
            continue;
        }

        //handle words
        std::vector<wchar_t> token;
        do
        {
            token.push_back(c);
            ++it;
            if(it != end)
            {
                c = *it;
            }
        } while(it != end
                && !iswspace(c)
                && request.punctuationChars.find(c) == request.punctuationChars.end());

        std::wstring strToken(token.begin(), token.end());        
        MemoryItem * tokenItem = new MemoryItem();
        tokenItem->type = TestableToken;
        tokenItem->value = strToken;
        result->items.push_back(*tokenItem);
    }

    outputBoundary.present(result);
}

