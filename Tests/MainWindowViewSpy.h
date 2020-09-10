#ifndef MAINWINDOWVIEWSPY_H
#define MAINWINDOWVIEWSPY_H

#include "MainWindowView.h"

class MainWindowViewSpy: public MainWindowView
{
public:
    MainWindowViewSpy() {}
    ~MainWindowViewSpy()
    {
        if(receivedModel != nullptr)
        {
            delete receivedModel;
            receivedModel = nullptr;
        }
    }
    void show(MainWindowViewModel* model) override
    {
        receivedModel = model;
    }
    MainWindowViewModel* receivedModel = nullptr;
};

#endif // MAINWINDOWVIEWSPY_H
