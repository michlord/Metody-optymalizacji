#include "NaiveHamiltonianCycleFinder.h"
#include "OptimisedHamiltonianCycleFinder.h"
#include "RandomGraphFactory.h"
#include "TestCase.h"
#include "Clock.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>


void setRandomSeed()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

std::vector<TestCase> getTestCases()
{
    return {
        { 10, 24 },
        { 10, 45 },
        { 10, 70 },
        { 13, 30 },
        { 13, 50 },
        { 13, 80 },
        // { 15, 30 },
        // { 15, 50 },
        // { 15, 80 }
    };
}

void printStats(
    const std::string& finderName,
    unsigned int solutions,
    const Clock::Duration& searchFirstTime,
    const Clock::Duration& searchAllTime)
{
    std::cout << "Finder: " << finderName << "\n";
    std::cout << "=================\n";
    std::cout << "Solutions found: " << solutions << "\n";
    std::cout << "First found in:  " << searchFirstTime.asMilliseconds<double>() << "ms" << "\n";
    std::cout << "All found in:    " << searchAllTime.asMilliseconds<double>()   << "ms" << "\n";

    std::cout << std::endl;
}

void test(const Graph& G, HamiltonianCycleFinder& cycleFinder)
{
    static Clock clock;

    clock.reset();
    auto cycle = cycleFinder.findFirstIn(G);
    auto searchFirstTime = clock.getElapsedTime();


    clock.reset();
    auto cycles = cycleFinder.findAllIn(G);
    auto searchAllTime = clock.getElapsedTime();

    printStats(cycleFinder.name, cycles.size(), searchFirstTime, searchAllTime);
}

int main()
{
    std::vector<TestCase> testCases = getTestCases();

    NaiveHamiltonianCycleFinder naiveFinder { "Naive" };
    OptimisedHamiltonianCycleFinder optimisedFinder { "Optimised" };

    setRandomSeed();

    for(const auto& testCase : testCases)
    {
        Graph G = RandomGraphFactory::generate(testCase.vertexCount, testCase.edgeCount);

        std::cout << "Test case:\n";
        std::cout << "==========\n";
        std::cout << "Vertices: " << testCase.vertexCount << "\n";
        std::cout << "Edges:    " << testCase.edgeCount << "\n\n";

        // std::cout << "Graph\n";
        // std::cout << "=====\n";
        // std::cout << G << std::endl;

        test(G, naiveFinder);
        test(G, optimisedFinder);

        std::cout << "\n\n";
    }

    // system("pause");

    return 0;
}
