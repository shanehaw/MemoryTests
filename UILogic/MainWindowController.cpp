#include "MainWindowController.h"

void MainWindowController::createMemoryDoc(std::wstring source, std::set<wchar_t> punctuationChars)
{
    CreateMemoryDocRequestModel request;
    request.source = source;
    request.punctuationChars = punctuationChars;
    inputBoundary->create(request, *presenter);
}
