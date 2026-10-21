#include "A_Star_Bidirectional.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// ============================================================
// Helpers
// ============================================================

void printPath(const vector<cell>& path)
{
    cout << "Path: ";

    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << "("
             << path[i].x
             << ","
             << path[i].y
             << ")";

        if (i + 1 < path.size())
            cout << " -> ";
    }

    cout << '\n';
}

void printGrid(
    const vector<vector<ll>>& grid,
    const cell& start,
    const cell& goal,
    const vector<cell>& path = {}
)
{
    vector<vector<char>> display(
        grid.size(),
        vector<char>(grid[0].size(), '.')
    );

    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] != 0)
                display[i][j] = '#';
        }
    }

    for (const cell& node : path)
    {
        if (node.x >= 0 &&
            node.x < static_cast<ll>(grid.size()) &&
            node.y >= 0 &&
            node.y < static_cast<ll>(grid[0].size()))
        {
            display[node.x][node.y] = '*';
        }
    }

    display[start.x][start.y] = 'S';
    display[goal.x][goal.y] = 'G';

    cout << '\n';

    for (size_t i = 0; i < display.size(); ++i)
    {
        for (size_t j = 0; j < display[i].size(); ++j)
        {
            cout << display[i][j] << ' ';
        }

        cout << '\n';
    }

    cout << '\n';
}

bool approximatelyEqual(ld a, ld b, ld epsilon = 1e-9L)
{
    return fabsl(a - b) <= epsilon;
}

int passed = 0;
int failed = 0;

void reportTest(
    const string& name,
    bool condition
)
{
    if (condition)
    {
        cout << "[PASS] " << name << '\n';
        ++passed;
    }
    else
    {
        cout << "[FAIL] " << name << '\n';
        ++failed;
    }
}

void runTest(
    const string& name,
    const vector<vector<ll>>& grid,
    const cell& start,
    const cell& goal,
    const AStarConfig& config,
    bool expectedSuccess,
    ld expectedCost = -1.0L,
    bool showGrid = false
)
{
    cout << "\n============================================================\n";
    cout << name << '\n';
    cout << "============================================================\n";

    try
    {
        AStarResult result =
            AStar(grid, start, goal, config);

        cout << "Success: "
             << boolalpha
             << result.success
             << '\n';

        cout << "Path length: "
             << result.pathLength
             << '\n';

        cout << "Cost: "
             << fixed
             << setprecision(6)
             << static_cast<double>(result.bestCost)
             << '\n';

        if (!result.path.empty())
            printPath(result.path);

        if (showGrid)
            printGrid(grid, start, goal, result.path);

        bool successCorrect =
            result.success == expectedSuccess;

        bool costCorrect = true;

        if (expectedSuccess && expectedCost >= 0.0L)
        {
            costCorrect =
                approximatelyEqual(
                    result.bestCost,
                    expectedCost
                );
        }

        reportTest(
            name + " - success",
            successCorrect
        );

        if (expectedSuccess && expectedCost >= 0.0L)
        {
            reportTest(
                name + " - cost",
                costCorrect
            );
        }
    }
    catch (const exception& e)
    {
        cout << "Exception: "
             << e.what()
             << '\n';

        reportTest(
            name + " - unexpected exception",
            false
        );
    }
}

// ============================================================
// Main
// ============================================================

int main()
{
    cout << "============================================================\n";
    cout << "        Bidirectional A* Test Suite\n";
    cout << "============================================================\n";


    // ========================================================
    // Configuration 1
    // Standard 4-directional movement
    // ========================================================

    AStarConfig fourWay;
    fourWay.heuristic = Heuristic::Manhattan;
    fourWay.allowDiagonal = false;
    fourWay.preventCornerCutting = false;
    fourWay.straightCost = 1.0L;
    fourWay.diagonalCost = DIAGONAL_COST;


    // ========================================================
    // Configuration 2
    // Standard 8-directional movement
    // ========================================================

    AStarConfig eightWay;
    eightWay.heuristic = Heuristic::Diagonal;
    eightWay.allowDiagonal = true;
    eightWay.preventCornerCutting = false;
    eightWay.straightCost = 1.0L;
    eightWay.diagonalCost = DIAGONAL_COST;


    // ========================================================
    // Test 1
    // Start == Goal
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        cell start(1, 1);
        cell goal(1, 1);

        runTest(
            "Test 1 - Start equals Goal",
            grid,
            start,
            goal,
            eightWay,
            true,
            0.0L,
            true
        );
    }


    // ========================================================
    // Test 2
    // Simple horizontal path
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0, 0, 0}
        };

        cell start(0, 0);
        cell goal(0, 4);

        runTest(
            "Test 2 - Simple horizontal path",
            grid,
            start,
            goal,
            fourWay,
            true,
            4.0L,
            true
        );
    }


    // ========================================================
    // Test 3
    // Simple vertical path
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0},
            {0},
            {0},
            {0},
            {0}
        };

        cell start(0, 0);
        cell goal(4, 0);

        runTest(
            "Test 3 - Simple vertical path",
            grid,
            start,
            goal,
            fourWay,
            true,
            4.0L,
            true
        );
    }


    // ========================================================
    // Test 4
    // Straight diagonal
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 2);

        ld expected =
            2.0L * DIAGONAL_COST;

        runTest(
            "Test 4 - Pure diagonal path",
            grid,
            start,
            goal,
            eightWay,
            true,
            expected,
            true
        );
    }


    // ========================================================
    // Test 5
    // Diagonal movement disabled
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 2);

        runTest(
            "Test 5 - Diagonal disabled",
            grid,
            start,
            goal,
            fourWay,
            true,
            4.0L,
            true
        );
    }


    // ========================================================
    // Test 6
    // Obstacle forces detour
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0}
        };

        cell start(1, 0);
        cell goal(1, 4);

        runTest(
            "Test 6 - Obstacle forces detour",
            grid,
            start,
            goal,
            fourWay,
            true,
            6.0L,
            true
        );
    }


    // ========================================================
    // Test 7
    // Completely blocked
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 0}
        };

        cell start(0, 0);
        cell goal(0, 2);

        runTest(
            "Test 7 - Completely blocked",
            grid,
            start,
            goal,
            fourWay,
            false,
            -1.0L,
            true
        );
    }


    // ========================================================
    // Test 8
    // Start blocked
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {1, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 2);

        runTest(
            "Test 8 - Start blocked",
            grid,
            start,
            goal,
            eightWay,
            false,
            -1.0L,
            true
        );
    }


    // ========================================================
    // Test 9
    // Goal blocked
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 1}
        };

        cell start(0, 0);
        cell goal(2, 2);

        runTest(
            "Test 9 - Goal blocked",
            grid,
            start,
            goal,
            eightWay,
            false,
            -1.0L,
            true
        );
    }


    // ========================================================
    // Test 10
    // Corner cutting allowed
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 1},
            {1, 0}
        };

        cell start(0, 0);
        cell goal(1, 1);

        AStarConfig config = eightWay;
        config.preventCornerCutting = false;

        runTest(
            "Test 10 - Corner cutting allowed",
            grid,
            start,
            goal,
            config,
            true,
            DIAGONAL_COST,
            true
        );
    }


    // ========================================================
    // Test 11
    // Corner cutting prevented
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 1},
            {1, 0}
        };

        cell start(0, 0);
        cell goal(1, 1);

        AStarConfig config = eightWay;
        config.preventCornerCutting = true;

        runTest(
            "Test 11 - Corner cutting prevented",
            grid,
            start,
            goal,
            config,
            false,
            -1.0L,
            true
        );
    }


    // ========================================================
    // Test 12
    // Cost configuration: 10 / 14
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 2);

        AStarConfig config;
        config.heuristic = Heuristic::Diagonal;
        config.allowDiagonal = true;
        config.preventCornerCutting = false;
        config.straightCost = 10.0L;
        config.diagonalCost = 14.0L;

        runTest(
            "Test 12 - Custom costs 10 / 14",
            grid,
            start,
            goal,
            config,
            true,
            28.0L,
            true
        );
    }


    // ========================================================
    // Test 13
    // Expensive diagonal
    //
    // straight = 1
    // diagonal = 3
    //
    // Optimal path should prefer two straight moves
    // over one diagonal wherever appropriate.
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0},
            {0, 0}
        };

        cell start(0, 0);
        cell goal(1, 1);

        AStarConfig config;
        config.heuristic = Heuristic::Diagonal;
        config.allowDiagonal = true;
        config.preventCornerCutting = false;
        config.straightCost = 1.0L;
        config.diagonalCost = 3.0L;

        runTest(
            "Test 13 - Expensive diagonal",
            grid,
            start,
            goal,
            config,
            true,
            2.0L,
            true
        );
    }


    // ========================================================
    // Test 14
    // Euclidean heuristic
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };

        cell start(0, 0);
        cell goal(4, 4);

        AStarConfig config = eightWay;
        config.heuristic = Heuristic::Euclidean;

        runTest(
            "Test 14 - Euclidean heuristic",
            grid,
            start,
            goal,
            config,
            true,
            4.0L * DIAGONAL_COST,
            true
        );
    }


    // ========================================================
    // Test 15
    // Large open grid
    // ========================================================

    {
        vector<vector<ll>> grid(
            20,
            vector<ll>(20, 0)
        );

        cell start(0, 0);
        cell goal(19, 19);

        runTest(
            "Test 15 - Large open grid",
            grid,
            start,
            goal,
            eightWay,
            true,
            19.0L * DIAGONAL_COST,
            false
        );
    }


    // ========================================================
    // Test 16
    // Maze-like obstacle configuration
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0, 1, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0}
        };

        cell start(0, 0);
        cell goal(4, 6);

        runTest(
            "Test 16 - Maze-like grid",
            grid,
            start,
            goal,
            fourWay,
            true,
            -1.0L,
            true
        );
    }


    // ========================================================
    // Test 17
    // Non-rectangular grid
    // Should throw.
    // ========================================================

    {
        cout << "\n============================================================\n";
        cout << "Test 17 - Non-rectangular grid\n";
        cout << "============================================================\n";

        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0},
            {0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 2);

        bool threw = false;

        try
        {
            AStar(grid, start, goal, fourWay);
        }
        catch (const invalid_argument&)
        {
            threw = true;
        }

        reportTest(
            "Test 17 - Non-rectangular grid throws",
            threw
        );
    }


    // ========================================================
    // Test 18
    // Empty grid
    // ========================================================

    {
        cout << "\n============================================================\n";
        cout << "Test 18 - Empty grid\n";
        cout << "============================================================\n";

        vector<vector<ll>> grid;

        cell start(0, 0);
        cell goal(0, 0);

        AStarResult result =
            AStar(grid, start, goal, fourWay);

        reportTest(
            "Test 18 - Empty grid fails",
            !result.success
        );
    }


    // ========================================================
    // Test 19
    // Manhattan heuristic with diagonal movement
    // This should be rejected by the implementation once
    // configuration validation is added.
    //
    // Currently this test only demonstrates the configuration.
    // ========================================================

    {
        cout << "\n============================================================\n";
        cout << "Test 19 - Manhattan + diagonal movement\n";
        cout << "============================================================\n";

        vector<vector<ll>> grid =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 2);

        AStarConfig config = eightWay;
        config.heuristic = Heuristic::Manhattan;

        bool threw = false;

        try
        {
            AStar(grid, start, goal, config);
        }
        catch (const invalid_argument&)
        {
            threw = true;
        }

        cout << "Exception thrown: "
             << boolalpha
             << threw
             << '\n';

        cout << "NOTE: This test expects rejection only if your AStar()\n"
             << "validates Manhattan + diagonal movement.\n";

        reportTest(
            "Test 19 - Manhattan + diagonal rejected",
            threw
        );
    }


    // ========================================================
    // Test 20
    // Different custom costs
    // ========================================================

    {
        vector<vector<ll>> grid =
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        };

        cell start(0, 0);
        cell goal(2, 3);

        AStarConfig config;
        config.heuristic = Heuristic::Diagonal;
        config.allowDiagonal = true;
        config.preventCornerCutting = false;
        config.straightCost = 2.0L;
        config.diagonalCost = 3.0L;

        // 2 diagonal + 1 straight
        // = 3 + 3 + 2
        // = 8

        runTest(
            "Test 20 - Custom costs 2 / 3",
            grid,
            start,
            goal,
            config,
            true,
            8.0L,
            true
        );
    }


    // ========================================================
    // Final summary
    // ========================================================

    cout << "\n\n============================================================\n";
    cout << "                     TEST SUMMARY\n";
    cout << "============================================================\n";

    cout << "Passed: "
         << passed
         << '\n';

    cout << "Failed: "
         << failed
         << '\n';

    cout << "Total:  "
         << passed + failed
         << '\n';

    cout << "============================================================\n";

    return failed == 0 ? 0 : 1;
}