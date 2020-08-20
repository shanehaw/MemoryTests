#ifndef MEMORYITEM_H
#define MEMORYITEM_H

#include "MemoryItemType.h"
#include <string>

struct MemoryItem {
    MemoryItemType type;
    std::wstring value;
};

#endif // MEMORYITEM_H
