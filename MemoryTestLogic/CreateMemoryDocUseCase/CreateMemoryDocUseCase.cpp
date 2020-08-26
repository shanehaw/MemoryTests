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
    punctuationChars = request.punctuationChars;
    current = request.source.cbegin();
    end = request.source.cend();
    while(hasNextToken())
    {        
        getNextToken(*result);
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

bool CreateMemoryDocUseCase::hasNextToken()
{
    skipWhitespace();
    return current != end || buffer.size() > 0;
}

void CreateMemoryDocUseCase::getNextToken(CreateMemoryDocResultModel& fooResult)
{
    MemoryItem * result = nullptr;
    if(buffer.size() > 0)
    {
        MemoryItem item = buffer.front();
        result = &item;
        buffer.pop_front();
    }

    if(result == nullptr && hasNextToken())
    {
        wchar_t c = *current;

        if(isPunctuationCharacter(c)) {
            result = createPunctuationItem(c);
            ++current;
        }
        else
        {
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
                c = *(++current);
            } while(current != end && !iswspace(c));

            std::wstring strToken(token.begin(), token.end());
            result = createTokenItem(strToken);

            for(auto tpc = trailingPuncChars.begin(); tpc != trailingPuncChars.end(); ++tpc)
            {
                buffer.push_back(*createPunctuationItem(*tpc));
            }
        }
    }
    fooResult.items.push_back(*result);
}

void CreateMemoryDocUseCase::skipWhitespace()
{
    wchar_t c = *current;
    while(iswspace(c))
    {
        ++current;
        c = *current;
    }
}
