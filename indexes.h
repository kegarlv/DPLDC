#ifndef INDEXES_H
#define INDEXES_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <exception>

using namespace std;


class Indexes
{
    Indexes();
public:
    static QVector<double> getData(QString filePath);
};

#endif // INDEXES_H
