//
// Created by marco on 19/03/18.
//

#include <iostream>
#include "MainWindow.h"

MainWindow::MainWindow(){
    tableView = new QTableView();
    centralWidget = new QWidget();
    vLayout = new QVBoxLayout();
    applicationLog = new QLabel();
    stdOut = new QLabel();
    editor = new QPlainTextEdit();

    QSplitter* verticalSplitter = new QSplitter(Qt::Orientation::Vertical);
    QSplitter* horizontalSplitter = new QSplitter(Qt::Orientation::Horizontal);

    applicationLog->setStyleSheet("background-color:white;");
    stdOut->setStyleSheet("background-color:white;");

    verticalSplitter->addWidget(editor);
    verticalSplitter->addWidget(stdOut);
    verticalSplitter->addWidget(applicationLog);
    horizontalSplitter->addWidget(verticalSplitter);
    horizontalSplitter->addWidget(tableView);

    vLayout->addWidget(horizontalSplitter);

    QList<int> widgetWidth;
    widgetWidth << windowWidth*0.7 << windowWidth*0.3;

    QList<int> widgetHeight;
    widgetHeight << windowHeight*0.5 << windowHeight*0.25 <<windowHeight*0.25;

    horizontalSplitter->setSizes(widgetWidth);
    verticalSplitter->setSizes(widgetHeight);

    centralWidget->setLayout(vLayout);

    setCentralWidget(centralWidget);


    QToolBar* toolbar = this->addToolBar("Main ToolBar");
    toolbar->addAction("Run",this,SLOT(callParser()));

    this->resize(windowWidth,windowHeight);
}

void MainWindow::callParser(){
    parse(editor->toPlainText().toStdString());
}