#include "basenewpersonwidg.h"

void BaseNewPersonWidg::appendBaptism(const CreateBookWidget::BookType &type)
{
    if (!CreateBookWidget::isBaptismType(type))
        return;
    append(QVariant(bornDate()));
    append(QVariant(bornPlace()));
    append(QVariant(baptismDate()));

    append(QVariant(father()));
    append(QVariant(fatherPlace()));
    append(QVariant(mother()));
    append(QVariant(motherPlace()));

    append(QVariant(paternalGrandPa()));
    append(QVariant(paternalGrandPaPlace()));
    append(QVariant(paternalGrandMa()));
    append(QVariant(paternalGrandMaPlace()));

    append(QVariant(maternalGrandPa()));
    append(QVariant(maternalGrandPaPlace()));
    append(QVariant(maternalGrandMa()));
    append(QVariant(maternalGrandMaPlace()));

    append(QVariant(godFather()));
    append(QVariant(godMother()));
    append(QVariant(getMinister()));
}

void BaseNewPersonWidg::appendMarriage(const CreateBookWidget::BookType &type)
{
    if (!CreateBookWidget::isMarriageType(type))
        return;
    append(QVariant(getMalePerson()));
    append(QVariant(getFemalePerson()));
    append(QVariant(maleBornPlace()));
    append(QVariant(femaleBornPlace()));
    append(QVariant(marriageDate()));

    append(QVariant(maleFather()));
    append(QVariant(maleMother()));

    append(QVariant(femaleFather()));
    append(QVariant(femaleMother()));

    append(QVariant(maleWitness()));
    append(QVariant(femaleWitness()));

    append(QVariant(maleGodfather()));
    append(QVariant(femaleGodmother()));
    append(QVariant(getMinister()));
}

void BaseNewPersonWidg::appendDefunction(const CreateBookWidget::BookType &type)
{
    if (!CreateBookWidget::isDefunctionType(type))
        return;
    append(QVariant(burialDate()));
    append(QVariant(dateOfDeath()));

    append(QVariant(causeOfDeath()));
    append(QVariant(age()));

    append(QVariant(father()));
    append(QVariant(mother()));
    append(QVariant(minister()));
}

void BaseNewPersonWidg::appendConfirmation(const CreateBookWidget::BookType &type)
{
    if (!CreateBookWidget::isConfirmationType(type))
        return;
    append(QVariant(confirmationDate()));
    append(QVariant(godFatherOrMother()));
    append(QVariant(minister()));
}

void BaseNewPersonWidg::showBaptism(const CreateBookWidget::BookType &type){
    if (!CreateBookWidget::isBaptismType(type))
        return;
    setBornDate(nextValue().toDate());
    setBornPlace(nextValue().toString());
    setBaptismDate(nextValue().toDate());

    setFather(nextValue().toString());
    setFatherPlace(nextValue().toString());
    setMother(nextValue().toString());
    setMotherPlace(nextValue().toString());

    setPaternalGrandPa(nextValue().toString());
    setPaternalGrandPaPlace(nextValue().toString());
    setPaternalGrandMa(nextValue().toString());
    setPaternalGrandMaPlace(nextValue().toString());

    setMaternalGrandPa(nextValue().toString());
    setMaternalGrandPaPlace(nextValue().toString());
    setMaternalGrandMa(nextValue().toString());
    setMaternalGrandMaPlace(nextValue().toString());

    setGodFather(nextValue().toString());
    setGodMother(nextValue().toString());
    setMinister(nextValue().toString());
}

void BaseNewPersonWidg::showMarriage(const CreateBookWidget::BookType &type){
    if (!CreateBookWidget::isMarriageType(type))
        return;
    setMalePerson(nextValue().toString());
    setFemalePerson(nextValue().toString());
    setMaleBornPlace(nextValue().toString());
    setFemaleBornPlace(nextValue().toString());
    setMarriageDate(nextValue().toDate());

    setMaleFather(nextValue().toString());
    setMaleMother(nextValue().toString());

    setFemaleFather(nextValue().toString());
    setFemaleMother(nextValue().toString());

    setMaleWitness(nextValue().toString());
    setFemaleWitness(nextValue().toString());

    setMaleGodfather(nextValue().toString());
    setFemaleGodmother(nextValue().toString());
    setMinister(nextValue().toString());
}

void BaseNewPersonWidg::showDefunction(const CreateBookWidget::BookType &type){
    if (!CreateBookWidget::isDefunctionType(type))
        return;
    setBurialDate(nextValue().toDate());
    setDateOfDeath(nextValue().toDate());

    setCauseOfDeath(nextValue().toString());
    setAge(nextValue().toString());

    setFather(nextValue().toString());
    setMother(nextValue().toString());
    setMinister(nextValue().toString());
}

void BaseNewPersonWidg::showConfirmation(const CreateBookWidget::BookType &type){
    if (!CreateBookWidget::isConfirmationType(type))
        return;
    setConfirmationDate(nextValue().toDate());
    setGodFatherOrMother(nextValue().toString());
    setMinister(nextValue().toString());
}

BaseNewPersonWidg::BaseNewPersonWidg(QWidget *parent)
    : QWidget{parent}
{

}


