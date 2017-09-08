#include "chartviewer.h"

ChartViewer::ChartViewer(const QVector<double> &activeData, const QVector<double> &reactiveData, QWidget *parent) : QWidget(parent) {
    m_activeSeries = new QtCharts::QLineSeries(this);
    m_reactiveSeries = new QtCharts::QLineSeries(this);

    QVector<double> activeDiff, reactiveDiff;
    for (int i = 1; i < activeData.size(); i++) {
        m_activeSeries->append(i, activeData[i] - activeData[i - 1]);
        activeDiff.push_back(activeData[i] - activeData[i - 1]);

        m_reactiveSeries->append(i, reactiveData[i] - reactiveData[i - 1]);
        reactiveDiff.push_back(reactiveData[i] - reactiveData[i - 1]);
    }

    m_activeInfo.uom = "кВт";
    m_activeInfo.type = "Активний";

    m_reactiveInfo.uom = "кВАр";
    m_reactiveInfo.type = "Реактивний";

    for (auto &x : activeDiff) {
        m_activeInfo.max = std::max(m_activeInfo.max, x);
        m_activeInfo.min = std::min(m_activeInfo.min, x);
        m_activeInfo.total += x;
    }
    for (auto &x : reactiveDiff) {
        m_reactiveInfo.max = std::max(m_reactiveInfo.max, x);
        m_reactiveInfo.min = std::min(m_reactiveInfo.min, x);
        m_reactiveInfo.total += x;
    }

    m_activeInfo.average = (activeDiff.size() ? m_activeInfo.total / activeDiff.size() : 0);
    m_reactiveInfo.average = (reactiveDiff.size() ? m_reactiveInfo.total / reactiveDiff.size() : 0);

    m_chart = new QtCharts::QChart();
    m_chart->addSeries(m_activeSeries);
    m_chart->addSeries(m_reactiveSeries);
    m_chart->createDefaultAxes();

    (dynamic_cast<QtCharts::QValueAxis*>(m_chart->axisX()))->setTickCount(24);
    m_chartView = new QtCharts::QChartView(m_chart, this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_activeConsumptionInfoWidget = new ConsumptionInfoWidget(m_activeInfo, this);
    m_reactiveConsumptionInfoWidget = new ConsumptionInfoWidget(m_reactiveInfo, this);

    m_mainLayout = new QHBoxLayout(this);
    m_consumpingInfoLayout = new QVBoxLayout(this);

    m_spacerItem = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_consumpingInfoLayout->addWidget(m_activeConsumptionInfoWidget);
    m_consumpingInfoLayout->addWidget(m_reactiveConsumptionInfoWidget);
    m_consumpingInfoLayout->addItem(m_spacerItem);

    m_consumpingInfoLayout->setSizeConstraint(QLayout::SetMinimumSize);
    m_mainLayout->addWidget(m_chartView);
    m_mainLayout->addItem(m_consumpingInfoLayout);

    this->setLayout(m_mainLayout);
    this->resize(QApplication::desktop()->screenGeometry().size());
}

ChartViewer::~ChartViewer() {
    delete m_chart;
    delete m_spacerItem;
}
