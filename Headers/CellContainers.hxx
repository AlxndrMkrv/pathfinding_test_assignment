#pragma once

#include "Cell.hxx"
#include <unordered_map>
#include <unordered_set>
#include <vector>

using CellSet = std::unordered_set<Cell, Cell::Hash, Cell::EqualTo>;
using EdgeContainer =
    std::unordered_map<Cell, CellSet, Cell::Hash, Cell::EqualTo>;
using Route = std::vector<Cell>;
