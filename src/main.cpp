#include <iostream>
#include "ConverterJSON.h"
#include <QApplication>

int main(int argc, char *argv[]) {
     QApplication app(argc, argv);
    ConverterJson converter;
    converter.GetTextDocuments();
    return app.exec();
}
