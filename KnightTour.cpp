#include <iostream>
#include <vector>

using namespace std;

bool isValidMove(int x, int y, int rows, int cols, vector<vector<bool>> &visited) {
    //To ensure the moves are still inclusive of the chessboard area
    return (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y]);
}

bool backtrack(int x, int y, int moveCount, int rows, int cols, vector<vector<bool>> &visited, vector<pair<int, int>> &path, vector<pair<int, int>> &moves) {
    //To keep track of the Visited Coordinates
    visited[x][y] = true;  
    path.push_back({x, y});  
    
    // "-1" from total (rows * cols) because the 24th move visits the last coordinate
    if (moveCount == rows * cols - 1) {
        return true;  
    }
    
    //Recursively goes through all possible movements
    for (auto move : moves) {
        int newX = x + move.first;
        int newY = y + move.second;
        if (isValidMove(newX, newY, rows, cols, visited)) {
            if (backtrack(newX, newY, moveCount + 1, rows, cols, visited, path, moves)) {
                return true; 
            }
        }
    }
    
    //If no movements introduce a different coordinate
    visited[x][y] = false;
    path.pop_back();
    return false; 
}

vector<pair<int, int>> knightTourAnticlockwise(int rows, int cols, int startX, int startY) {
    //The order of movements in an "anticlockwise" manner
    vector<pair<int, int>> moves = {
        {2, -1}, {1, -2}, 
        {-1, -2}, {-2, -1}, 
        {-2, 1}, {-1, 2}, 
        {1, 2}, {2, 1}
    };
    
    //Initiating visited coordinates and path
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int, int>> path;

    backtrack(startX, startY, 0, rows, cols, visited, path, moves);

    return path; 
}

int main() {
    int rows, cols, startX, startY;

    cin >> rows;
    cin >> cols;

    cin >> startX;
    cin >> startY;

    vector<pair<int, int>> result = knightTourAnticlockwise(rows, cols, startX, startY);

    for (auto coordinate : result) {
        cout << coordinate.first << ' ' << coordinate.second << endl;
    }

    return 0;
}
