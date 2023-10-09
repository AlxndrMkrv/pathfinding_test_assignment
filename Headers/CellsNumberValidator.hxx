#pragma once

#include <QValidator>
#include <QDebug>

class CellsNumberValidator : public QIntValidator
{
public:
    using QIntValidator::QIntValidator;

    virtual QValidator::State validate(QString &text, int &pos) const override {
        bool success;
        int value = text.toInt(&success);

        /*qDebug() << "Validator(" << text << ", " << pos << ")["
                 << bottom() << ", " << top() << "]: "
                 << value << ", " << success;*/

        if (! text.size() || (success && value < bottom()))
            return Intermediate;
        else if (success && bottom() <= value && value <= top())
            return Acceptable;
        else
            return Invalid;
    }
};
