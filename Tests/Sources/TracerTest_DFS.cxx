#include "TracerTest.hxx"
#include <algorithm>
#include <vector>

int main()
{
    std::vector<bool> results{tracerTest_4_2_AB<DFS>(),
                              tracerTest_4_2_BA<DFS>(), tracerTest_5_5<DFS>(),
                              tracerTest_7_5<DFS>()};

    // set breakpoint here if something goes wrong
    if (std::all_of(results.begin(), results.end(),
                    [](bool i){return i;}))
        return 0;
    else
        return 1;
}
