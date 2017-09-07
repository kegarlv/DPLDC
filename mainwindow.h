#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QVector>
#include <QTableWidget>
#include <QLabel>

#include "dialog.h"
#include "meterviewv2.h"
#include "chartviewer.h"

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

    void on_activeTableButton_clicked();

    void on_cumulativeTableButton_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *myDialog;
    QVector<MeterViewV2*> m_meterViews;
    QWidget *activeWidgetContainer, *reactiveWidgetContainer;
    QVBoxLayout *activeMeterLayout, *reactiveMeterLayout;
};

#endif // MAINWINDOW_H
