#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Dialog) {
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout_3);
}

Dialog::~Dialog() {
    delete ui;
}

Meter Dialog::getMeter() {
    Meter res;
    res.setId(ui->idLineEdit->text());
    res.setK(ui->krozLineEdit->text().toInt());
    res.setIndexesFilePath(m_filename);
    res.setType((Meter::Type)ui->typeComboBox->currentIndex());
    return res;
}

void Dialog::on_pushButton_clicked() {
    m_filename = QFileDialog::getOpenFileName(this, "Відкрити файл...", "");
}
