#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "meter.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
  public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    Meter getMeter();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::Dialog *ui;
    QString m_filename;
};

#endif // DIALOG_H
