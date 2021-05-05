#include "headers/mainwindow.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/icons/icon.ico"));
    w.show();
    return a.exec();
}
