#include "Graph.hxx"
#include <limits>
#include <vector>
#include <sstream>

AbstractGraph::AbstractGraph(const uint8_t &cols, const uint8_t &rows)
{
    if (std::min(cols, rows) < 2)
        throw std::out_of_range("Graph size must not be less than 4 nodes");

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

void AbstractGraph::add(const Cell &node)
{
    // Skip if node already exists
    if (! _edges.count(node)) {
        std::vector<Cell> neighbours;
        neighbours.reserve(4);

        // Add left neighbour if possible
        if (node.col &&
            _edges.count(Cell(node.col - 1, node.row)))
            neighbours.push_back(Cell(node.col - 1, node.row));

        // Add right neighbour if possible
        if (node.col < std::numeric_limits<decltype(node.col)>::max() &&
            _edges.count(Cell(node.col + 1, node.row)))
            neighbours.push_back(Cell(node.col + 1, node.row));

        // Add up neighbour if possible
        if (node.row &&
            _edges.count(Cell(node.col, node.row - 1)))
            neighbours.push_back(Cell(node.col, node.row - 1));

        // Add down neighbour if possible
        if (node.row < std::numeric_limits<decltype(node.row)>::max() &&
            _edges.count(Cell(node.col, node.row + 1)))
            neighbours.push_back(Cell(node.col, node.row + 1));

        // Create connections with neighbours
        for (Cell neighbour : neighbours) {
            _edges[neighbour].insert(node);
            _edges[node].insert(neighbour);
        }

        // Throw exception if the node is still not exist
        // (can't be connected to the graph)
        if (! _edges.count(node)) {
            std::stringstream ss;
            ss << "Cell" << node << " can not be connected to any other node";
            throw std::out_of_range(ss.str());
        }
    }
}

void AbstractGraph::remove(const Cell &node) noexcept
{
    for (auto neighbour : _edges[node])
        _edges[neighbour].erase(node);
    _edges.erase(node);
}

unsigned int AbstractGraph::nodesNumber() const noexcept
{
    return _edges.size();
}

unsigned int AbstractGraph::edgesNumber() const noexcept
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

bool AbstractGraph::isExists(const Cell &node) const noexcept
{
    return _edges.count(node);
}
