#include "indexes.h"

Indexes::Indexes(){}

QVector<double> Indexes::getData(QString filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw exception();
    }
    QVector<double> res;
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        line = line.left(line.length()-1);
        bool isOk;
        double tmp = line.toDouble(&isOk);
        if(isOk) res.append(tmp);
    }
    return res;
}
