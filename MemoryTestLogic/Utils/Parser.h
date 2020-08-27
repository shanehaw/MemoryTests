#ifndef PARSER_H
#define PARSER_H

#include "../CreateMemoryDocUseCase/MemoryItem.h"

#include <cwctype>
#include <vector>
#include <string>
#include <deque>
#include <set>
#include <iostream>

class Parser
{
public:    
    Parser(std::wstring src, std::set<wchar_t> puncChars)
    {
        source = src;
        punctuationChars = puncChars;
    }

    bool hasNextToken();
    MemoryItem * getNextToken();

private:
    std::wstring source;
    unsigned long index = 0;

    std::set<wchar_t> punctuationChars;
    std::deque<MemoryItem *> buffer;
    std::vector<wchar_t> tokenBuilder;
    std::vector<wchar_t> trailingPunctuationCharactersBuilder;
    wchar_t curChar;

    bool isPunctuationCharacter(wchar_t c);
    MemoryItem * createPunctuationItem(wchar_t punctuationChar);
    MemoryItem * createTokenItem(std::wstring token);



    void skipWhitespace();

    bool shouldProcessBuffer();
    MemoryItem * getNextBufferItem();
    void moveNextChar();

    MemoryItem * processNextChar();
    MemoryItem * processNextWord();

    void clearBuilders();
    void buildWordToken();
    void processTrailingPunctuationCharacters();

    MemoryItem * createTokenItemFromBuilder();
    bool isEndOfWord();
    bool isNotEndOfSource();
    void addTrailingPunctuationCharactersToTokenBuilder();
};

#endif // PARSER_H
