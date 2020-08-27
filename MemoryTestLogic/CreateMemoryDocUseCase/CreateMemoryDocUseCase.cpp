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
    return isNotEndOfSource() || shouldProcessBuffer();
}

MemoryItem * CreateMemoryDocUseCase::getNextToken()
{
    if(shouldProcessBuffer())
    {
        return getNextBufferItem();
    }
    return processNextChar();
}

MemoryItem * CreateMemoryDocUseCase::processNextChar()
{
    skipWhitespace();
    getNextChar();    
    if(isPunctuationCharacter(curChar)) {
        return createPunctuationItem(curChar);
    }
    return processNextWord();
}

MemoryItem * CreateMemoryDocUseCase::processNextWord()
{
    clearBuilders();
    buildWordToken();
    processTrailingPunctuationCharacters();
    return createTokenItemFromBuilder();
}

void CreateMemoryDocUseCase::clearBuilders()
{
    tokenBuilder.clear();
    trailingPunctuationCharactersBuilder.clear();
}

void CreateMemoryDocUseCase::buildWordToken()
{
    tokenBuilder.push_back(curChar);
    while(isNotEndOfSource())
    {
        getNextChar();
        if(isEndOfWord()) break;

        if(isPunctuationCharacter(curChar))
        {
            trailingPunctuationCharactersBuilder.push_back(curChar);
        }
        else
        {
            addTrailingPunctuationCharactersToTokenBuilder();
            tokenBuilder.push_back(curChar);
        }
    }
}

bool CreateMemoryDocUseCase::isEndOfWord()
{
    return iswspace(curChar);
}

void CreateMemoryDocUseCase::processTrailingPunctuationCharacters()
{
    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        buffer.push_back(createPunctuationItem(*tpc));
    }
}

MemoryItem * CreateMemoryDocUseCase::createTokenItemFromBuilder()
{
    std::wstring strToken(tokenBuilder.begin(), tokenBuilder.end());
    return createTokenItem(strToken);
}

void CreateMemoryDocUseCase::addTrailingPunctuationCharactersToTokenBuilder()
{
    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        wchar_t tpchar = *tpc;
        tokenBuilder.push_back(tpchar);
    }
    trailingPunctuationCharactersBuilder.clear();
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

void CreateMemoryDocUseCase::getNextChar()
{    
    curChar = *current;
    if(current != end)
    {
        ++current;
    }    
}

bool CreateMemoryDocUseCase::isNotEndOfSource()
{
    return current != end;
}
