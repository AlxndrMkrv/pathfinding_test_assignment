#include "Graph.hxx"

TRoute DFS::findRoute(const Cell &start, const Cell &end) const
{
    // throw exception if start/end not in graph
    if (! _edges.count(start))
        throw std::out_of_range("Start cell is out of Graph");
    if (! _edges.count(end))
        throw std::out_of_range("End cell is out of Graph");

    TRoute route {start};

    // return if start is equal to end
    if (start == end) {
        route.shrink_to_fit();
        return route;
    }

    // prepare visited cells set
    TCellSet visited {start};

    // reserve 3/4 of nodes number cells in route
    route.reserve(nodesNumber() * 3/4);
    // run recursive DFS search algorithm
    trace(route, visited, end);
    // remove extra space from route vector
    route.shrink_to_fit();
    return route;
}

void DFS::trace(TRoute &path, TCellSet &visited, const Cell &end) const
{
    for (Cell node : _edges.at(path.back())) {
        // append the node to the path if not visited
        if (! visited.count(node)) {
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
