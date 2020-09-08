#include "Parser.h"

bool Parser::hasNextToken()
{
    skipWhitespace();
    return isNotEndOfSource() || shouldProcessBuffer();
}

MemoryItem * Parser::getNextToken()
{
    if(shouldProcessBuffer())
    {
        return getNextBufferItem();
    }
    return processNextChar();
}

MemoryItem * Parser::processNextChar()
{
    skipWhitespace();    
    MemoryItem * result = isPunctuationCharacter(curChar) 
       ? createPunctuationItem(curChar)
       : processNextWord();    
    moveNextChar();
    return result;
}

MemoryItem * Parser::processNextWord()
{
    clearBuilders();
    buildWordToken();
    processTrailingPunctuationCharacters();
    return createTokenItemFromBuilder();
}

void Parser::clearBuilders()
{
    tokenBuilder.clear();
    trailingPunctuationCharactersBuilder.clear();
}

void Parser::buildWordToken()
{
    do
    {
        if(isPunctuationCharacter(curChar))
        {
            trailingPunctuationCharactersBuilder.push_back(curChar);
        }
        else
        {
            addTrailingPunctuationCharactersToTokenBuilder();
            tokenBuilder.push_back(curChar);
        }
        moveNextChar();
    } while(isNotEndOfSource() && isNotEndOfWord());
}

bool Parser::isNotEndOfWord()
{
    return !iswspace(curChar);
}

void Parser::processTrailingPunctuationCharacters()
{
    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        buffer.push_back(createPunctuationItem(*tpc));
    }
}

MemoryItem * Parser::createTokenItemFromBuilder()
{
    std::wstring strToken(tokenBuilder.begin(), tokenBuilder.end());
    return createTokenItem(strToken);
}

void Parser::addTrailingPunctuationCharactersToTokenBuilder()
{
    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        wchar_t tpchar = *tpc;
        tokenBuilder.push_back(tpchar);
    }
    trailingPunctuationCharactersBuilder.clear();
}

void Parser::skipWhitespace()
{
    curChar = source[index];
    while(iswspace(curChar))
    {
        curChar = source[++index];
    }
}

bool Parser::shouldProcessBuffer()
{
    return buffer.size() > 0;
}

MemoryItem * Parser::getNextBufferItem()
{
    MemoryItem * result = buffer.front();
    buffer.pop_front();
    return result;
}

void Parser::moveNextChar()
{
    if(index < source.length())
    {
        curChar = source[++index];
    }
}

bool Parser::isNotEndOfSource()
{
    return index < source.length();
}

bool Parser::isPunctuationCharacter(wchar_t c)
{
    return punctuationChars.find(c) != punctuationChars.end();
}

MemoryItem * Parser::createPunctuationItem(wchar_t punctuationChar)
{
    MemoryItem * punctuationItem = new MemoryItem();
    punctuationItem->type = Punctionation;
    punctuationItem->value = punctuationChar;
    return punctuationItem;
}

MemoryItem * Parser::createTokenItem(std::wstring token)
{
    MemoryItem * tokenItem = new MemoryItem();
    tokenItem->type = TestableToken;
    tokenItem->value = token;
    return tokenItem;
}
