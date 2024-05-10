#pragma once

#include "Cell.hxx"
#include <QDebug>

class MatrixCell : public Cell {
    // New field for a Cell structure
    bool _invalid;

public:
    // Static method to create invalid cell
    static MatrixCell Invalid() { return MatrixCell{0, 0, true}; }

    // Constructors
    MatrixCell(const uint8_t & c, const uint8_t & r) :
        Cell(c, r), _invalid(false)
    {
    }

    MatrixCell(const uint8_t & c, const uint8_t & r, const bool & i) :
        Cell(c, r), _invalid(i)
    {
    }

    MatrixCell(const Cell & cell) : Cell(cell), _invalid(false) {}

    // Flags
    inline bool isInvalid() const { return _invalid; }
    inline bool isValid() const { return !_invalid; }

    // Equality operators
    inline bool operator==(const MatrixCell & other) const
    {
        return Cell::operator==(other) && _invalid == other._invalid;
    }

    inline bool operator!=(const MatrixCell & other) const
    {
        return !operator==(other);
    }

    // Converter to std::string
    operator std::string() const
    {
        return _invalid ? "(-, -)" : Cell::operator std::string();
    }

    // Stream operator for std::ostream
    friend std::ostream & operator<<(std::ostream & os, const MatrixCell & cell)
    {
        os << cell._invalid ? std::string("(-, -)") : static_cast<Cell>(cell);
        return os;
    }

    // Converter to QString
    operator QString() const
    {
        return _invalid ? "(-, -)"
                        : "(" + QString::number(col) + ", " +
                              QString::number(row) + ")";
    }

    // Stream operator for QDebug
    friend QDebug & operator<<(QDebug & out, const MatrixCell & cell)
    {
        out << QString(std::string(cell).c_str());
        return out;
    }
};
