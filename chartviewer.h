#ifndef CHARTVIEWER_H
#define CHARTVIEWER_H

#include <QVector>
#include <QWidget>
#include <QtCharts>
#include <QSpacerItem>

#include <algorithm>

#include "consumptioninfowidget.h"

class ChartViewer : public QWidget {
    Q_OBJECT
  public:
    ChartViewer(const QVector<double> &activeData, const QVector<double> &reactiveData, QWidget *parent = nullptr);
    ~ChartViewer();

  private:
    QtCharts::QLineSeries *m_activeSeries, *m_reactiveSeries;
    QtCharts::QChart *m_chart;
    QtCharts::QChartView *m_chartView;

    QLayout *m_mainLayout;
    QLayout *m_consumpingInfoLayout;

    ConsumptionInfoWidget::ConsumpingInfo m_activeInfo, m_reactiveInfo;
    ConsumptionInfoWidget *m_activeConsumptionInfoWidget, *m_reactiveConsumptionInfoWidget;
    QSpacerItem *m_spacerItem;
};

#endif // CHARTVIEWER_H
