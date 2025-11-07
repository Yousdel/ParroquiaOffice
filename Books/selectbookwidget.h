#ifndef SELECTBOOKWIDGET_H
#define SELECTBOOKWIDGET_H

#include <QWidget>
#include <QLabel>
#include "Books/createbookwidget.h"

class SuggestWidget;

class SelectBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectBookWidget(const QString &dbfilepath, QWidget *parent = nullptr);
    const QStringList &list() const;
    void setPathAndRefreshSuggestList(const QString &path);
    const CreateBookWidget::BookType &getType(const QString &book) const;
    const QString &path() const {
        return m_path;
    }
    void setText(const QString &text);
    void refreshList();

private:
    QLabel *typeLabel;
    SuggestWidget *suggestWidg;
    QString m_path,
        type;

    void showDetails(const QString &book);
signals:
    void bookSelected(QString book);
};

#endif // SELECTBOOKWIDGET_H
