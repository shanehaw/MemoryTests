#include "CreateMemoryDocUseCase.h"

CreateMemoryDocUseCase::CreateMemoryDocUseCase()
{

}

CreateMemoryDocUseCase::~CreateMemoryDocUseCase()
{

}

void CreateMemoryDocUseCase::create(std::wstring source, CreateMemoryDocOutputBoundary& outputBoundary)
{    
    CreateMemoryDocResultModel * result = new CreateMemoryDocResultModel();
    for(wchar_t const &c: source)
    {
        if(iswspace(c)) {
            continue;
        }

        if(c == L'.') {
            MemoryItem * punctuationItem = new MemoryItem();
            punctuationItem->type = Punctionation;
            punctuationItem->value = L".";
            result->items.push_back(*punctuationItem);
        }
    }

    outputBoundary.present(result);
}

