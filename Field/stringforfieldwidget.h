
#ifndef STRINGFORFIELDWIDGET_H
#define STRINGFORFIELDWIDGET_H

#include <QWidget>
#include <QLabel>

class StringForField;
class QTextEdit;
class QPushButton;

/**
 * @brief Widget para modificar/mostrar
 * la cadena de caracteres del campo.
 */
class StringForFieldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StringForFieldWidget(QWidget *parent = nullptr);
    explicit StringForFieldWidget(StringForField *model, QWidget *parent = nullptr);

    void setModel(StringForField *model);
    StringForField *model() const { return m_model; }

    inline void makeTitle()
    {
        if (m_is_title){
            QString text=m_label->text();
            text.prepend("<b>");
            text.append("</b>");
            m_label->setText(text);
        }
    }

    void setIsTitle(bool isTitle=false){
        m_is_title=isTitle;
        makeTitle();
    }

private slots:
    void onChangeClicked();
    void onSaveClicked();
    void modelValueChanged(const QString &v);
    void returnToViewMode();

private:
    void updateView();

    StringForField *m_model;
    QLabel *m_label;
    QTextEdit *m_editor;
    QPushButton *m_btnChange;
    QPushButton *m_btnSave, *m_btnCancel;
    bool m_is_title=false;

signals:
    void modelChanged(StringForField *newString);
};

#endif // STRINGFORFIELDWIDGET_H
