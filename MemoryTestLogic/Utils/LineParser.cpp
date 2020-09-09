#include "LineParser.h"

bool LineParser::hasNextToken()
{
    skipWhitespace();
    return isNotEndOfSource() || shouldProcessBuffer();
}

MemoryItem * LineParser::getNextToken()
{
    if(shouldProcessBuffer())
    {
        return getNextBufferItem();
    }
    return processNextChar();
}

MemoryItem * LineParser::processNextChar()
{
    skipWhitespace();    
    MemoryItem * result = isPunctuationCharacter(curChar) 
       ? createPunctuationItem(curChar)
       : processNextWord();    
    moveNextChar();
    return result;
}

MemoryItem * LineParser::processNextWord()
{
    clearBuilders();
    buildWordToken();
    processTrailingPunctuationCharacters();
    return createTokenItemFromBuilder();
}

void LineParser::clearBuilders()
{
    tokenBuilder.clear();
    trailingPunctuationCharactersBuilder.clear();
}

void LineParser::buildWordToken()
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

bool LineParser::isNotEndOfWord()
{
    return !iswspace(curChar);
}

void LineParser::processTrailingPunctuationCharacters()
{
    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        buffer.push_back(createPunctuationItem(*tpc));
    }
}

MemoryItem * LineParser::createTokenItemFromBuilder()
{
    std::wstring strToken(tokenBuilder.begin(), tokenBuilder.end());
    return createTokenItem(strToken);
}

void LineParser::addTrailingPunctuationCharactersToTokenBuilder()
{
    for(auto tpc = trailingPunctuationCharactersBuilder.begin(); tpc != trailingPunctuationCharactersBuilder.end(); ++tpc)
    {
        wchar_t tpchar = *tpc;
        tokenBuilder.push_back(tpchar);
    }
    trailingPunctuationCharactersBuilder.clear();
}

void LineParser::skipWhitespace()
{
    curChar = source[index];
    while(iswspace(curChar))
    {
        curChar = source[++index];
    }
}

bool LineParser::shouldProcessBuffer()
{
    return buffer.size() > 0;
}

MemoryItem * LineParser::getNextBufferItem()
{
    MemoryItem * result = buffer.front();
    buffer.pop_front();
    return result;
}

void LineParser::moveNextChar()
{
    if(index < source.length())
    {
        curChar = source[++index];
    }
}

bool LineParser::isNotEndOfSource()
{
    return index < source.length();
}

bool LineParser::isPunctuationCharacter(wchar_t c)
{
    return punctuationChars.find(c) != punctuationChars.end();
}

MemoryItem * LineParser::createPunctuationItem(wchar_t punctuationChar)
{
    MemoryItem * punctuationItem = new MemoryItem();
    punctuationItem->type = Punctionation;
    punctuationItem->value = punctuationChar;
    return punctuationItem;
}

MemoryItem * LineParser::createTokenItem(std::wstring token)
{
    MemoryItem * tokenItem = new MemoryItem();
    tokenItem->type = TestableToken;
    tokenItem->value = token;
    return tokenItem;
}
