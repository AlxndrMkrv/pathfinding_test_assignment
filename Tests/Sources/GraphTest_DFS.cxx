#include "Graph.hxx"
#include "GraphTest.hxx"
#include <cinttypes>
#include <vector>


int main()
{
    const uint8_t cols = 10, rows = 10;

    std::vector<bool> results {TestingGraph<DFS>::TestTooFewNodes(),
                               TestingGraph<DFS>::TestCreation(cols, rows),
                               TestingGraph<DFS>::TestRemoveDiagonal(cols, rows),
                               TestingGraph<DFS>::TestRemoveNonExist(cols, rows),
                               TestingGraph<DFS>::TestAddNeighbour(cols, rows),
                               TestingGraph<DFS>::TestAddNonNeighbour(cols, rows)};

    // set breakpoint here if something goes wrong
    if (std::all_of(results.begin(), results.end(),
                    [](bool i){return i;}))
        return 0;
    else
        return 1;
}
