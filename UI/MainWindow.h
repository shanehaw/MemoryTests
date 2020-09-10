#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "MainWindowView.h"
#include "MainWindowPresenter.h"
#include "MainWindowController.h"
#include "CreateMemoryDocUseCase.h"

class MainWindow : public QMainWindow, MainWindowView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
    void render(MainWindowViewModel* model) override;


private slots:
    void newMemDoc();
    void open();
    void save();
    void about();
    void editText();

private:
     QMenu* fileMenu;
     QAction* newAct;
     QAction* openAct;
     QAction* saveAct;
     QAction* exitAct;

     QMenu* editMenu;
     QAction* editTextAct;

     QMenu* helpMenu;
     QAction* aboutAct;
     QAction* aboutQtAct;

     QGridLayout * mainLayout;

     MainWindowPresenter* presenter;
     CreateMemoryDocUseCase* inputBoundary;
     MainWindowController* controller;
};
#endif // MAINWINDOW_H
