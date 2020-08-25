#include "CreateMemoryDocUseCase.h"

CreateMemoryDocUseCase::CreateMemoryDocUseCase()
{

}

CreateMemoryDocUseCase::~CreateMemoryDocUseCase()
{

}

void CreateMemoryDocUseCase::create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary)
{    
    source = request.source;
    punctuationChars = request.punctuationChars;


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
        if(isPunctuationCharacter(c)) {            
            result->items.push_back(*createPunctuationItem(c));
            ++it;
            continue;
        }

        //handle words
        std::vector<wchar_t> token;
        std::vector<wchar_t> trailingPuncChars;
        do
        {            
            if(isPunctuationCharacter(c))
            {
                trailingPuncChars.push_back(c);
            }
            else
            {
                for(auto tpc = trailingPuncChars.begin(); tpc != trailingPuncChars.end(); ++tpc)
                {
                    wchar_t tpchar = *tpc;
                    token.push_back(tpchar);
                }
                trailingPuncChars.clear();
                token.push_back(c);
            }
            c = *(++it);
        } while(it != end && !iswspace(c));

        std::wstring strToken(token.begin(), token.end());        
        result->items.push_back(*createTokenItem(strToken));

        for(auto tpc = trailingPuncChars.begin(); tpc != trailingPuncChars.end(); ++tpc)
        {
            result->items.push_back(*createPunctuationItem(*tpc));
        }
    }

    outputBoundary.present(result);
}

bool CreateMemoryDocUseCase::isPunctuationCharacter(wchar_t c)
{
    return punctuationChars.find(c) != punctuationChars.end();
}

MemoryItem * CreateMemoryDocUseCase::createPunctuationItem(wchar_t punctuationChar)
{
    MemoryItem * punctuationItem = new MemoryItem();
    punctuationItem->type = Punctionation;
    punctuationItem->value = punctuationChar;
    return punctuationItem;
}

MemoryItem * CreateMemoryDocUseCase::createTokenItem(std::wstring token)
{
    MemoryItem * tokenItem = new MemoryItem();
    tokenItem->type = TestableToken;
    tokenItem->value = token;
    return tokenItem;
}
