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
        //Do not show subuserMeters
        break;
    }

    //TODO
    //    myDialog->reset();
}

void MainWindow::on_graphButton_clicked() {

    QVector<double> activeData(25); /*Active means active-sububer*/
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
        case Meter::subuser:
            for(int i=0; i<tmp.size(); i++) {
                activeData[i] -= tmp[i]*view->getK();
            }
            break;
        }
    }

    ChartViewer *viewer = new ChartViewer(activeData, reactiveData);
    viewer->show();
}

void MainWindow::on_activeTableButton_clicked()
{
}

void MainWindow::on_cumulativeTableButton_clicked()
{
    //TODO
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(3);
    tableWidget->setRowCount(25);

    QVector<double> activeData(25); /*Active means active-sububer*/
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
        case Meter::subuser:
            for(int i=0; i<tmp.size(); i++) {
                activeData[i] -= tmp[i]*view->getK();
            }
            break;
        }
    }

    for(int i=0;i<24;i++) {
        for(int j=0;j<2;j++) {
            tableWidget->setCellWidget(i,j,new QLabel(QString::number(j?activeData[i]:reactiveData[i])));
        }
    }

    tableWidget->show();
}
