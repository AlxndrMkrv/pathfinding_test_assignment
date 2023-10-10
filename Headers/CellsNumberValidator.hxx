#pragma once

#include <QValidator>

class CellsNumberValidator : public QIntValidator
{
public:
    using QIntValidator::QIntValidator;

    virtual QValidator::State validate(QString &text, int &pos) const override {
        // Try to convert QString to integer value
        bool success;
        int value = text.toInt(&success);

        // Give intermediate status to an empty string or too small integers
        if (! text.size() || (success && value < bottom()))
            return Intermediate;

        // Accept strings containing an integer in a given range
        else if (success && bottom() <= value && value <= top())
            return Acceptable;

        // Decline everything else
        else
            return Invalid;
    }
};
