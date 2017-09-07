#ifndef CONSUMPTIONINFOWIDGET_H
#define CONSUMPTIONINFOWIDGET_H

#include <QWidget>

namespace Ui {
class ConsumptionInfoWidget;
}

class ConsumptionInfoWidget : public QWidget {
    Q_OBJECT

  public:
    struct ConsumpingInfo {
        double total = 0, max = -1e9, min = 1e9, average = 0;
        QString type = "";
        QString uom = "";
    };

    explicit ConsumptionInfoWidget(const ConsumpingInfo &info, QWidget *parent = 0);
    ~ConsumptionInfoWidget();

  private:
    Ui::ConsumptionInfoWidget *ui;
};

#endif // CONSUMPTIONINFOWIDGET_H
