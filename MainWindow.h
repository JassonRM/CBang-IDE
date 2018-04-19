//
// Created by marco on 19/03/18.
//

#ifndef CFACTORIAL_IDE_MAINWINDOW_H
#define CFACTORIAL_IDE_MAINWINDOW_H


#include <QtWidgets>
#include "Parser.h"


class MainWindow : public QMainWindow {

    Q_OBJECT
public:
    MainWindow();
    void stdOutErr(string err);

private slots:
    void callParser();
    void callStepper();
    void updateLines(int);
private:
    QWidget* centralWidget;

    QVBoxLayout* vLayout;

    QTextEdit* editor;

    QLabel* stdOut;

    QLabel* applicationLog;

    QTableView* tableView;

    QToolBar* toolbar;

    QLabel* lineNumbers;

    int const windowWidth = 800;

    int const windowHeight = 600;
};

#endif //CFACTORIAL_IDE_MAINWINDOW_H
