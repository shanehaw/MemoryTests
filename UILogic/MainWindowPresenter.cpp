#include "MainWindowPresenter.h"

void MainWindowPresenter::present(CreateMemoryDocResultModel * resultModel)
{
    MainWindowViewModel * result = new MainWindowViewModel();
    for(std::vector<MemoryItem*> line: resultModel->lines)
    {
        std::vector<MainWindowViewItem*> viewLine;
        for(MemoryItem* memoryItem: line)
        {
            MainWindowViewItem* viewItem = new MainWindowViewItem();
            if(memoryItem->type == Punctionation)
            {
                viewItem->type = Label;
            }
            else
            {
                viewItem->type = TextBox;
            }

            viewItem->value = memoryItem->value;
            viewLine.push_back(viewItem);

            //delete memoryItem;
        }
        result->items.push_back(viewLine);
    }
    //delete resultModel;
    view->render(result);
}
