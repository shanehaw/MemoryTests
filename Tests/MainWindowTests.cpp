#include "MainWindowTests.h"

void MainWindowTests::init()
{
    viewSpy = new MainWindowViewSpy();
}

void MainWindowTests::cleanup()
{
    delete viewSpy;
}

void MainWindowTests::multiLineMultiType()
{
    CreateMemoryDocResultModel result = createResultModel({{L"T:Line1", L"P:!"},{L"T:Line2", L"P:?"}, {L"T:Line3", L"P:;"}});
    CreateMemoryDocInputBoundaryStub inputBoundary(&result);
    MainWindowPresenter presenter(viewSpy);
    MainWindowController ctrl(&presenter, &inputBoundary);
    ctrl.createMemoryDoc(L"", {});
    verifyViewModel({{L"T:Line1", L"L:!"},{L"T:Line2", L"L:?"},{L"T:Line3", L"L:;"}});
}

CreateMemoryDocResultModel MainWindowTests::createResultModel(std::vector<std::vector<std::wstring>> lines)
{
    CreateMemoryDocResultModel result;

    for(std::vector<std::wstring> line: lines)
    {
        std::vector<MemoryItem*> resultLine;
        for(std::wstring item: line)
        {
            MemoryItem* resultItem = new MemoryItem();
            std::wstring type = item.substr(0, 1);
            std::wstring value = item.substr(2);
            if(type == L"P")
            {
                resultItem->type = Punctionation;
            }
            else if(type == L"T")
            {
                resultItem->type = TestableToken;
            }
            resultItem->value = value;
            resultLine.push_back(resultItem);
        }
        result.lines.push_back(resultLine);
    }

    return result;
}

void MainWindowTests::verifyViewModel(std::vector<std::vector<std::wstring>> lines)
{
    QVERIFY(viewSpy->receivedModel != nullptr);
    QVERIFY(viewSpy->receivedModel->items.size() == lines.size());
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<std::wstring> line = lines[i];
        std::vector<MainWindowViewItem*> viewLine = viewSpy->receivedModel->items[i];
        QVERIFY(viewLine.size() == line.size());
        for(size_t j = 0; j < line.size(); j++)
        {
            std::wstring item = line[j];
            MainWindowViewItem * viewItem = viewLine[j];
            std::wstring type = item.substr(0, 1);
            std::wstring value = item.substr(2);
            QVERIFY(viewItem->value == value);
            if(type == L"L")
            {
                QVERIFY(viewItem->type == Label);
            }
            else if(type == L"T")
            {
                QVERIFY(viewItem->type == TextBox);
            }
            else
            {
                QT_THROW(std::exception());
            }
        }
    }
}
