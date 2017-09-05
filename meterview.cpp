#include "meterview.h"

MeterView::MeterView(const Meter &meter, QWidget *parent) : QWidget(parent), m_meter(meter) {
    m_groupBox = new QGroupBox(this);
    m_mainLayout = new QHBoxLayout(this);
    m_groupBoxLayout = new QVBoxLayout(this);
    m_typeLabel = new QLabel(this);
    m_kRozLabel = new QLabel(this);
    m_checkBox = new QCheckBox(this);

    m_mainLayout->addWidget(m_checkBox);
    m_mainLayout->addWidget(m_groupBox);

    m_groupBox->setLayout(m_groupBoxLayout);
    m_groupBoxLayout->addWidget(m_typeLabel);
    m_groupBoxLayout->addWidget(m_kRozLabel);

    m_groupBox->setTitle("Номер лічильника: " + m_meter.getId());
    m_typeLabel->setText("Тип лічильника: " + m_meter.getStringType());
    m_kRozLabel->setText("Розрахунковий коефіцієнт: " + QString::number(m_meter.k()));

    this->setLayout(m_mainLayout);
}

MeterView::~MeterView() {
    delete m_checkBox;
    delete m_kRozLabel;
    delete m_typeLabel;
    delete m_groupBoxLayout;
    delete m_groupBox;
    delete m_mainLayout;
}
