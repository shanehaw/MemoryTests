QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../MemoryTestLogic/CreateMemoryDocUseCase/ \
    ../MemoryTestLogic/Utils/ \
    ../UILogic/

LIBS += -L../MemoryTestLogic -lMemoryTestLogic
LIBS += -L../UILogic -lUILogic

SOURCES +=  \
    CreateMemoryDocOutputBoundarySpy.cpp \
    CreateMemoryDocUseCaseTests.cpp \
    MainWindowTests.cpp \
    TestRunner.cpp

HEADERS += \
    CreateMemoryDocInputBoundaryStub.h \
    CreateMemoryDocOutputBoundarySpy.h \
    CreateMemoryDocUseCaseTests.h \
    MainWindowTests.h \
    MainWindowViewSpy.h
