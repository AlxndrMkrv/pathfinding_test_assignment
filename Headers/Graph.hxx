#pragma once

#include "CellContainers.hxx"

class Graph {
public:
    Graph() = default;
    Graph(const uint8_t & columns, const uint8_t & rows);

    void rebuild(const uint8_t & columns, const uint8_t & rows);
    void add(const Cell & node);
    void remove(const Cell & node) noexcept;

    unsigned int nodesNumber() const noexcept;
    unsigned int edgesNumber() const noexcept;
    bool isNeighbours(const Cell & a, const Cell & b) const noexcept;
    bool isExists(const Cell & node) const noexcept;

    inline const EdgeContainer & edges() const { return _edges; }

private:
    EdgeContainer _edges;
};
