#include "CreateMemoryDocUseCaseTests.h"

//test hooks
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

//tests
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

void CreateMemoryDocUseCaseTests::singlePunctuation()
{
    CreateMemoryDocRequestModel request;
    request.source = L".";
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'.');

    useCase->create(request, *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 1);

    MemoryItem item = items.front();
    QVERIFY(item.type == Punctionation);
    QVERIFY(item.value == std::wstring(L"."));
    items.pop_front();

    QVERIFY(items.size() == 0);
}

void CreateMemoryDocUseCaseTests::multiplePunctuation()
{
    CreateMemoryDocRequestModel request;
    request.source = L"...";
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'.');

    useCase->create(request, *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 3);

    int counter = 3;
    while(--counter >= 0)
    {
        MemoryItem item = items.front();
        QVERIFY(item.type == Punctionation);
        QVERIFY(item.value == std::wstring(L"."));
        items.pop_front();
    }

    QVERIFY(items.size() == 0);
}

void CreateMemoryDocUseCaseTests::singleCharacter()
{
    CreateMemoryDocRequestModel request;
    request.source = L"a";
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'.');

    useCase->create(request, *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 1);

    MemoryItem item = items.front();
    QVERIFY(item.type == TestableToken);
    QVERIFY(item.value == std::wstring(L"a"));
    items.pop_front();

    QVERIFY(items.size() == 0);
}

void CreateMemoryDocUseCaseTests::singleWord()
{
    CreateMemoryDocRequestModel request;
    request.source = L"word";
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'.');

    useCase->create(request, *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 1);

    MemoryItem item = items.front();
    QVERIFY(item.type == TestableToken);
    QVERIFY(item.value == std::wstring(L"word"));
    items.pop_front();

    QVERIFY(items.size() == 0);
}

void CreateMemoryDocUseCaseTests::multipleWords()
{
    CreateMemoryDocRequestModel request;
    request.source = L"multiple words";
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'.');

    useCase->create(request, *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 2);

    MemoryItem item1 = items.front();
    QVERIFY(item1.type == TestableToken);
    QVERIFY(item1.value == std::wstring(L"multiple"));
    items.pop_front();

    MemoryItem item2 = items.front();
    QVERIFY(item2.type == TestableToken);
    QVERIFY(item2.value == std::wstring(L"words"));
    items.pop_front();

    QVERIFY(items.size() == 0);
}

void CreateMemoryDocUseCaseTests::punctuationWithWords()
{
    CreateMemoryDocRequestModel request;
    request.source = L"This contains \"multiple words\"!?#";
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'\"');
    request.punctuationChars.insert(L'!');
    request.punctuationChars.insert(L'?');
    request.punctuationChars.insert(L'#');

    useCase->create(request, *spy);
    std::deque<MemoryItem> items = spy->receivedModel->items;

    QVERIFY(items.size() == 8);

    MemoryItem item1 = items.front();
    QVERIFY(item1.type == TestableToken);
    QVERIFY(item1.value == std::wstring(L"This"));
    items.pop_front();

    MemoryItem item2 = items.front();
    QVERIFY(item2.type == TestableToken);
    QVERIFY(item2.value == std::wstring(L"contains"));
    items.pop_front();

    /*MemoryItem item3 = items.front();
    QVERIFY(item3.type == TestableToken);
    QVERIFY(item3.value == std::wstring(L"\""));
    items.pop_front();*/

    //TODO: This needs fixing
    MemoryItem item4 = items.front();
    QVERIFY(item4.type == TestableToken);
    QVERIFY(item4.value == std::wstring(L"\"multiple"));
    items.pop_front();

    MemoryItem item5 = items.front();
    QVERIFY(item5.type == TestableToken);
    QVERIFY(item5.value == std::wstring(L"words"));
    items.pop_front();

    MemoryItem item6 = items.front();
    QVERIFY(item6.type == Punctionation);
    QVERIFY(item6.value == std::wstring(L"\""));
    items.pop_front();

    MemoryItem item7 = items.front();
    QVERIFY(item7.type == Punctionation);
    QVERIFY(item7.value == std::wstring(L"!"));
    items.pop_front();

    MemoryItem item8 = items.front();
    QVERIFY(item8.type == Punctionation);
    QVERIFY(item8.value == std::wstring(L"?"));
    items.pop_front();

    MemoryItem item9 = items.front();
    QVERIFY(item9.type == Punctionation);
    QVERIFY(item9.value == std::wstring(L"#"));
    items.pop_front();

    QVERIFY(items.size() == 0);
}

//helpers¸
void CreateMemoryDocUseCaseTests::verifyEmptyResultFor(std::wstring source)
{
    CreateMemoryDocRequestModel request;
    request.source = source;
    request.punctuationChars = std::set<wchar_t>();
    request.punctuationChars.insert(L'.');
    useCase->create(request, *spy);
    QVERIFY(spy->receivedModel != nullptr);

    std::deque<MemoryItem> items = spy->receivedModel->items;
    QVERIFY(items.size() == 0);
}
