//
// Created by marco on 19/03/18.
//

#include "MainWindow.h"

MainWindow::MainWindow(){

    tableView = new QTableView();
    centralWidget = new QWidget();
    vLayout = new QVBoxLayout();
    applicationLog = new QLabel();
    stdOut = new QLabel();
    editor = new TextEditor();

    Highlighter* highlighter = new Highlighter(editor->document());

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    editor->setSizePolicy(spRight);
    editor->setTabStopWidth(16);
    editor->setLineWrapMode(QPlainTextEdit::NoWrap);

    QSplitter* verticalSplitter = new QSplitter(Qt::Orientation::Vertical);
    QSplitter* horizontalSplitter = new QSplitter(Qt::Orientation::Horizontal);

    applicationLog->setStyleSheet("background-color:white;");
    stdOut->setStyleSheet("background-color:white; color:red");
    stdOut->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    stdOut->setMargin(10);


    QScrollArea* area1 = new QScrollArea();
    area1->setWidgetResizable(true);
    area1->setWidget(stdOut);

    QScrollArea* area2 = new QScrollArea();
    area2->setWidgetResizable(true);
    area2->setWidget(applicationLog);
    verticalSplitter->addWidget(editor);
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

void MainWindow::stdOutErr(string err) {
    stdOut->setText(stdOut->text() + QString::fromStdString(err));
}