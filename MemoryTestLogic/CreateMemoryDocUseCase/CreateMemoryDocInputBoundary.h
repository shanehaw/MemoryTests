#ifndef CREATEMEMORYDOCINPUTBOUNDARY_H
#define CREATEMEMORYDOCINPUTBOUNDARY_H

#include "CreateMemoryDocOutputBoundary.h"
#include <string>

class CreateMemoryDocInputBoundary {
public:
    CreateMemoryDocInputBoundary() {}
    virtual ~CreateMemoryDocInputBoundary() {}
    virtual void create(std::wstring source, CreateMemoryDocOutputBoundary& outputBoundary) = 0;
};


#endif // CREATEMEMORYDOCINPUTBOUNDARY_H
