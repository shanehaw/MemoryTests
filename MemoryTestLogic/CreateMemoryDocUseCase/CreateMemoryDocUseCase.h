#ifndef CREATEMEMORYDOCUSECASE_H
#define CREATEMEMORYDOCUSECASE_H

#include "CreateMemoryDocInputBoundary.h"
#include <cwctype>
#include <vector>
#include <string>
#include <iostream>

class CreateMemoryDocUseCase : public CreateMemoryDocInputBoundary
{
public:
    CreateMemoryDocUseCase();
    ~CreateMemoryDocUseCase();
    void create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary) override;

private:    



    std::set<wchar_t> punctuationChars;
    std::wstring::const_iterator current;
    std::wstring::const_iterator end;
    std::deque<MemoryItem *> buffer;
    std::vector<wchar_t> tokenBuilder;
    std::vector<wchar_t> trailingPunctuationCharactersBuilder;
    wchar_t curChar;

    bool isPunctuationCharacter(wchar_t c);
    MemoryItem * createPunctuationItem(wchar_t punctuationChar);
    MemoryItem * createTokenItem(std::wstring token);

    bool hasNextToken();
    MemoryItem * getNextToken();
    void skipWhitespace();

    bool shouldProcessBuffer();
    MemoryItem * getNextBufferItem();
    void getNextChar();

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

#endif // CREATEMEMORYDOCUSECASE_H
