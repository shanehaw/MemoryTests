#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include "CreateMemoryDocOutputBoundary.h"
#include "MainWindowView.h"

class MainWindowPresenter: public CreateMemoryDocOutputBoundary
{
public:
    MainWindowPresenter(MainWindowView* view)
    {
        this->view = view;
    }
    virtual ~MainWindowPresenter() {}
    void present(CreateMemoryDocResultModel *result) override;

private:
    MainWindowView * view;
};

#endif // MAINWINDOWPRESENTER_H
