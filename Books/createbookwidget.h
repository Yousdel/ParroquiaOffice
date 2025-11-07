#ifndef CREATEBOOKWIDGET_H
#define CREATEBOOKWIDGET_H

#include <QWidget>

namespace Ui {
class CreateBookWidget;
}

class CreateBookWidget : public QWidget
{
    Q_OBJECT

public:
    enum BookType {
        GB=0, SB, GM, SM, GD, SD, GC, SC,
        BPersonalized,
        MPersonalized,
        DPersonalized,
        CPersonalized,
        None
    };

    explicit CreateBookWidget(QWidget *parent = nullptr);
    ~CreateBookWidget();

    static bool isSinglePersonType(const BookType &type) {
        //para libros de una sola persona(bautismo, defuncion y confirmacion)
        if (type == GB || type == SB ||
            type == GD || type == SD ||
            type == GC || type == SC ||
            type == BPersonalized ||
            type == DPersonalized ||
            type == CPersonalized)
            return true;
        return false;
    }

    static const QString &shortString(const BookType &type){
        static QString s; s.clear();
        if (isBaptismType(type))
            s.append(tr("Bautismo"));
        else if (isDefunctionType(type))
            s.append(tr("Defunción"));
        else if (isConfirmationType(type))
            s.append(tr("Confirmación"));
        else
            s.append(tr("Matrimonio"));
        return s;
    }

    static bool isBaptismType(const BookType &type) {
        return (type == GB || type == SB ||
                type == BPersonalized);
    }

    static bool isMarriageType(const BookType &type) {
        return (type == GM || type == SM ||
                type == MPersonalized);
    }

    static bool isDefunctionType(const BookType &type) {
        return (type == GD || type == SD ||
                type == DPersonalized);
    }

    static bool isConfirmationType(const BookType &type) {
        return (type == GC || type == SC ||
                type == CPersonalized);
    }

    BookType desiredType() const;
    const QString entireName() const;

    const QString desiredSigla() const;

    static const QString stringForType(CreateBookWidget::BookType type);
private slots:
    void on_createBtn_clicked();

    void on_cancelBtn_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::CreateBookWidget *ui;

signals:
    void createBook(BookType type,QString sigla, QString entireName);
    void widgetClosed();
};

#endif // CREATEBOOKWIDGET_H
