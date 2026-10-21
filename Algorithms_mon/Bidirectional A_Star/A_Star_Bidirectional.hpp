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

ld manhattanH(ll x1, ll y1, ll x2, ll y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

ld euclideanH(ll x1, ll y1, ll x2, ll y2){
    ld dx = abs(x1 - x2), dy = abs(y1 - y2);
    return sqrt(dx * dx + dy * dy);
}

pair<ll, ll> neighbors(ll x, ll y, int i){
    ll nX = x + di[i], nY = y + dj[i];
    return {nX, nY};
}

struct cell{
    ll x, y;
    ll parent_x, parent_y;
    ld g, h, f;
    
    cell(): x(0), y(0), g(INF), h(0.0L), f(INF), parent_x(-1), parent_y(-1) {}
    cell(ll x, ll y) : x(x), y(y), g(INF), h(0.0L), f(INF), parent_x(-1), parent_y(-1) {}

    bool operator>(const cell& other) const{
        return f > other.f || (f == other.f && h > other.h);
    }
};

struct AStarResult{
    vector<cell> path = {};
    bool success = false;
    ld bestCost = INF;
    size_t pathLength = 0;

    vector<vector<cell>> forward_backward_path = {};
    vector<vector<cell>> final_path_grid = {};
};

enum class Heuristic{
    Manhattan,
    Diagonal,
    Euclidean,
};

struct AStarConfig{
    Heuristic heuristic = Heuristic::Diagonal;

    bool allowDiagonal = true;
    bool preventCornerCutting = false;

    ld straightCost = 1.0L;
    ld diagonalCost = DIAGONAL_COST;
};

struct searchState{
    vector<vector<cell>> grid;
    vector<vector<bool>> closed;
    priority_queue<cell, vector<cell>, greater<cell>> openSet;
};

ld calculateHeuristic(const cell& current, const cell& goal, const AStarConfig& config){
    const ld dx = abs(current.x - goal.x), dy = abs(current.y - goal.y);
    switch(config.heuristic){
        case Heuristic::Manhattan:
            return manhattanH(current.x, current.y, goal.x, goal.y) * config.straightCost;
        case Heuristic::Diagonal: {
            if (!config.allowDiagonal) {
                return manhattanH(current.x, current.y, goal.x, goal.y) * config.straightCost;
            }

            const ld diagonalStepCost = min(config.diagonalCost, 2.0L * config.straightCost);
            const ll diagonalSteps = min(dx, dy);
            const ll straightSteps = max(dx, dy) - diagonalSteps;

            return diagonalSteps * diagonalStepCost + straightSteps * config.straightCost;
        }
        case Heuristic::Euclidean:
            return euclideanH(current.x, current.y, goal.x, goal.y) * config.straightCost;
    }
    throw invalid_argument("calculateHeuristic: invalid heuristic");
}

ld calculatePathCost(const vector<cell>& path, const AStarConfig& config){
    if(path.size() < 2)
        return 0.0L;

    ld totalCost = 0.0L;

    for(size_t i = 1; i < path.size(); i++){
        ll dx = abs(path[i].x - path[i - 1].x);
        ll dy = abs(path[i].y - path[i - 1].y);

        if(dx == 1 && dy == 1){
            totalCost += config.diagonalCost;
        }
        else if((dx == 1 && dy == 0) || (dx == 0 && dy == 1)){
            totalCost += config.straightCost;
        }
        else{
            throw invalid_argument("calculatePathCost: invalid path");
        }
    }

    return totalCost;
}

vector<cell> path_tracing(
    const vector<vector<cell>>& forward, 
    const vector<vector<cell>>& backward, 
    const cell& start, const cell& goal, const cell& meeting){

    vector<cell> forward_path, backward_path, final_path;
    ll curr_x = meeting.x, curr_y = meeting.y;

    while(curr_x != start.x || curr_y != start.y){
        assert(curr_x >= 0 && curr_y >= 0);
        forward_path.push_back(forward[curr_x][curr_y]);
        ll parentX = forward[curr_x][curr_y].parent_x;
        ll parentY = forward[curr_x][curr_y].parent_y;
        curr_x = parentX, curr_y = parentY;
    }

    forward_path.push_back(forward[start.x][start.y]);
    reverse(forward_path.begin(), forward_path.end());

    curr_x = meeting.x, curr_y = meeting.y;

    while(curr_x != goal.x || curr_y != goal.y){
        assert(curr_x >= 0 && curr_y >= 0);
        backward_path.push_back(backward[curr_x][curr_y]);
        ll parentX = backward[curr_x][curr_y].parent_x;
        ll parentY = backward[curr_x][curr_y].parent_y;
        curr_x = parentX, curr_y = parentY;
    }

    backward_path.push_back(backward[goal.x][goal.y]);

    final_path = forward_path;
    final_path.insert(final_path.end(), next(backward_path.begin()), backward_path.end());

    return final_path;
}

AStarResult AStar(const vector<vector<ll>> &grid, const cell start, const cell goal, const AStarConfig& config){
    if (config.straightCost <= 0.0L ||config.diagonalCost <= 0.0L){
        throw invalid_argument("AStar: movement costs must be greater than zero");
    }

    if (config.allowDiagonal &&config.heuristic == Heuristic::Manhattan){
        throw invalid_argument("AStar: Manhattan heuristic is invalid when diagonal movement is enabled");
    }

    size_t n = grid.size();
    if(n == 0) return AStarResult{};
    
    size_t m = grid[0].size();
    if(m == 0) return AStarResult{};

    for(size_t i = 1; i < n; i++){
        if(grid[i].size() != m)
            throw invalid_argument("AStar: grid must be rectangular");
    }

    searchState forward, backward;
    forward.grid = vector<vector<cell>>(n, vector<cell>(m));
    backward.grid = vector<vector<cell>>(n, vector<cell>(m));
    
    forward.closed.assign(n, vector<bool>(m, false));
    backward.closed.assign(n, vector<bool>(m, false));

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < m; j++){
            forward.grid[i][j] = cell(i, j);
            backward.grid[i][j] = cell(i, j);
        }
    }

    auto inBounds = [&](ll x, ll y){
        return x >= 0 &&
            x < static_cast<ll>(n) &&
            y >= 0 &&
            y < static_cast<ll>(m);
    };

    auto isValid = [&](ll x, ll y){
        return inBounds(x, y) && grid[x][y] == 0;
    };

    if(!isValid(start.x, start.y) || !isValid(goal.x, goal.y))
        return AStarResult{};

    if(start.x == goal.x && start.y == goal.y){
        vector<cell> path{start};
        return AStarResult{path, true, 0.0L, path.size()};
    }

    forward.grid[start.x][start.y].g = 0.0L;
    forward.grid[start.x][start.y].h = calculateHeuristic(forward.grid[start.x][start.y], goal, config);
    forward.grid[start.x][start.y].f = forward.grid[start.x][start.y].g + forward.grid[start.x][start.y].h;

    forward.openSet.push(forward.grid[start.x][start.y]);

    backward.grid[goal.x][goal.y].g = 0.0L;
    backward.grid[goal.x][goal.y].h = calculateHeuristic(backward.grid[goal.x][goal.y], start, config);
    backward.grid[goal.x][goal.y].f = backward.grid[goal.x][goal.y].g + backward.grid[goal.x][goal.y].h;

    backward.openSet.push(backward.grid[goal.x][goal.y]);

    ld bestCost = INF;
    cell meeting;
    bool hasMeeting = false;
    const int directions = (config.allowDiagonal) ? 8 : 4;

    auto updateMeeting = [&](ll nx, ll ny){
        if(forward.grid[nx][ny].g ==  INF) return;
        if(backward.grid[nx][ny].g == INF) return;
        ld candidate = forward.grid[nx][ny].g + backward.grid[nx][ny].g;
        if(candidate < bestCost){
            bestCost = candidate;
            meeting = forward.grid[nx][ny];
            hasMeeting = true;
        }
    };

    while(!forward.openSet.empty() && !backward.openSet.empty()){
        while(!forward.openSet.empty()){
            const cell& top = forward.openSet.top();
            if(top.g == forward.grid[top.x][top.y].g) break;
            forward.openSet.pop();
        }

        while(!backward.openSet.empty()){
            const cell& top = backward.openSet.top();
            if(top.g == backward.grid[top.x][top.y].g) break;
            backward.openSet.pop();
        }

        if(forward.openSet.empty() || backward.openSet.empty()) break;

        if(hasMeeting){
            ld forwardLowerBound = forward.openSet.top().f;
            ld backwardLowerBound = backward.openSet.top().f;
            if(min(forwardLowerBound, backwardLowerBound) >= bestCost) break;
        }

        const cell& top_forward = forward.openSet.top(), &top_backward = backward.openSet.top();
        bool expand_forward_flag = top_forward.f <= top_backward.f;
    
        if(expand_forward_flag){

            cell current = forward.openSet.top();
            forward.openSet.pop();

            if(current.g != forward.grid[current.x][current.y].g) continue;
            if(forward.closed[current.x][current.y]) continue;

            forward.closed[current.x][current.y] = true;

            updateMeeting(current.x, current.y);

            for(int i = 0; i < directions; i++){
                auto [nx_forward, ny_forward] = neighbors(current.x, current.y, i);
                if(!isValid(nx_forward, ny_forward)) continue;

                if (abs(di[i]) == 1 && abs(dj[i]) == 1){
                    if (config.preventCornerCutting){
                        if (!isValid(current.x, ny_forward) || !isValid(nx_forward, current.y)) continue;
                    }
                }

                ld movement_cost_forward = (nx_forward != current.x && ny_forward != current.y) ? config.diagonalCost : config.straightCost;
                ld tentative_g_forward = current.g + movement_cost_forward;
                cell &neighbor_forward = forward.grid[nx_forward][ny_forward];

                if(!forward.closed[nx_forward][ny_forward] && tentative_g_forward < neighbor_forward.g){

                    neighbor_forward.parent_x = current.x;
                    neighbor_forward.parent_y = current.y;
                    neighbor_forward.g = tentative_g_forward;
                    neighbor_forward.h = calculateHeuristic(neighbor_forward, goal, config);
                    neighbor_forward.f = neighbor_forward.g + neighbor_forward.h;

                    forward.openSet.push(neighbor_forward);
                }

               updateMeeting(nx_forward, ny_forward);
            }
        }
        else{

            cell current = backward.openSet.top();
            backward.openSet.pop();
            if(current.g != backward.grid[current.x][current.y].g) continue;
            if(backward.closed[current.x][current.y]) continue;

            backward.closed[current.x][current.y] = true;

            updateMeeting(current.x, current.y);

            for(int i = 0; i < directions; i++){
                auto [nx_backward, ny_backward] = neighbors(current.x, current.y, i);
                if(!isValid(nx_backward, ny_backward)) continue;

                if (abs(di[i]) == 1 && abs(dj[i]) == 1){
                    if (config.preventCornerCutting){
                        if (!isValid(current.x, ny_backward) || !isValid(nx_backward, current.y)) continue;
                    }
                }

                ld movement_cost_backward = (nx_backward != current.x && ny_backward != current.y) ? config.diagonalCost : config.straightCost;
                ld tentative_g_backward = current.g + movement_cost_backward;
                cell &neighbor_backward = backward.grid[nx_backward][ny_backward];

                if(!backward.closed[nx_backward][ny_backward] && tentative_g_backward < neighbor_backward.g){

                    neighbor_backward.parent_x = current.x;
                    neighbor_backward.parent_y = current.y;
                    neighbor_backward.g = tentative_g_backward;
                    neighbor_backward.h = calculateHeuristic(neighbor_backward, start, config);
                    neighbor_backward.f = neighbor_backward.g + neighbor_backward.h;

                    backward.openSet.push(neighbor_backward);
                }

               updateMeeting(nx_backward, ny_backward);
            }
        }
    }

    if(!hasMeeting) return AStarResult{};
    vector<cell> path = path_tracing(forward.grid, backward.grid, start, goal, meeting);
    ld pathCost = calculatePathCost(path, config);

    return AStarResult{path, true, pathCost, path.size()};
}