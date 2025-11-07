#ifndef NEWPERSONWIDGETFACTORY_H
#define NEWPERSONWIDGETFACTORY_H


#include "baptismnewpersonwidg.h"
#include "newmarriagewidg.h"
#include "defunctionsnewpersonwidg.h"
#include "confirmationnewpersonwidg.h"

#include "Books/createbookwidget.h"

/** decide que widget crear segun el tipo de libro o tabla */
class NewPersonWidgetFactory
{

public:
    static BaseNewPersonWidg *createForType(const CreateBookWidget::BookType &type,
                                            const QString &parroquia,
                                            const QString &bookName){
        BaseNewPersonWidg *w=nullptr;
        if  (type == CreateBookWidget::GB ||
            type == CreateBookWidget::SB ||
            type == CreateBookWidget::BPersonalized){
            w = new BaptismNewPersonWidg();
        } else if (type == CreateBookWidget::GM ||
                   type == CreateBookWidget::SM ||
                   type == CreateBookWidget::MPersonalized){
            w = new NewMarriageWidg();
        } else if (type == CreateBookWidget::GD ||
                   type == CreateBookWidget::SD ||
                   type == CreateBookWidget::DPersonalized){
            w = new DefunctionsNewPersonWidg();
        } else if (type==CreateBookWidget::GC ||
                   type==CreateBookWidget::SC ||
                   type==CreateBookWidget::CPersonalized){
            w = new ConfirmationNewPersonWidg();
        }
        if (w == nullptr) return w;
        //proceder
        w->setParroquia(parroquia);
        w->setBookName(bookName);
        w->resize(700, 700);
        return w;
    }
};

#endif // NEWPERSONWIDGETFACTORY_H
