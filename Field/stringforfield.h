#ifndef STRINGFORFIELD_H
#define STRINGFORFIELD_H

#include <QObject>
#include <QString>

class StringForField : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit StringForField(QObject *parent = nullptr);
    explicit StringForField(const QString &v, QObject *parent = nullptr);

    QString value() const;
    void setValue(const QString &v);

signals:
    void valueChanged(const QString &v);

private:
    QString m_value;
};

#endif // STRINGFORFIELD_H
