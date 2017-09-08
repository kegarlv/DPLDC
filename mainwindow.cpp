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

    ui->deleteMeterButton->setVisible(false);

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

void MainWindow::getMeterData(QVector<double> &activeData, QVector<double> &reactiveData) {
    for (auto view : m_meterViews) {
        if(!view->isVisible()) {continue;}
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
            for (int i = 0; i < tmp.size(); i++) {
                activeData[i] -= tmp[i] * view->getK();
            }
            break;
        }
    }
}

void MainWindow::on_addMeterButton_clicked() {
    myDialog->show();
}

void MainWindow::addNewMeter() {
    myDialog->hide();
    Meter meter = myDialog->getMeter();

    MeterViewV2 *meterView = new MeterViewV2(meter);
    m_meterViews.push_back(meterView);

    connect(meterView, &MeterViewV2::meterViewChecked, [this](bool isChecked) {
        static int i = 0;
        isChecked ? i++ : i--;
        ui->deleteMeterButton->setVisible(i);
    });

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

    getMeterData(activeData, reactiveData);

    ChartViewer *viewer = new ChartViewer(activeData, reactiveData);
    viewer->show();
}

void MainWindow::on_activeTableButton_clicked() {
}

void MainWindow::on_cumulativeTableButton_clicked() {
    QVector<double> activeData(25); /*Active means active-sububer*/
    QVector<double> reactiveData(25);
    getMeterData(activeData, reactiveData);

    for (int i = 1; i < activeData.size(); i++) {
        activeData[i - 1] = activeData[i] - activeData[i - 1];
    }

    for (int i = 1; i < reactiveData.size(); i++) {
        reactiveData[i - 1] = reactiveData[i] - reactiveData[i - 1];
    }

    QString saveFileName = QFileDialog::getSaveFileName(this, "Виберіть файл");
    saveFileName += ".csv";

    QFile file(saveFileName);
    file.open(QIODevice::WriteOnly);
    file.write(",,Зведена відомість\n,,вимірів у режимний день\n,,21 грудня 2016 р.\n,,ДП Львівський державний цирк\n");
    for(int i=0; i<activeData.size()-1; i++) {
        file.write((QString::number(activeData[i]) + "," + QString::number(reactiveData[i]) + "\n").toStdString().c_str());
    }

}

void MainWindow::on_deleteMeterButton_clicked() {
    for (auto itBegin = m_meterViews.begin(); itBegin != m_meterViews.end(); itBegin++) {
        if ((*itBegin)->isChecked()) {
            (*itBegin)->hide();
            (*itBegin)->setChecked(false);
        }
    }
}
