#ifndef DROPTABLEWIDGET_H
#define DROPTABLEWIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class DropTableWidget;
}

class DropTableWidget : public QWidget
{
    Q_OBJECT

public:
    DropTableWidget(const QString &dbpath,
                    QWidget *parent = nullptr);
    ~DropTableWidget();

    const QString &bookToDrop();
    void updateBooks();
    void setPath(const QString &dbpath) {
        _path=dbpath;
    }
    
private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_removeBook_clicked();

    void on_CancelBtn_clicked();

private:
    Ui::DropTableWidget *ui;
    QString m_selected_book, _path;

signals:
    void widgetClosed(bool remove);
};

#endif // DROPTABLEWIDGET_H
