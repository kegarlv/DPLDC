#include "meter.h"

Meter::Meter() {
}

QString Meter::getId() const {
    return m_id;
}

void Meter::setId(const QString &value) {
    m_id = value;
}

int Meter::k() const {
    return m_k;
}

void Meter::setK(int k) {
    m_k = k;
}

Meter::Type Meter::type() const {
    return m_type;
}

QString Meter::getStringType()
{
    switch(m_type) {
    case Meter::active:
        return "Активний";
    case Meter::reactive:
        return "Реактивний";
    case Meter::subuser:
        return "Субкористувач";
    }
}

void Meter::setType(const Type &type) {
    m_type = type;
}

QString Meter::indexesFilePath() const {
    return m_indexesFilePath;
}

void Meter::setIndexesFilePath(const QString &indexesFilePath) {
    m_indexesFilePath = indexesFilePath;
}
