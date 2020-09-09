#include "MainWindowTests.h"

void MainWindowTests::init()
{
    viewSpy = new MainWindowViewSpy();
}

void MainWindowTests::cleanup()
{
    delete viewSpy;
}

void MainWindowTests::punctuation()
{
    CreateMemoryDocResultModel result;
    MemoryItem * punctuation = new MemoryItem();
    punctuation->type = Punctionation;
    punctuation->value = L".";
    result.lines = {{ punctuation }};
    CreateMemoryDocInputBoundaryStub inputBoundary(&result);

    MainWindowPresenter presenter(viewSpy);
    MainWindowController ctrl(&presenter, &inputBoundary);

    ctrl.createMemoryDoc(L".", {L'.'});

    QVERIFY(viewSpy->receivedModel->items.size() == 1); //1 Line
    QVERIFY(viewSpy->receivedModel->items[0].size() == 1); //1 Item
    QVERIFY(viewSpy->receivedModel->items[0][0]->type == Label);
    QVERIFY(viewSpy->receivedModel->items[0][0]->value == L".");
}
