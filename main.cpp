//
// Created by marco on 19/03/18.
//

#include <QtWidgets>
#include "MainWindow.h"
#include "Parser.h"

int main(int argc, char *argv[]) {

    //parse("int a = 1*(2+7);"
    //              "struct {int b = 0;"
    //              "}a;");

    QApplication app(argc, argv);

    MainWindow window;

    window.show();

    return app.exec();


    return 0;
}