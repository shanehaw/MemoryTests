#ifndef CREATEMEMORYDOCRESULTMODEL_H
#define CREATEMEMORYDOCRESULTMODEL_H

#include <vector>
#include <iostream>
#include "MemoryItem.h"

struct CreateMemoryDocResultModel {
    std::vector<std::vector<MemoryItem*>> lines;
};

#endif // CREATEMEMORYDOCRESULTMODEL_H
