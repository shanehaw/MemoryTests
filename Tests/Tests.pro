QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../MemoryTestLogic/CreateMemoryDocUseCase/ \
    ../MemoryTestLogic/Utils/

LIBS += -L ../MemoryTestLogic -l MemoryTestLogic

SOURCES +=  \
    CreateMemoryDocOutputBoundarySpy.cpp \
    CreateMemoryDocUseCaseTests.cpp \
    TestRunner.cpp

HEADERS += \
    CreateMemoryDocOutputBoundarySpy.h \
    CreateMemoryDocUseCaseTests.h
