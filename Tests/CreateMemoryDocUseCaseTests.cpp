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
    CreateMemoryDocRequestModel request = createRequest(
        L".",
        { L'.' });
    useCase->create(request, *spy);
    verifyResults({{ L"P:." }});
}

void CreateMemoryDocUseCaseTests::multiplePunctuation()
{
    CreateMemoryDocRequestModel request = createRequest(
        L"...",
        { L'.' });
    useCase->create(request, *spy);
    verifyResults({{L"P:.", L"P:.", L"P:."}});
}

void CreateMemoryDocUseCaseTests::singleCharacter()
{
    CreateMemoryDocRequestModel request = createRequest(
        L"a",
        { L'.' });
    useCase->create(request, *spy);
    verifyResults({{L"T:a"}});
}

void CreateMemoryDocUseCaseTests::singleWord()
{    
    CreateMemoryDocRequestModel request = createRequest(
                L"word",
                { L'.' });
    useCase->create(request, *spy);
    verifyResults({{L"T:word"}});
}

void CreateMemoryDocUseCaseTests::multipleWords()
{
    CreateMemoryDocRequestModel request = createRequest(
                L"multiple words",
                { L'.' });
    useCase->create(request, *spy);
    verifyResults({{L"T:multiple", L"T:words"}});
}

void CreateMemoryDocUseCaseTests::punctuationWithWords()
{
    CreateMemoryDocRequestModel request = createRequest(
                L"This contains \"multiple words\"!?#",
                { L'\"', L'!', L'?', L'#' });
    useCase->create(request, *spy);
    verifyResults({{L"T:This", L"T:contains", L"P:\"", L"T:multiple", L"T:words", L"P:\"", L"P:!", L"P:?", L"P:#"}});
}

void CreateMemoryDocUseCaseTests::punctuationInWords()
{
    CreateMemoryDocRequestModel request = createRequest(
                L"Let's go",
                { L'\'' });
    useCase->create(request, *spy);
    verifyResults({{L"T:Let\'s", L"T:go"}});
}

void CreateMemoryDocUseCaseTests::punctuationOnEndButNotEndOfSource()
{
    CreateMemoryDocRequestModel request = createRequest(
                L"Let's go! I said.",
                { L'\'', L'.', L'!' });
    useCase->create(request, *spy);
    verifyResults({{L"T:Let\'s", L"T:go", L"P:!", L"T:I", L"T:said", L"P:."}});
}

//helpers¸
void CreateMemoryDocUseCaseTests::verifyEmptyResultFor(std::wstring source)
{
    CreateMemoryDocRequestModel request = createRequest(
        source,
        { L'.' });
    useCase->create(request, *spy);
    QVERIFY(spy->receivedModel != nullptr);

    std::vector<std::vector<MemoryItem *>*> lines = spy->receivedModel->lines;
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<MemoryItem*> * items = lines[i];
        QVERIFY(items->size() == 0);
    }
}

void CreateMemoryDocUseCaseTests::verifyResults(std::vector<std::vector<std::wstring>> expectationLines)
{
    //std::wcout << L"Start of verifyResults" << std::endl;
    CreateMemoryDocResultModel * model = spy->receivedModel;    
    QVERIFY(model != nullptr);

    //std::wcout << L"Result is not null" << std::endl;
    CreateMemoryDocResultModel result = *model;   

    /*
    for(std::vector<MemoryItem*> * line : result.lines)
    {
        std::wcout << L"found line" << std::endl;
        for(MemoryItem * item : *line)
        {
            std::wcout << L"found item" << std::endl;
            std::wcout << L"'" << item->value << L"'\n";
        }
    }
    */

    QVERIFY(result.lines.size() == expectationLines.size());
    for(size_t i = 0; i < expectationLines.size(); i++)
    {
        std::vector<MemoryItem*>* actualLine = result.lines[i];
        std::vector<std::wstring> expectedLine = expectationLines[i];
        for(size_t j = 0; j < expectedLine.size(); j++)
        {
            std::wstring expected = expectedLine[j];
            MemoryItem* actual = (*actualLine)[j];
            std::wstring type = expected.substr(0, 1);
            std::wstring value = expected.substr(2);

            if(type == L"P")
            {
                QVERIFY(actual->type == Punctionation);
                QVERIFY(actual->value == std::wstring(value));
            }
            else if(type == L"T")
            {
                QVERIFY(actual->type == TestableToken);
                QVERIFY(actual->value == std::wstring(value));
            }
            else
            {
                //Surely there is a better way to do this?
                QVERIFY(1 == 2);
            }
        }
    }
}

CreateMemoryDocRequestModel CreateMemoryDocUseCaseTests::createRequest(std::wstring source, std::vector<wchar_t> punctuationMarks)
{
    CreateMemoryDocRequestModel request;
    request.source = source;
    request.punctuationChars = std::set<wchar_t>();

    for(auto it = punctuationMarks.begin(); it < punctuationMarks.end(); it++) {
        wchar_t nextChar = *it;
        request.punctuationChars.insert(nextChar);
    }

    return request;
}

std::string CreateMemoryDocUseCaseTests::convertToString(std::wstring source)
{
    return std::string(source.begin(), source.end());
}
