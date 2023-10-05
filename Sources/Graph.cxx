#include "Graph.hxx"

AbstractGraph::AbstractGraph(const uint8_t &cols, const uint8_t &rows)
{
    for (auto r = 0; r < rows; ++r) {
        for (auto c = 0; c < cols; ++c) {
            // Create connection with upper neighbour on non-zero rows
            if (r) {
                _edges[Cell(c, r)].insert(Cell(c, r-1));
                _edges[Cell(c, r-1)].insert(Cell(c, r));
            }
            // Create connection with left neighbour on non-zero columns
            if (c) {
                _edges[Cell(c, r)].insert(Cell(c-1, r));
                _edges[Cell(c-1, r)].insert(Cell(c, r));
            }
        }
    }
}

void AbstractGraph::remove(const Cell &node)
{
    for (auto neighbour : _edges[node])
        _edges[neighbour].erase(node);
    _edges.erase(node);
}

unsigned int AbstractGraph::nodesNumber() const
{
    return _edges.size();
}

unsigned int AbstractGraph::edgesNumber() const
{
    unsigned int counter = 0;
    for (auto & it: _edges)
        counter += it.second.size();
    return counter;
}

bool AbstractGraph::isNeighbours(const Cell &a, const Cell &b) const noexcept
{
    // _edges.count() guards _edges.at() from throwing out_of_range exception
    return _edges.count(a) && _edges.at(a).count(b) &&
           _edges.count(b) && _edges.at(b).count(a);
}
