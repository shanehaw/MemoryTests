#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "MainWindowPresenter.h"
#include "CreateMemoryDocInputBoundary.h"

class MainWindowController
{
public:
    MainWindowController(MainWindowPresenter* presenter, CreateMemoryDocInputBoundary* inputBoundary)
    {
        this->presenter = presenter;
        this->inputBoundary = inputBoundary;
    }
    virtual ~MainWindowController() {}
    void createMemoryDoc(std::wstring source, std::set<wchar_t> punctuationChars);

private:
    MainWindowPresenter* presenter;
    CreateMemoryDocInputBoundary* inputBoundary;
};

#endif // MAINWINDOWCONTROLLER_H
