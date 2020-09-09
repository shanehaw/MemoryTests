#ifndef MAINWINDOWVIEWITEM_H
#define MAINWINDOWVIEWITEM_H

#include "MemoryItemViewType.h"
#include <string>

struct MainWindowViewItem
{
    MemoryItemViewType type;
    std::wstring value;
};

#endif // MAINWINDOWVIEWITEM_H
