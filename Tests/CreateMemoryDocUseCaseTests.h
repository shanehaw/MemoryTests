#ifndef CREATEMEMORYDOCUSECASETESTS_H
#define CREATEMEMORYDOCUSECASETESTS_H

#include <QtTest/QtTest>
#include "CreateMemoryDocUseCase.h"
#include "CreateMemoryDocOutputBoundarySpy.h"

class CreateMemoryDocUseCaseTests: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();        
    void degenerateCaseSourceIsEmpty();
    void degenerateCaseSourceIsOnlyWhitespace();
    void degenerateCaseSourceIsOnlyTabs();
    void degenerateCaseSourceIsOnlyNewLines();
    void singlePunctionation();

private:
    CreateMemoryDocInputBoundary * useCase;
    CreateMemoryDocOutputBoundarySpy * spy;

    void verifyEmptyResultFor(std::wstring source);
};


#endif // CREATEMEMORYDOCUSECASETESTS_H
