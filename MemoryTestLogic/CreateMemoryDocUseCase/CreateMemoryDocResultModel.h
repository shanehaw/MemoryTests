#ifndef CREATEMEMORYDOCRESULTMODEL_H
#define CREATEMEMORYDOCRESULTMODEL_H

#include <deque>
#include "MemoryItem.h"

struct CreateMemoryDocResultModel {
    std::deque<MemoryItem*> items;
};

#endif // CREATEMEMORYDOCRESULTMODEL_H
