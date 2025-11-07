#ifndef FINDTEXTWIDGET_H
#define FINDTEXTWIDGET_H

#include <QWidget>

namespace Ui {
class findTextWidget;
}

class FindTextWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindTextWidget(QWidget *parent = nullptr);
    ~FindTextWidget();

    const QString buttonText() const;

    void on_findBtn_clicked();
public slots:
    void returnToNormalView(){
        on_findBtn_clicked();
    }

private slots:
    void on_lineEdit_returnPressed();

    void on_find_clicked();

private:
    Ui::findTextWidget *ui;
    bool checked=false;

signals:
    void searchDesired(QString text, bool searchAllTables, bool matchAllWords);
    void returnedToNormalView();
};

#endif // FINDTEXTWIDGET_H
