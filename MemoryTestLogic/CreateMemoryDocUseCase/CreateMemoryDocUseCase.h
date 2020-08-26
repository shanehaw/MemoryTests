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
    std::deque<MemoryItem> buffer;

    bool isPunctuationCharacter(wchar_t c);
    MemoryItem * createPunctuationItem(wchar_t punctuationChar);
    MemoryItem * createTokenItem(std::wstring token);

    bool hasNextToken();
    void getNextToken(CreateMemoryDocResultModel& result);
    void skipWhitespace();
};

#endif // CREATEMEMORYDOCUSECASE_H
