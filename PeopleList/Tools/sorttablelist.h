#ifndef SORTTABLELIST_H
#define SORTTABLELIST_H

#include <QVector>
#include <QString>
#include <QRegularExpression>
//c++
#include <algorithm> // Para std::sort

class SortTableList
{
public:
    static void sort(QVector<QString> &list){
        QRegularExpression re("^([A-Za-z]+)(\\d+)$");
        std::sort(list.begin(), list.end(), [&re](const QString &a, const QString &b) {
            QRegularExpressionMatch matchA = re.match(a);
            QRegularExpressionMatch matchB = re.match(b);
            if (!matchA.hasMatch()) return false;
            if (!matchB.hasMatch()) return true;
            int numA = matchA.captured(2).toInt();
            int numB = matchB.captured(2).toInt();
            if (numA != numB) return numA < numB;
            return matchA.captured(1) < matchB.captured(1);
        });
    }
};

#endif // SORTTABLELIST_H
