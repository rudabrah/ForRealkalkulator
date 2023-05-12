#include "kalkulator.h"
#include "./ui_kalkulator.h"

Kalkulator::Kalkulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
    connect(ui->clearBtn, &QPushButton::clicked, this, &Kalkulator::clearAll);
    connect(ui->addLineBtn, &QPushButton::clicked, this, &Kalkulator::addNew);
    connect(ui->removeBtn, &QPushButton::clicked, this, &Kalkulator::removeLastLine);

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

QList<float> calculate()
{
    //This is reused from earlier function - It makes the code dynamic, parsing through
    //all inputlines by counting the actual lines first.
    QList<QLineEdit*> lineEdits = ui->centralwidget->findChildren<QLineEdit*>();
    QList<float> inputnumbers;

    for (QLineEdit* lineEdit : lineEdits)
    {
        QString text = lineEdit->text();
        bool ok;
        float value = text.toFloat(&ok);
        if (ok)
        {
            inputnumbers.append(value);
        }
    }
    return inputnumbers;


}

//Herfra sliter vi - for å hente variabler må jeg ha Kalkulator:: forran

/*QList<QString> getExpressions()
{
    //Reuse yet again, but with the comboboxes.
    QList<QComboBox*> comboBoxes = ui->centralwidget->findChildren<QComboBox*>();
    QList<QString> expresions;

    for (QComboBox* combobox : comboBoxes)
    {
        QString exps = combobox ->currentText();

        expresions.append(exps);
    }
    return expresions;

}*/

float calculateResult(const QList<float>& values, const QList<QString>& operators) {
    float result = values[0];  // Start with the first value in the list

    for (int i = 1; i < values.size(); i++) {
        const QString& op = operators[i-1];
        float value = values[i];

        if (op == "+") {
            result += value;
        } else if (op == "-") {
            result -= value;
        } else if (op == "*") {
            result *= value;
        } else if (op == "/") {
            if (value == 0) {
                // Handle division by zero error
                return 0.0;
            } else {
                result /= value;
            }
        }
    }

    return result;
}
