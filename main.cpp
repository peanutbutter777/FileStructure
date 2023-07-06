#include "mainwindow.h"
#include<QFile>
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile("D:/FSCQT/Ubuntu.qss"); // Replace with the correct path
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
    }
    MainWindow w;

     w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
