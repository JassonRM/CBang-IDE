//
// Created by marco on 19/03/18.
//

#include "MainWindow.h"

MainWindow::MainWindow(){

    tableWidget = new QTableWidget();
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
    horizontalSplitter->addWidget(tableWidget);

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


    //RAM Live View
    tableWidget->setColumnCount(4);

    QStringList labels;
    labels<<"Address"<<"Identifier"<<"Value"<<"References";
    tableWidget->setHorizontalHeaderLabels(labels);


}

void MainWindow::callStepper(){
    step();
    updateLiveView();
}

void MainWindow::callParser(){
    string code = editor->toPlainText().toStdString();
    parseString(code,this);
    updateLiveView();
}

void MainWindow::stdOutErr(string err) {
    stdOut->setText(stdOut->text() + QString::fromStdString(err));
}

void MainWindow::updateLiveView() {
    QString request = "{\"Request\":\"RAM Status\"}";
    QJsonDocument jsonRequest = QJsonDocument::fromJson(request.toUtf8());

    std::cout << jsonRequest.toJson().data() << std::endl;


    ServerConnection *server = ServerConnection::getServerConnection();
    QJsonDocument *response = server->request(&jsonRequest);

    QJsonArray array = response->array();

    for(int row = 0; row < response->array().size(); row++){
        tableWidget->setRowCount(row + 1);
        QTableWidgetItem *address = new QTableWidgetItem(1);
        address->setText(QString::number(array.at(row).toObject()["Address"].toInt()));
        tableWidget->setItem(row, 0, address);

        QTableWidgetItem *identifier = new QTableWidgetItem(2);
        identifier->setText(array.at(row).toObject()["Identifier"].toString());
        tableWidget->setItem(row, 1, identifier);

        QTableWidgetItem *value = new QTableWidgetItem(3);

        QString type = array.at(row).toObject()["Type"].toString();
        if(type == "int" || type == "reference"){
            value->setText(QString::number(array.at(row).toObject()["Value"].toInt()));
        }else if(type == "long" || type == "double" || type == "float"){
            value->setText(QString::number(array.at(row).toObject()["Value"].toDouble()));
        }else if(type == "char"){
            char charvalue = array.at(row).toObject()["Value"].toInt();
            value->setText(QString::fromUtf8(&charvalue, 1));
        }

        tableWidget->setItem(row, 2, value);

        QTableWidgetItem *references = new QTableWidgetItem(1);
        references->setText(QString::number(array.at(row).toObject()["References"].toInt()));
        tableWidget->setItem(row, 3, references);
    }

    std::cout<<response->toJson().toStdString()<<std::endl;
}