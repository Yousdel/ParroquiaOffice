#include "stringforfieldwidget.h"
#include "stringforfield.h"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

StringForFieldWidget::StringForFieldWidget(QWidget *parent)
    : QWidget(parent),
    m_model(nullptr),
    m_label(new QLabel(this)),
    m_editor(new QTextEdit(this)),
    m_btnChange(new QPushButton(tr("Cambiar"), this)),
    m_btnSave(new QPushButton(tr("Guardar"), this)),
    m_btnCancel(new QPushButton(tr("Cancelar"), this))
{
    int fontPointSize=0xc;
    // Por defecto mostramos label y botón Cambiar.
    m_editor->setFont(QFont("",fontPointSize));
    m_editor->setVisible(false);
    m_btnSave->setVisible(false);
    m_btnCancel->hide();

    m_editor->setAcceptRichText(false); // texto plano
    m_editor->setTabChangesFocus(true);

    auto *topLayout = new QHBoxLayout;
    m_label->setFont(QFont("", fontPointSize));
    topLayout->addWidget(m_label);
    topLayout->addStretch();
    topLayout->addWidget(m_btnChange);

    auto *editLayout = new QHBoxLayout;
    editLayout->addWidget(m_editor);

    auto *editBtnsLayout = new QVBoxLayout;
    editBtnsLayout->addWidget(m_btnSave);
    editBtnsLayout->addWidget(m_btnCancel);
    editLayout->addLayout(editBtnsLayout);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(editLayout);
    setLayout(mainLayout);

    connect(m_btnChange, &QPushButton::clicked,
            this, &StringForFieldWidget::onChangeClicked);
    connect(m_btnSave, &QPushButton::clicked,
            this, &StringForFieldWidget::onSaveClicked);
    connect(m_btnCancel, &QPushButton::clicked,
            this, &StringForFieldWidget::returnToViewMode);

    updateView();
}

StringForFieldWidget::StringForFieldWidget(StringForField *model, QWidget *parent)
    : StringForFieldWidget(parent)
{
    setModel(model);
}

void StringForFieldWidget::setModel(StringForField *model)
{
    if (m_model == model) return;

    if (m_model) {
        disconnect(m_model, &StringForField::valueChanged,
                   this, &StringForFieldWidget::modelValueChanged);
    }

    m_model = model;

    if (m_model) {
        connect(m_model, &StringForField::valueChanged,
                this, &StringForFieldWidget::modelValueChanged);
    }

    updateView();
}

void StringForFieldWidget::onChangeClicked()
{
    if (!m_model) return;
    // pasar a modo edición
    m_editor->setPlainText(m_model->value());
    m_label->setVisible(false);
    m_btnChange->setVisible(false);

    m_editor->setVisible(true);
    m_btnSave->setVisible(true);
    m_btnCancel->show();
    m_editor->setFocus();
}

void StringForFieldWidget::returnToViewMode()
{
    m_editor->setVisible(false);
    m_btnSave->setVisible(false);
    m_btnCancel->hide();

    m_label->setVisible(true);
    m_btnChange->setVisible(true);
}

void StringForFieldWidget::onSaveClicked()
{
    if (!m_model) return;
    QString newVal = m_editor->toPlainText();
    m_model->setValue(newVal); // emitirá valueChanged

    // volver a modo vista
    returnToViewMode();

    emit modelChanged(m_model);
}

void StringForFieldWidget::modelValueChanged(const QString & /*v*/)
{
    updateView();
}

void StringForFieldWidget::updateView()
{
    QString text = m_model ? m_model->value() : QString();
    // Si el texto puede ser multiline, QLabel mostrará saltos si usas setTextInteractionFlags
    m_label->setText(text);
    makeTitle();  //si es titulo se pone en negrita
}
