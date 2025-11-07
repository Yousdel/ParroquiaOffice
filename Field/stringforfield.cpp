#include "stringforfield.h"

StringForField::StringForField(QObject *parent)
    : QObject(parent), m_value()
{}

StringForField::StringForField(const QString &v, QObject *parent)
    : QObject(parent), m_value(v)
{}

QString StringForField::value() const
{
    return m_value;
}

void StringForField::setValue(const QString &v)
{
    if (m_value == v) return;
    m_value = v;
    emit valueChanged(m_value);
}
