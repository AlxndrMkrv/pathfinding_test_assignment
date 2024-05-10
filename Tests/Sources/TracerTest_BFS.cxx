#include "TracerTest.hxx"
#include <algorithm>
#include <vector>

int main()
{
    std::vector<bool> results{tracerTest_4_2_AB<BFS>(),
                              tracerTest_4_2_BA<BFS>(), tracerTest_5_5<BFS>(),
                              tracerTest_7_5<BFS>()};

    // set breakpoint here if something goes wrong
    if (std::all_of(results.begin(), results.end(), [](bool i) { return i; }))
        return 0;
    else
        return 1;
}
