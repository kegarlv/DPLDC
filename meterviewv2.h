#ifndef METERVIEWV2_H
#define METERVIEWV2_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSizePolicy>
#include <QCheckBox>
#include <QSplineSeries>
#include <QtDebug>

#include "meter.h"
#include "indexes.h"

namespace Ui {
class MeterViewV2;
}

class MeterViewV2 : public QWidget
{
    Q_OBJECT

public:
    explicit MeterViewV2(const Meter &meter, QWidget *parent = 0);
    ~MeterViewV2();

    bool isChecked();
    Meter::Type getType();
    int getK() {return m_meter.k();}
    QVector<double> getData();

private:
    Ui::MeterViewV2 *ui;
    Meter m_meter;

};

#endif // METERVIEWV2_H
