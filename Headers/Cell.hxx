#pragma once

#include <cstdint>
#include <ostream>
#include <string>

struct Cell {
    union {
        struct {
            uint8_t col;
            uint8_t row;
        };
        uint16_t id;
    };

    Cell() = default;
    Cell(const uint8_t & c, const uint8_t & r) : col(c), row(r) {}

    inline bool operator==(const Cell & other) const { return id == other.id; }
    inline bool operator!=(const Cell & other) const { return id != other.id; }

    friend std::ostream & operator<<(std::ostream & os, const Cell & cell)
    {
        os << "(" << std::to_string(cell.col) << ", "
           << std::to_string(cell.row) << ")";
        return os;
    }

    operator std::string() const
    {
        return "(" + std::to_string(col) + ", " + std::to_string(row) + ")";
    }

    /* Nested structs for std containers compability */
    struct Hash {
        inline size_t operator()(const Cell & cell) const { return cell.id; }
    };

    struct EqualTo {
        inline bool operator()(const Cell & lhs, const Cell & rhs) const
        {
            return lhs.id == rhs.id;
        }
    };

    struct Compare {
        inline bool operator()(const Cell & lhs, const Cell & rhs) const
        {
            return lhs.id < rhs.id;
        }
    };
};
