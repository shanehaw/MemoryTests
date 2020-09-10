#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include "MainWindowViewModel.h"

class MainWindowView {
public:
    MainWindowView() {}
    virtual ~MainWindowView() {}
    virtual void render(MainWindowViewModel* model) = 0;
};

#endif // MAINWINDOWVIEW_H
