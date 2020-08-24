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
    std::wstring source;
    std::set<wchar_t> punctuationChars;
    bool isPunctuationCharacter(wchar_t c);
};

#endif // CREATEMEMORYDOCUSECASE_H
