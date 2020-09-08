#ifndef CREATEMEMORYDOCRESULTMODEL_H
#define CREATEMEMORYDOCRESULTMODEL_H

#include <vector>
#include <iostream>
#include "MemoryItem.h"

struct CreateMemoryDocResultModel {
    std::vector<std::vector<MemoryItem*>*> lines;
    ~CreateMemoryDocResultModel()
    {
        /*for(std::vector<MemoryItem*>* line : lines)
        {
            for(MemoryItem * item : *line)
            {
                delete item;
            }
            delete line;
        }*/
    }
};

#endif // CREATEMEMORYDOCRESULTMODEL_H
