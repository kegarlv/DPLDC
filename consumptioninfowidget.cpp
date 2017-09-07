#include "consumptioninfowidget.h"
#include "ui_consumptioninfowidget.h"

ConsumptionInfoWidget::ConsumptionInfoWidget(const ConsumpingInfo &info, QWidget *parent) : QWidget(parent),
                                                                                            ui(new Ui::ConsumptionInfoWidget) {
    ui->setupUi(this);

    ui->averageLabel->setText(QString::number(info.average));
    ui->maximumLabel->setText(QString::number(info.max));
    ui->minmalLabel->setText(QString::number(info.min));
    ui->totalLabel->setText(QString::number(info.total));

    ui->averageUoM->setText(info.uom);
    ui->maximumUoM->setText(info.uom);
    ui->minimalUoM->setText(info.uom);
    ui->totalUoM->setText(info.uom);

    ui->meterTypeLabel->setText(info.type);
    this->setLayout(ui->verticalLayout_2);
}

ConsumptionInfoWidget::~ConsumptionInfoWidget() {
    delete ui;
}
