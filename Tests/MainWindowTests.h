#ifndef MAINWINDOWTESTS_H
#define MAINWINDOWTESTS_H

#include <QtTest/QtTest>
#include "CreateMemoryDocInputBoundaryStub.h"
#include "MainWindowViewSpy.h"
#include "MainWindowPresenter.h"
#include "MainWindowController.h"

class MainWindowTests : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void multiLineMultiType();

private:
    MainWindowViewSpy* viewSpy;

    CreateMemoryDocResultModel createResultModel(std::vector<std::vector<std::wstring>> lines);
    void verifyViewModel(std::vector<std::vector<std::wstring>> lines);
};

#endif // MAINWINDOWTESTS_H
