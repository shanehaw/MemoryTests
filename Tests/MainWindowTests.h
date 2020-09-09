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
    void punctuation();

private:
    MainWindowViewSpy* viewSpy;
};

#endif // MAINWINDOWTESTS_H
