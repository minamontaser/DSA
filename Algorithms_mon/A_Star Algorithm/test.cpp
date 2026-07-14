#include "A_Star.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

vector<vector<ll>> generateGrid(
    int n,
    int m,
    double obstacleProbability
){
    vector<vector<ll>> grid(
        n,
        vector<ll>(m, 0)
    );

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> dist(0.0, 1.0);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(dist(gen) < obstacleProbability)
                grid[i][j] = 1;
        }
    }

    return grid;
}

void runTest(
    const string& name,
    vector<vector<ll>> grid,
    pair<ll,ll> startPos,
    pair<ll,ll> goalPos
){
    cout << "\n========== "
         << name
         << " ==========\n";

    grid[startPos.first][startPos.second] = 0;
    grid[goalPos.first][goalPos.second] = 0;

    cell start(startPos.first, startPos.second);
    cell goal(goalPos.first, goalPos.second);

    auto begin =
        chrono::high_resolution_clock::now();

    AStarResult result =
        AStar(grid, start, goal);

    auto end =
        chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<
            chrono::milliseconds
        >(end - begin);

    cout << "Success: "
         << boolalpha
         << result.success
         << '\n';

    cout << "Path length: "
         << result.path.size()
         << '\n';

    cout << "Execution time: "
         << duration.count()
         << " ms\n";

    if(result.success){
        cout << "Goal Cost (g): "
             << result.path.back().g
             << '\n';
    }
}

int main(){

    try{

        // Test 1
        {
            vector<vector<ll>> grid(
                1,
                vector<ll>(1, 0)
            );

            runTest(
                "1x1 Grid",
                grid,
                {0,0},
                {0,0}
            );
        }

        // Test 2
        {
            auto grid =
                generateGrid(
                    10,
                    10,
                    0.20
                );

            runTest(
                "10x10 Sparse",
                grid,
                {0,0},
                {9,9}
            );
        }

        // Test 3
        {
            auto grid =
                generateGrid(
                    100,
                    100,
                    0.10
                );

            runTest(
                "100x100 Sparse",
                grid,
                {0,0},
                {99,99}
            );
        }

        // Test 4
        {
            auto grid =
                generateGrid(
                    100,
                    100,
                    0.40
                );

            runTest(
                "100x100 Dense",
                grid,
                {0,0},
                {99,99}
            );
        }

        // Test 5
        {
            auto grid =
                generateGrid(
                    500,
                    500,
                    0.15
                );

            runTest(
                "500x500 Stress",
                grid,
                {0,0},
                {499,499}
            );
        }

        // Test 6
        {
            auto grid =
                generateGrid(
                    1000,
                    1000,
                    0.10
                );

            runTest(
                "1000x1000 Stress",
                grid,
                {0,0},
                {999,999}
            );
        }

        // Test 7
        {
            auto grid =
                generateGrid(
                    50,
                    50,
                    0.25
                );

            runTest(
                "Start Equals Goal",
                grid,
                {25,25},
                {25,25}
            );
        }

        // Test 8
        {
            vector<vector<ll>> grid(
                50,
                vector<ll>(50, 0)
            );

            for(int j = 0; j < 50; j++)
                grid[25][j] = 1;

            runTest(
                "No Path",
                grid,
                {0,0},
                {49,49}
            );
        }

        // Test 9
        {
            vector<vector<ll>> grid = {
                {0,1},
                {1,0}
            };

            runTest(
                "Corner Cutting Check",
                grid,
                {0,0},
                {1,1}
            );
        }

    }
    catch(const exception& ex){
        cerr << "\nException: "
             << ex.what()
             << '\n';
    }

    return 0;
}