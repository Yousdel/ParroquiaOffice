#ifndef SEARCHALLWIDGET_H
#define SEARCHALLWIDGET_H

#include <QWidget>

class QSqlQueryModel;
class QTableView;
class QCloseEvent;
class QLabel;

class SearchAllWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchAllWidget(const QString &text, QWidget *parent = nullptr);

    void setModel(QSqlQueryModel *resultModel);
private:
    QTableView *tv=nullptr;
    QLabel *noitems;

private slots:
    void rowClicked(const QModelIndex &index);

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void rowSelected(QString book, QString folio, QString insc_number);
    void widgetClosed();
};

#endif // SEARCHALLWIDGET_H
