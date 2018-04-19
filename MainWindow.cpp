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
    editor = new QTextEdit();
    lineNumbers = new QLabel("1");

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    editor->setSizePolicy(spRight);
    editor->setTabStopWidth(16);

    QSplitter* verticalSplitter = new QSplitter(Qt::Orientation::Vertical);
    QSplitter* horizontalSplitter = new QSplitter(Qt::Orientation::Horizontal);

    applicationLog->setStyleSheet("background-color:white;");
    stdOut->setStyleSheet("background-color:white; color:red");
    stdOut->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    stdOut->setMargin(10);

    QWidget* topParent = new QWidget();

    QScrollArea* area = new QScrollArea();
    QHBoxLayout* layout = new QHBoxLayout();
    QSizePolicy spLineNumber(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLineNumber.setHorizontalStretch(0);
    lineNumbers->setSizePolicy(spLineNumber);
    lineNumbers->setMargin(5);
    layout->addWidget(lineNumbers,0,0);
    layout->setAlignment(lineNumbers,Qt::AlignTop | Qt::AlignHCenter);
    editor->setLineWrapMode(QTextEdit::NoWrap);
    //editor->setFixedWidth(area->width()-area->verticalScrollBar()->width()-2);

    layout->addWidget(editor,0,0);
    layout->setContentsMargins(0,0,0,0);
    topParent->setLayout(layout);

    area->setWidgetResizable(true);
    area->setWidget(topParent);

    QScrollArea* area1 = new QScrollArea();
    area1->setWidgetResizable(true);
    area1->setWidget(stdOut);

    QScrollArea* area2 = new QScrollArea();
    area2->setWidgetResizable(true);
    area2->setWidget(applicationLog);
    verticalSplitter->addWidget(area);
    verticalSplitter->addWidget(area1);
    verticalSplitter->addWidget(area2);
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
    toolbar->addAction("Step",this,SLOT(callStepper()));
    connect(editor->document(), SIGNAL(blockCountChanged(int)),this,SLOT(updateLines(int)));
    this->resize(windowWidth,windowHeight);
    this->editor->setFocus();
}

void MainWindow::callStepper(){
    step();
}

void MainWindow::callParser(){
    string code = editor->toPlainText().toStdString();
    parseString(code,this);
}

void MainWindow::updateLines(int lines){

    lineNumbers->setText("");
    string newLine = "1";
    for (int index = 2; index <= lines; index++){
        newLine = newLine + "\n" + to_string(index);
    }
    lineNumbers->setText(QString::fromStdString(newLine));
}

void MainWindow::stdOutErr(string err) {
    stdOut->setText(stdOut->text() + QString::fromStdString(err));
}