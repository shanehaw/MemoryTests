#ifndef MAINWINDOWVIEWSPY_H
#define MAINWINDOWVIEWSPY_H

#include "MainWindowView.h"

class MainWindowViewSpy: public MainWindowView
{
public:
    MainWindowViewSpy() {}
    ~MainWindowViewSpy() {}
    void show(MainWindowViewModel* model) override
    {
        receivedModel = model;
    }
    MainWindowViewModel* receivedModel;
};

#endif // MAINWINDOWVIEWSPY_H
