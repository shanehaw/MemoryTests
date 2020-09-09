#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include "MainWindowViewModel.h"

class MainWindowView {
public:
    MainWindowView() {}
    virtual ~MainWindowView() {}
    virtual void show(MainWindowViewModel* model) = 0;
};

#endif // MAINWINDOWVIEW_H
