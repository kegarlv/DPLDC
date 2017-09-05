#ifndef METER_H
#define METER_H

#include <bits/stdc++.h>
#include "indexes.h"

#include <QString>


class Meter {
  public:
    enum Type { active,
                reactive,
                subuser };
    Meter();

    QString getId() const;
    void setId(const QString &id);

    int k() const;
    void setK(int k);

    Type type() const;
    QString getStringType();
    void setType(const Type &type);

    QString indexesFilePath() const;
    void setIndexesFilePath(const QString &indexesFilePath);

  private:
    QString m_id;
    int m_k;
    Type m_type;
    QString m_indexesFilePath;
};

#endif // METER_H
