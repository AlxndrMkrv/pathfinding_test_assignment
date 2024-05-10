#include "Graph.hxx"

TRoute DFS::calculateRoute(const Cell & start, const Cell & end) const
{
    // prepare visited cells set
    TCellSet visited {start};

    TRoute route{start};

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
