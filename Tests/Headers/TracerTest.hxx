#pragma once

#include "Graph.hxx"
#include "Tracer.hxx"

template <class TTracer>
static bool __checkRoute(const TTracer & tracer, const Graph & graph,
                         const Cell & start, const Cell & end)
{
    Route route = tracer.findRoute(start, end);

    bool success = route.size() && route.front() == start && route.back() == end;
    if (success)
        for (auto i = 1; i < route.size(); ++i)
            success &= graph.isNeighbours(route[i - 1], route[i]);
    return success;
}

template <class TTracer>
bool tracerTest_4_2_AB()
{
    /*     0   1   2   3
     *   ╔═══╦═══╦═══╦═══╗
     * 0 ║   ║ A ║ B ║   ║
     *   ╠═══╬═══╬═══╬═══╣
     * 1 ║   ║   ║   ║   ║
     *   ╚═══╩═══╩═══╩═══╝
     */

    static_assert(std::is_base_of<AbstractTracer, TTracer>::value,
                  "Invalid Tracer type given");

    Graph graph(4, 2);
    TTracer tracer(graph.edges());
    return __checkRoute<TTracer>(tracer, graph, {1, 0}, {2, 0});
}

template <class TTracer>
bool tracerTest_4_2_BA()
{
    /*     0   1   2   3
     *   ╔═══╦═══╦═══╦═══╗
     * 0 ║   ║ B ║ A ║   ║
     *   ╠═══╬═══╬═══╬═══╣
     * 1 ║   ║   ║   ║   ║
     *   ╚═══╩═══╩═══╩═══╝
     */

    static_assert(std::is_base_of<AbstractTracer, TTracer>::value,
                  "Invalid Tracer type given");

    Graph graph(4, 2);
    TTracer tracer(graph.edges());
    return __checkRoute<TTracer>(tracer, graph, {2, 0}, {1, 0});
}

template <class TTracer>
bool tracerTest_5_5()
{
    /*     0   1   2   3   4
     *   ╔═══╦═══╦═══╦═══╦═══╗
     * 0 ║   ║   ║   ║ X ║   ║
     *   ╠═══╬═══╬═══╬═══╬═══╣
     * 1 ║ X ║   ║ ┌ ║ B ║   ║
     *   ╠═══╬═══╬═══╬═══╬═══╣
     * 2 ║   ║ X ║ ├ ║ ┘ ║ X ║
     *   ╠═══╬═══╬═══╬═══╬═══╣
     * 3 ║   ║ ┌ ║ ┤ ║ X ║   ║
     *   ╠═══╬═══╬═══╬═══╬═══╣
     * 4 ║   ║ A ║ ┘ ║   ║   ║
     *   ╚═══╩═══╩═══╩═══╩═══╝
     */

    static_assert(std::is_base_of<AbstractTracer, TTracer>::value,
                  "Invalid Graph type given");

    Graph graph(5, 5);
    for (Cell c : {Cell{3, 0}, Cell{0, 1}, Cell{1, 2}, Cell{4, 2}, Cell{3, 3}})
        graph.remove(c);

    TTracer tracer(graph.edges());
    return __checkRoute<TTracer>(tracer, graph, {1, 4}, {3, 1});
}

template <class TTracer>
bool tracerTest_7_5()
{
    /*     0   1   2   3   4   5   6
     *   ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╗
     * 0 ║ ┌ ║ ─ ║ ─ ║ B ║ X ║   ║   ║
     *   ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╣
     * 1 ║ │ ║ X ║ X ║ X ║   ║ A ║ ┐ ║
     *   ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╣
     * 2 ║ └ ║ ─ ║ ┐ ║ X ║   ║ X ║ │ ║
     *   ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╣
     * 3 ║ X ║ X ║ │ ║ X ║ X ║ X ║ │ ║
     *   ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╣
     * 4 ║   ║   ║ └ ║ ─ ║ ─ ║ ─ ║ ┘ ║
     *   ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╝
     */

    static_assert(std::is_base_of<AbstractTracer, TTracer>::value,
                  "Invalid Graph type given");

    Graph graph(7, 5);
    for (Cell c : {Cell{4, 0},
                   Cell{1, 1}, Cell{2, 1}, Cell{3, 1},
                   Cell{3, 2}, Cell{5, 2},
                   Cell{0, 3}, Cell{1, 3}, Cell{3, 3}, Cell{4, 3}, Cell{5, 3}})
        graph.remove(c);

    TTracer tracer(graph.edges());
    return __checkRoute<TTracer>(tracer, graph, {5, 1}, {3, 0});
}
