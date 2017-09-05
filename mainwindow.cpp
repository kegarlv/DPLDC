#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    myDialog = new Dialog(this);
    connect(myDialog, &Dialog::accepted, this, &MainWindow::addNewMeter);

    activeWidgetContainer = new QWidget(this);
    reactiveWidgetContainer = new QWidget(this);
    activeMeterLayout = new QVBoxLayout(this);
    reactiveMeterLayout = new QVBoxLayout(this);

    activeWidgetContainer->setLayout(activeMeterLayout);
    reactiveWidgetContainer->setLayout(reactiveMeterLayout);

    ui->activeMeterScrollArea->setWidget(activeWidgetContainer);
    ui->reactiveMeterScrollArea->setWidget(reactiveWidgetContainer);

    ui->centralWidget->setLayout(ui->verticalLayout);
}

MainWindow::~MainWindow() {
    delete ui;
    delete myDialog;
    for (auto &x : m_meterViews) {
        delete x;
    }

    delete activeMeterLayout;
    delete reactiveMeterLayout;
    delete activeWidgetContainer;
    delete reactiveWidgetContainer;
}

void MainWindow::on_addMeterButton_clicked() {
    myDialog->show();
}

void MainWindow::addNewMeter() {
    myDialog->hide();
    Meter meter = myDialog->getMeter();

    MeterViewV2 *meterView = new MeterViewV2(meter);
    m_meterViews.push_back(meterView);

    switch (meter.type()) {
    case Meter::active:
        activeMeterLayout->addWidget(meterView);
        break;
    case Meter::reactive:
        reactiveMeterLayout->addWidget(meterView);
        break;
    case Meter::subuser:

        break;
    }

    //TODO
    //    myDialog->reset();
}

void MainWindow::on_graphButton_clicked() {
    QtCharts::QSplineSeries *activeSeries = new QtCharts::QSplineSeries();
    QtCharts::QSplineSeries *reactiveSeries = new QtCharts::QSplineSeries();

    QVector<double> activeData(25);
    QVector<double> reactiveData(25);

    for (auto view : m_meterViews) {
        QVector<double> tmp = view->getData();
        switch (view->getType()) {
        case Meter::active:
            for (int i = 0; i < tmp.size(); i++) {
                activeData[i] += tmp[i] * view->getK();
            }
            break;
        case Meter::reactive:
            for (int i = 0; i < tmp.size(); i++) {
                reactiveData[i] += tmp[i] * view->getK();
            }
            break;
        default:
            break;
        }
    }

    for (int i = 1; i < activeData.size(); i++) {
        activeSeries->append(i, activeData[i] - activeData[i - 1]);
    }


    QtCharts::QChart *activeChart = new QtCharts::QChart();
    QtCharts::QChart *reactiveChart = new QtCharts::QChart();

    activeChart->legend()->hide();
    activeChart->addSeries(activeSeries);
    activeChart->setTitle("Активні лічильники");
    activeChart->createDefaultAxes();


    QtCharts::QChartView *activeChartView = new QtCharts::QChartView(activeChart);
    activeChartView->setRenderHint(QPainter::Antialiasing);
    activeChartView->show();

    for (int i = 1; i < reactiveData.size(); i++) {
        reactiveSeries->append(i, reactiveData[i] - reactiveData[i - 1]);
    }

    reactiveChart->legend()->hide();
    reactiveChart->addSeries(reactiveSeries);
    reactiveChart->setTitle("Реактивні лічильники");
    reactiveChart->createDefaultAxes();

    QtCharts::QChartView *reactiveChartView = new QtCharts::QChartView(reactiveChart);
    reactiveChartView->setRenderHint(QPainter::Antialiasing);
    reactiveChartView->show();


}
