#ifndef LINEEXTRACTOR_H
#define LINEEXTRACTOR_H

#include <string>
#include <vector>

class LineExtractor
{
public:
    LineExtractor(std::wstring source, wchar_t newLineChar)
    {
        this->source = source;
        this->newLineChar = newLineChar;
    }

    std::vector<std::wstring> extractLines();

private:
    std::wstring source;
    wchar_t newLineChar;
};

#endif // LINEEXTRACTOR_H
