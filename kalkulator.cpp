#include "kalkulator.h"
#include "./ui_kalkulator.h"

Kalkulator::Kalkulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
    connect(ui->clearBtn, &QPushButton::clicked, this, &Kalkulator::clearAll);//Connects the "clear"-button to the function
    connect(ui->addLineBtn, &QPushButton::clicked, this, &Kalkulator::addNew);//Connects the "add new"-button to function
    connect(ui->removeBtn, &QPushButton::clicked, this, &Kalkulator::removeLastLine);//Connects the "remove line"-button to function
    connect(ui->equalBtn, &QPushButton::clicked, this, &Kalkulator::calculate);

}

Kalkulator::~Kalkulator()
{
    delete ui;
}

void Kalkulator::clearAll()
{
    // Get a list of all the lineEdits in the Kalkulator widget
    QList<QLineEdit*> lineEdits = ui->centralwidget->findChildren<QLineEdit*>();

    // Iterate through the lineEdits and clear their text
    for (QLineEdit* lineEdit : lineEdits) {
        lineEdit->clear();
    }


}

//Set some scaling

//Add new calculation line.
void Kalkulator::addNew()
{
    QLineEdit* newLineEdit = new QLineEdit();

    ui->lineEditLayout->addWidget(newLineEdit);
    // Set the spacing between widgets
    ui->lineEditLayout->setSpacing(6);

    // Set the margin around the layout
    ui->lineEditLayout->setContentsMargins(11, 11, 11, 11);

    QComboBox* newComboBox = new QComboBox();

    for (int i = 0; i < ui->comboBox1->count(); i++) {
        newComboBox->addItem(ui->comboBox1->itemText(i));
    }


    ui->comboBoxLayout->addWidget(newComboBox);
    // Set the spacing between widgets
    ui->comboBoxLayout->setSpacing(6);

    // Set the margin around the layout
    ui->comboBoxLayout->setContentsMargins(11, 11, 11, 11);


}
//Remove lines of calculation.
void Kalkulator::removeLastLine() {
    // Get the number of existing line edits and combo boxes
    int numLineEdits = ui->lineEditLayout->count();
    int numComboBoxes = ui->comboBoxLayout->count();

    // Remove the last line edit and combo box from their respective layouts
    if (numLineEdits > 2 && numComboBoxes > 1) {
        QLayoutItem* lineEditItem = ui->lineEditLayout->takeAt(numLineEdits - 1);
        QLayoutItem* comboBoxItem = ui->comboBoxLayout->takeAt(numComboBoxes - 1);
        delete lineEditItem->widget();
        delete comboBoxItem->widget();
        delete lineEditItem;
        delete comboBoxItem;
    }
}

// Create a slot function to be called when a calculation is required
void Kalkulator::calculate() {
    float sum = ui->inputLine->text().toFloat(); // Get the initial value

    for (int i = 1; i < ui->lineEditLayout->count(); i++) { // Loop through all the other input lines
        QComboBox* opComboBox = qobject_cast<QComboBox*>(ui->comboBoxLayout->itemAt(i)->widget()); // Get the QComboBox for the operator
        QLineEdit* numLineEdit = qobject_cast<QLineEdit*>(ui->lineEditLayout->itemAt(i)->widget()); // Get the QLineEdit for the number


        QString op = opComboBox->currentText(); // Get the operator
        float num = numLineEdit->text().toFloat(); // Get the number

        if (op == "+") {
            sum += num;
        } else if (op == "-") {
            sum -= num;
        } else if (op == "*") {
            sum *= num;
        } else if (op == "/") {
            sum /= num;
        }
    }

    // Output the result to a label or another QLineEdit
    ui->resLineEdit->setText(QString::number(sum));
}
