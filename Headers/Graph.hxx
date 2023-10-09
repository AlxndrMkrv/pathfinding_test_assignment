#pragma once

#include <cinttypes>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Cell.hxx"

using TRoute = std::vector<Cell>;
using TCellSet = std::unordered_set<Cell, Cell::Hash, Cell::EqualTo>;

class AbstractGraph
{
    using TContainer = std::unordered_map<Cell, TCellSet,
                                          Cell::Hash, Cell::EqualTo>;
    using TRoutes = std::vector<Cell>;
public:
    AbstractGraph() = default;
    AbstractGraph(const uint8_t &columns, const uint8_t &rows);

    void add(const Cell &node);
    void remove(const Cell &node) noexcept;

    unsigned int nodesNumber() const noexcept;
    unsigned int edgesNumber() const noexcept;
    bool isNeighbours(const Cell &a, const Cell &b) const noexcept;
    bool isExists(const Cell &node) const noexcept;

    virtual TRoute findRoute(const Cell &start, const Cell &end) const = 0;

protected:
    TContainer _edges;
};

/* ************************************************************************** *
 *                              Deep-first search                             */

class DFS : public AbstractGraph
{
public:
    using AbstractGraph::AbstractGraph;
    virtual TRoute findRoute(const Cell &start, const Cell &end) const override;
private:
    void trace(TRoute &path, TCellSet &visited, const Cell &end) const;
};
