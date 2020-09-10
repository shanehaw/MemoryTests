#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget * centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout;
    centralWidget->setLayout(mainLayout);

    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new Memory Document"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newMemDoc);
    fileMenu->addAction(newAct);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing Memory Document"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the Memory Document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));

    editTextAct = new QAction(tr("Edit &Text"));
    editTextAct->setStatusTip(tr("Edit the current Memory Document Text / Punctuation"));
    connect(editTextAct, &QAction::triggered, this, &MainWindow::editText);
    editMenu->addAction(editTextAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
    helpMenu->addAction(aboutAct);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    helpMenu->addAction(aboutQtAct);

    QDesktopWidget desktopWidget;
    int length = desktopWidget.height() * 0.7;

    setWindowTitle("Memory Test");
    setMinimumSize(length, length);
    resize(length, length);


    presenter = new MainWindowPresenter(this);
    inputBoundary = new CreateMemoryDocUseCase();
    controller = new MainWindowController(presenter, inputBoundary);
}

MainWindow::~MainWindow()
{
    delete presenter;
    delete inputBoundary;
    delete controller;
}

void MainWindow::render(MainWindowViewModel* model)
{
    /*QLayoutItem* item;
    while((item = layout()->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }*/

    std::wcout << model->items.size() << std::endl;
    int rowCounter = 0;
    for(std::vector<MainWindowViewItem*> line: model->items)
    {
        std::wcout << line.size() << std::endl;
        QHBoxLayout* lineLayout = new QHBoxLayout;
        for(MainWindowViewItem * item : line)
        {
            std::wcout << item->value << std::endl;
            QString vValue = QString::fromWCharArray(item->value.c_str());
            if(item->type == Label)
            {
                QLabel * label = new QLabel(this);
                label->setText(vValue);
                lineLayout->addWidget(label);
            }
            else
            {
                QLineEdit * lineEdit = new QLineEdit(this);
                lineEdit->setText(vValue);
                lineLayout->addWidget(lineEdit);
            }
        }
        mainLayout->addLayout(lineLayout, rowCounter++, 0);
    }
}

void MainWindow::newMemDoc()
{
    controller->createMemoryDoc(L"Hello World!\nHello Again?\nLet's 'test' something...\nWhat if a line has very very many words in it. Does this still work? Perhaps with a long word at the end? Supercalifragalisticexpialadoshisi", {L'!', L'?', L'\'', L'.'});
}

void MainWindow::open()
{

}

void MainWindow::save()
{

}

void MainWindow::editText()
{

}

void MainWindow::about()
{

}
