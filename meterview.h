#ifndef METERVIEW_H
#define METERVIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSizePolicy>
#include <QCheckBox>

#include "meter.h"

class MeterView : public QWidget
{
    Q_OBJECT
public:
    explicit MeterView(const Meter &meter, QWidget *parent = nullptr);
    ~MeterView();

signals:

public slots:

private:
    Meter m_meter;
    QLayout *m_mainLayout, *m_groupBoxLayout;

    QGroupBox *m_groupBox;
    QLabel *m_kRozLabel, *m_typeLabel;
    QCheckBox *m_checkBox;

};

#endif // METERVIEW_H
