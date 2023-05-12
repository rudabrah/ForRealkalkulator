#include "kalkulator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kalkulator w;
    w.show();
    return a.exec();
}
