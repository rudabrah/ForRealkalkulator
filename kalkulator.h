#ifndef KALKULATOR_H
#define KALKULATOR_H

//#include "qlineedit.h"
#include <QMainWindow>
#include <QArrayData>

QT_BEGIN_NAMESPACE
namespace Ui { class Kalkulator; }
QT_END_NAMESPACE

class Kalkulator : public QMainWindow
{
    Q_OBJECT

public:
    Kalkulator(QWidget *parent = nullptr);
    ~Kalkulator();

private:
    Ui::Kalkulator *ui;

    void clearAll();
    void addNew();
    void removeLastLine();
    void calculate();

};
#endif // KALKULATOR_H
