#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QVector>
#include <QSplineSeries>
#include <QChart>
#include <QtCharts>

#include "dialog.h"
#include "meterviewv2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addMeterButton_clicked();
    void addNewMeter();

    void on_graphButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *myDialog;
    QVector<MeterViewV2*> m_meterViews;
    QWidget *activeWidgetContainer, *reactiveWidgetContainer;
    QVBoxLayout *activeMeterLayout, *reactiveMeterLayout;
};

#endif // MAINWINDOW_H
