#ifndef CREATEMEMORYDOCREQUESTMODEL_H
#define CREATEMEMORYDOCREQUESTMODEL_H

#include <string>
#include <set>

struct CreateMemoryDocRequestModel
{
    std::wstring source;
    std::set<wchar_t> punctuationChars;
};

#endif // CREATEMEMORYDOCREQUESTMODEL_H
