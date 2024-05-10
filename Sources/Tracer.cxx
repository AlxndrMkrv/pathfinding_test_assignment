#include "Tracer.hxx"
#include <map>
#include <queue>

using CellMap = std::map<Cell, Cell, Cell::Compare>;
using CellQueue = std::queue<Cell>;

AbstractTracer::AbstractTracer(const EdgeContainer & edges) : _edges(edges) {}

Route AbstractTracer::findRoute(const Cell & start, const Cell & end) const
{
    // throw exception if start/end is not in the graph
    if (!_edges.count(start))
        throw std::out_of_range("Start cell is out of Graph");
    if (!_edges.count(end))
        throw std::out_of_range("End cell is out of Graph");

    // return if the start is equal to the end
    if (start == end) {
        return Route{start};
    }

    return implementation(start, end);
}

/* ************************************************************************** *
 *                              Deep-first search                             */

Route DFS::implementation(const Cell & start, const Cell & end) const
{
    // prepare visited cells set
    CellSet visited{start};

    Route route{start};

    // reserve 3/4 of nodes number cells in route
    route.reserve(nodesNumber() * 3 / 4);
    // run recursive DFS search algorithm
    trace(route, visited, end);
    // remove extra space from route vector
    route.shrink_to_fit();
    return route;
}

void DFS::trace(Route & path, CellSet & visited, const Cell & end) const
{
    for (Cell node : _edges.at(path.back())) {
        // append the node to the path if not visited
        if (!visited.count(node)) {
            visited.insert(node);
            path.push_back(node);
            // break the loop if end node found
            if (node == end)
                break;

            // go one level deeper
            trace(path, visited, end);

            // break the loop if end node found
            if (path.back() == end)
                break;

            // remove the node from path
            path.pop_back();
        }
    }
}

/* ************************************************************************** *
 *                            Breadth-first search                            */

Route BFS::implementation(const Cell & start, const Cell & end) const
{
    CellSet visited;
    CellQueue toVisit;
    CellMap parents;

    // traverse edges from the end until the start is found

    const Cell * cell = &end;

    while (*cell != start) {
        // get neighbours of the current cell
        for (const Cell & neighbour : _edges.at(*cell)) {
            // skip visited neighbours
            if (visited.contains(neighbour))
                continue;

            // add the neighbour to the queue
            toVisit.push(neighbour);
            parents.insert(std::make_pair(neighbour, *cell));
        }

        visited.insert(*cell);

        // get next cell from queue
        if (toVisit.empty())
            break;

        cell = &toVisit.front();
        toVisit.pop();
    }

    if (*cell != start)
        throw std::runtime_error("Unable to find the destination");

    // assemble the route
    Route route;

    for (; *cell != end; cell = &parents[*cell]) {
        route.push_back(*cell);
    }

    route.push_back(end);

    return route;
}
