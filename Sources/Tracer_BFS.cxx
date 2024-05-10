#include "Graph.hxx"

TRoute BFS::calculateRoute(const Cell & start, const Cell & end) const
{
    TCellSet visited;
    TCellQueue toVisit;
    TCellMap parents;

    // traverse edges from the end until the start is found

    const Cell * cell = &end;

    for (;; toVisit.pop()) {
        if (toVisit.empty())
            break;

        visited.insert(*cell);

        for (const Cell & neighbour : _edges.at(*cell)) {
            if (visited.find(neighbour) == visited.end()) {
                toVisit.push(neighbour);
                parents.insert(std::make_pair(neighbour, *cell));
            }
        }

        cell = &toVisit.front();
        if (*cell == start)
            break;
    }

    if (*cell != start)
        throw std::runtime_error("Unable to find the route");

    // assemble the route

    TRoute route{*cell};

    for (; *cell != end; cell = &parents[*cell]) {
        route.push_back(*cell);
    }

    route.push_back(end);

    return route;
}
