#include <iostream>
#include "tests.h"

typedef unsigned int ui32;

int main()
{
    for (ui32 queriesNumber = 1000000; queriesNumber <= 10000000; queriesNumber += 1000000)
    {
        GlobalTestResult globalTestResult;
        globalTestResult.execute(queriesNumber);
        double time = globalTestResult.time;
        std::cout.setf ( std::ios::fixed );
        std::cout.precision(10);
        std::cout << 1000000000 * time / (double)queriesNumber << '\n';
    }
    return 0;
}
