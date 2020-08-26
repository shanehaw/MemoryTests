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
        MemoryItem * item = getNextToken();
        result->items.push_back(*item);
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

MemoryItem * CreateMemoryDocUseCase::getNextToken()
{
    if(shouldProcessBuffer())
    {
        return getNextBufferItem();
    }

    skipWhitespace();
    wchar_t c = getNextChar();
    /*std::wcout << L"outer c = '" << c << L"'" << std::endl;*/
    if(isPunctuationCharacter(c)) {        
        return createPunctuationItem(c);;
    }

    tokenBuilder.clear();
    tokenBuilder.push_back(c);
    trailingPunctuationCharactersBuilder.clear();
    while(current != end)
    {
        c = getNextChar();
        /*std::wcout << L"inner c = '" << c << L"'" << std::endl;*/

        if(iswspace(c)) break;

        if(isPunctuationCharacter(c))
        {
            trailingPunctuationCharactersBuilder.push_back(c);
        }
        else
        {
            for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
            {
                wchar_t tpchar = *tpc;
                tokenBuilder.push_back(tpchar);
            }
            trailingPunctuationCharactersBuilder.clear();
            tokenBuilder.push_back(c);
        }
    }

    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        buffer.push_back(createPunctuationItem(*tpc));
    }

    std::wstring strToken(tokenBuilder.begin(), tokenBuilder.end());
    return createTokenItem(strToken);
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

bool CreateMemoryDocUseCase::shouldProcessBuffer()
{
    return buffer.size() > 0;
}

MemoryItem * CreateMemoryDocUseCase::getNextBufferItem()
{
    MemoryItem * result = buffer.front();
    buffer.pop_front();
    return result;
}

wchar_t CreateMemoryDocUseCase::getNextChar()
{    
    wchar_t result = *current;
    if(current != end)
    {
        ++current;
    }
    return result;
}
