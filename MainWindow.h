//
// Created by marco on 19/03/18.
//

#ifndef CFACTORIAL_IDE_MAINWINDOW_H
#define CFACTORIAL_IDE_MAINWINDOW_H

#include <iostream>
#include <QtWidgets>
#include "Parser.h"
#include "TextEditor.h"
#include "Highlighter.h"


class MainWindow : public QMainWindow {

    Q_OBJECT
public:
    MainWindow();
    void stdOutErr(string err);
    void updateLiveView();

private slots:
    void callParser();
    void callStepper();
private:
    QWidget* centralWidget;

    QVBoxLayout* vLayout;

    TextEditor* editor;

    QLabel* stdOut;

    QLabel* applicationLog;

    QTableWidget* tableWidget;

    QToolBar* toolbar;

    QLabel* lineNumbers;

    int const windowWidth = 800;

    int const windowHeight = 600;
};

#endif //CFACTORIAL_IDE_MAINWINDOW_H
