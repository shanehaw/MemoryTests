#include "LineExtractor.h"

std::vector<std::wstring> LineExtractor::extractLines()
{
    std::vector<std::wstring> result;
    std::vector<wchar_t> lineBuffer;
    for(size_t i = 0; i < source.length(); i++)
    {
        wchar_t current = source[i];
        if(current != newLineChar)
        {
            lineBuffer.push_back(current);
        }
        else
        {
            result.push_back(std::wstring(lineBuffer.begin(), lineBuffer.end()));
            lineBuffer.clear();
        }
    }
    result.push_back(std::wstring(lineBuffer.begin(), lineBuffer.end()));
    return result;
}
