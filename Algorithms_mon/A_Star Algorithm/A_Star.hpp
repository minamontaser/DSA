#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>
#include <limits>
#include <utility>
#include <stdexcept>
#include <cassert>

using namespace std;

using ll = long long;
using ld = long double;
using size_t = std::size_t;

constexpr ld INF = numeric_limits<ld>::max() / 2.0;
constexpr ld DIAGONAL_COST = 1.4142135623730950488L;

int di[8] = {0, 1, 0, -1, 1, 1, -1 , -1};
int dj[8] = {1, 0, -1, 0, 1, -1, -1, 1};

struct cell{
    ll x, y;
    ld g, h, f;
    ll parent_x, parent_y;
    bool valid;
    
    cell(): x(0), y(0), g(INF), h(0), f(INF), parent_x(-1), parent_y(-1), valid(true) {}
    cell(ll x, ll y) : x(x), y(y), g(INF), h(0), f(INF), parent_x(-1), parent_y(-1), valid(true) {}

    bool operator>(const cell& other) const{
        return f > other.f || (f == other.f && h > other.h);
    }
};

struct AStarResult{
    vector<cell> path;
    bool success;
};

ld manhattanH(ll x1, ll y1, ll x2, ll y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

ld diagonalH(ll x1, ll y1, ll x2, ll y2){
    ld dx = abs(x1 - x2);
    ld dy = abs(y1 - y2);

    return max(dx, dy) + (DIAGONAL_COST - 1.0) * min(dx, dy);
}

ld euclideanH(ll x1, ll y1, ll x2, ll y2){
    ld dx = abs(x1 - x2), dy = abs(y1 - y2);
    return sqrt(dx * dx + dy * dy);
}

pair<ll, ll> neighbors(ll x, ll y, int i){
    ll nX = x + di[i], nY = y + dj[i];
    return {nX, nY};
}

vector<cell> path_tracing(const vector<vector<cell>>& grid_cells, cell start, cell goal){
    vector<cell> path;
    ll curr_x = goal.x, curr_y = goal.y;

    while(curr_x != start.x || curr_y != start.y){
        assert(curr_x >= 0 && curr_y >= 0);

        path.push_back(grid_cells[curr_x][curr_y]);
        ll temp_x = grid_cells[curr_x][curr_y].parent_x;
        ll temp_y = grid_cells[curr_x][curr_y].parent_y;
        curr_x = temp_x, curr_y = temp_y;
    }
    
    path.push_back(grid_cells[start.x][start.y]);

    reverse(path.begin(), path.end());

    return path;
}

AStarResult AStar(const vector<vector<ll>>& grid, cell start, cell goal){
    size_t n = grid.size();
    if(n == 0) return AStarResult{{}, false};
    
    size_t m = grid[0].size();
    if(m == 0) return AStarResult{{}, false};

    for(size_t i = 1; i < n; i++){
        if(grid[i].size() != m)
            throw invalid_argument("AStar: grid must be rectangular");
    }

    vector<vector<cell>> grid_cells(n, vector<cell>(m));
    vector<vector<bool>> closed(n, vector<bool>(m, false));

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < m; j++){
            grid_cells[i][j] = cell(i, j);

            if(grid[i][j]){
                grid_cells[i][j].valid = false;
            }
        }
    }

    auto inside = [&](ll x, ll y){
        return x >= 0 &&
            x < static_cast<ll>(n) &&
            y >= 0 &&
            y < static_cast<ll>(m) &&
            grid_cells[x][y].valid;
    };

    if(!inside(start.x,start.y) || !inside(goal.x,goal.y))
        return AStarResult{{}, false};

    priority_queue<cell, vector<cell>, greater<cell>> pq;

    grid_cells[start.x][start.y].g = 0;
    grid_cells[start.x][start.y].h = diagonalH(start.x, start.y, goal.x, goal.y);
    grid_cells[start.x][start.y].f = grid_cells[start.x][start.y].g + grid_cells[start.x][start.y].h;

    pq.push(grid_cells[start.x][start.y]);

    while(!pq.empty()){
        cell curr_cell = pq.top();
        pq.pop();

        if(curr_cell.g > grid_cells[curr_cell.x][curr_cell.y].g) continue;
        if(curr_cell.x == goal.x && curr_cell.y == goal.y){
            return AStarResult{path_tracing(grid_cells, start, goal), true};
        }

        for(int i = 0; i < 8; i++){
            auto [nx, ny] = neighbors(curr_cell.x, curr_cell.y, i);
            if(inside(nx, ny)){

                if(abs(di[i]) == 1 && abs(dj[i]) == 1){
                    if(!inside(curr_cell.x, ny) ||
                    !inside(nx, curr_cell.y))
                        continue;
                }

                ld movement_cost = (nx != curr_cell.x && ny != curr_cell.y) ? DIAGONAL_COST : 1;
                ld tentative_g = curr_cell.g + movement_cost;

                cell& neighbor = grid_cells[nx][ny];
                if(tentative_g < neighbor.g){
                    neighbor.parent_x = curr_cell.x;
                    neighbor.parent_y = curr_cell.y;
                    neighbor.g = tentative_g;
                    neighbor.h = diagonalH(nx, ny, goal.x, goal.y);
                    neighbor.f = neighbor.g + neighbor.h;

                    pq.push(neighbor);
                }
            }
        }
    }

    return AStarResult{{}, false};
}