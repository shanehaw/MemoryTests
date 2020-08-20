QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../MemoryTestLogic/CreateMemoryDocUseCase

LIBS += -L ../../build-MemoryTests-Desktop_Qt_5_15_0_GCC_64bit-Debug/MemoryTestLogic -l MemoryTestLogic

SOURCES +=  \
    CreateMemoryDocOutputBoundarySpy.cpp \
    CreateMemoryDocUseCaseTests.cpp \
    TestRunner.cpp

HEADERS += \
    CreateMemoryDocOutputBoundarySpy.h \
    CreateMemoryDocUseCaseTests.h
