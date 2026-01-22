#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QPalette>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
