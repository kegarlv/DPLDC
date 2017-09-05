#include "meterviewv2.h"
#include "ui_meterviewv2.h"

MeterViewV2::MeterViewV2(const Meter &meter, QWidget *parent) : QWidget(parent),
                                                                ui(new Ui::MeterViewV2),
                                                                m_meter(meter) {
    ui->setupUi(this);
    ui->groupBox->setTitle("Номер лічильника: " + m_meter.getId());
    ui->type->setText("Тип лічильника: " + m_meter.getStringType());
    ui->kRoz->setText("Розрахунковий коефіцієнт: " + QString::number(m_meter.k()));
    ui->filePath->setText(m_meter.indexesFilePath());

    this->setLayout(ui->horizontalLayout);
    ui->groupBox->setLayout(ui->verticalLayout);
}

MeterViewV2::~MeterViewV2() {
    delete ui;
}

bool MeterViewV2::isChecked() {
    return ui->checkBox->isChecked();
}

Meter::Type MeterViewV2::getType() {
    return m_meter.type();
}

QVector<double> MeterViewV2::getData() {
    return Indexes::getData(m_meter.indexesFilePath());
}
