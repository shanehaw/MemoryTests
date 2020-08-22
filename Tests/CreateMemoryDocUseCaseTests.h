#ifndef CREATEMEMORYDOCUSECASETESTS_H
#define CREATEMEMORYDOCUSECASETESTS_H

#include <QtTest/QtTest>
#include "CreateMemoryDocUseCase.h"
#include "CreateMemoryDocOutputBoundarySpy.h"
#include <sstream>
#include <string>
#include <iostream>

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
    void singlePunctuation();
    void multiplePunctuation();
    void singleCharacter();
    void singleWord();
    void multipleWords();
    void punctuationWithWords();

private:
    CreateMemoryDocInputBoundary * useCase;
    CreateMemoryDocOutputBoundarySpy * spy;

    void verifyEmptyResultFor(std::wstring source);
};


#endif // CREATEMEMORYDOCUSECASETESTS_H