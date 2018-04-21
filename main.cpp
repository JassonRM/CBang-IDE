//
// Created by marco on 19/03/18.
//

#include <QtWidgets>
#include "MainWindow.h"
#define LOGURU_IMPLEMENTATION 1
#include <loguru.hpp>

int main(int argc, char *argv[]) {

    loguru::init(argc, argv);

    loguru::add_file("~/everything.log", loguru::Append, loguru::Verbosity_1);

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}