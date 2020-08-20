#include "CreateMemoryDocUseCaseTests.h"

void CreateMemoryDocUseCaseTests::init()
{
    spy = new CreateMemoryDocOutputBoundarySpy();
    useCase = new CreateMemoryDocUseCase();
}

void CreateMemoryDocUseCaseTests::cleanup()
{
    delete useCase;
    delete spy;
}

void CreateMemoryDocUseCaseTests::degenerateCaseSourceIsEmpty()
{
    verifyEmptyResultFor(L"");
}

void CreateMemoryDocUseCaseTests::degenerateCaseSourceIsOnlyWhitespace()
{
    verifyEmptyResultFor(L"      ");
}

void CreateMemoryDocUseCaseTests::degenerateCaseSourceIsOnlyTabs()
{
    verifyEmptyResultFor(L"\t\t\t");
}

void CreateMemoryDocUseCaseTests::degenerateCaseSourceIsOnlyNewLines()
{
    verifyEmptyResultFor(L"\n\n\n");
}

void CreateMemoryDocUseCaseTests::singlePunctionation()
{
    useCase->create(std::wstring(L"."), *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 1);

    MemoryItem item = items.front();
    QVERIFY(item.type == Punctionation);
    QVERIFY(item.value == std::wstring(L"."));
    items.pop_front();

    QVERIFY(items.size() == 0);
}


void CreateMemoryDocUseCaseTests::verifyEmptyResultFor(std::wstring source)
{
    useCase->create(source, *spy);
    QVERIFY(spy->receivedModel != nullptr);

    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 0);
}
