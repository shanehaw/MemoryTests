#ifndef CREATEMEMORYDOCUSECASE_H
#define CREATEMEMORYDOCUSECASE_H

#include "CreateMemoryDocInputBoundary.h"
#include "../Utils/LineParser.h"
#include "../Utils/LineExtractor.h"

class CreateMemoryDocUseCase : public CreateMemoryDocInputBoundary
{
public:
    CreateMemoryDocUseCase() { }
    ~CreateMemoryDocUseCase() { }
    void create(CreateMemoryDocRequestModel& request, CreateMemoryDocOutputBoundary& outputBoundary) override;

private:
    std::vector<MemoryItem*> parseLine(std::wstring line, std::set<wchar_t> punctuationChars);
};

#endif // CREATEMEMORYDOCUSECASE_H
