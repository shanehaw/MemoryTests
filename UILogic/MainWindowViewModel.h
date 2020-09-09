#ifndef MAINWINDOWVIEWMODEL_H
#define MAINWINDOWVIEWMODEL_H

#include <vector>
#include "MainWindowViewItem.h"

struct MainWindowViewModel
{
    std::vector<std::vector<MainWindowViewItem*>> items;
};

#endif // MAINWINDOWVIEWMODEL_H
