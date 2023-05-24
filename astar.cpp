#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y,g,h,f; // Coordinates of the node   // Total cost (g + h)
    Node(int x, int y, int g, int h) : x(x), y(y), g(g), h(h), f(g + h) {}

    // Overloading the '<' operator for priority queue
    bool operator<(const Node& other) const {
        return f > other.f; // Smaller f value has higher priority
    }
};

// Helper function to calculate the Manhattan distance heuristic
int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int numRows, int numCols) {
    return x >= 0 && x < numRows && y >= 0 && y < numCols;
}

vector<pair<int, int>> findPath(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    vector<vector<pair<int, int>>> parent(numRows, vector<pair<int, int>>(numCols));

    // Define the possible movement directions (up, down, left, right, diagonal)
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

    // Priority queue for open nodes
    priority_queue<Node> open;

    // Add the start node to the open set
    open.push(Node(start.first, start.second, 0, manhattanDistance(start.first, start.second, goal.first, goal.second)));

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        int x = current.x;
        int y = current.y;

        // Check if the current node is the goal node
        if (x == goal.first && y == goal.second) {
            // Reconstruct the path from the goal to the start node
            vector<pair<int, int>> path;
            while (x != start.first || y != start.second) {
                path.push_back(make_pair(x, y));
                pair<int, int> p = parent[x][y];
                x = p.first;
                y = p.second;
            }
            path.push_back(make_pair(start.first, start.second));
            reverse(path.begin(), path.end());
            return path;
        }

        // Mark the current node as visited
        visited[x][y] = true;

        // Explore the neighbors of the current node
        for (int i = 0; i < 8; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // Check if the neighbor is valid and not visited
            if (isValid(newX, newY, numRows, numCols) && !visited[newX][newY] && grid[newX][newY] != 1) {
                int newG = current.g + 1;
                int newH = manhattanDistance(newX, newY, goal.first, goal.second);
                int newF = newG + newH;

                // Check if the neighbor is not in the open set or has a lower f value
                if (!visited[newX][newY] || newF < current.f) {
                    open.push(Node(newX, newY, newG, newH));
                    parent[newX][newY] = make_pair(x, y);
                }
            }
        }
    }

    // No path found
    return {};
}

int main() {
    int numRows, numCols;
    cout << "Enter the number of rows and columns: ";
    cin >> numRows >> numCols;

    vector<vector<int>> grid(numRows, vector<int>(numCols, 0));

    cout << "Enter the grid (0 for empty, 1 for obstacle):\n";
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cin >> grid[i][j];
        }
    }

    pair<int, int> start, goal;
    cout << "Enter the start position (row col): ";
    cin >> start.first >> start.second;
    cout << "Enter the goal position (row col): ";
    cin >> goal.first >> goal.second;

    vector<pair<int, int>> path = findPath(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found!\n";
        cout << "Path: ";
        for (auto p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found!\n";
    }

    return 0;
}
