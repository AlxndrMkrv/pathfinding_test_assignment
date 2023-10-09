#include "RouteTest.hxx"
#include <algorithm>
#include <vector>

int main()
{
    std::vector<bool> results {routeTest_4_2_AB<DFS>(),
                               routeTest_4_2_BA<DFS>(),
                               routeTest_5_5<DFS>(),
                               routeTest_7_5<DFS>()};

    // set breakpoint here if something goes wrong
    if (std::all_of(results.begin(), results.end(),
                    [](bool i){return i;}))
        return 0;
    else
        return 1;
}
