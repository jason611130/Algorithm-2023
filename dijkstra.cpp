#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

// 定義迷宮的大小
const int ROWS = 5;
const int COLS = 5;

// 定義迷宮格子的狀態
enum CellState {
    EMPTY,
    WALL,
    START,
    END
};

// 定義每個格子的資訊
struct Cell {
    int row, col;
    CellState state;
};

// 定義每個節點的資訊
struct Node {
    int row, col, distance;

    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Dijkstra算法
int dijkstra(const vector<vector<Cell>>& maze, const Cell& start, const Cell& end, vector<vector<int>>& prev) {
    // 定義方向向量，用於確定相鄰格子的位置
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    // 建立二維陣列用於儲存起點到每個點的最短距離
    vector<vector<int>> distance(ROWS, vector<int>(COLS, INT_MAX));

    // 建立優先佇列，用於選擇下一個要擴展的節點
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // 將起點加入優先佇列
    pq.push({start.row, start.col, 0});
    distance[start.row][start.col] = 0;

    while (!pq.empty()) {
        // 取出優先佇列中距離最短的節點
        Node current = pq.top();
        pq.pop();

        // 檢查是否為終點
        if (current.row == end.row && current.col == end.col) {
            return current.distance;
        }

        // 擴展相鄰的格子
        for (int i = 0; i < 4; ++i) {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];

            // 檢查是否超出邊界
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) {
                continue;
            }

            // 檢查格子是否為牆
            if (maze[nr][nc].state == WALL) {
                continue;
            }

            // 計算新的距離
            int newDistance = current.distance + 1;

            // 如果新的距離比之前的短，則更新距離並將節點加入優先佇列
            if (newDistance < distance[nr][nc]) {
                distance[nr][nc] = newDistance;
                pq.push({nr, nc, newDistance});
                // 保存前一個節點
                prev[nr][nc] = current.row * COLS + current.col;
            }
        }
    }

    // 如果無法到達終點，回傳-1表示失敗
    return -1;
}

// 輸出最短路徑
void printShortestPath(const vector<vector<int>>& prev, const Cell& start, const Cell& end) {
    stack<int> path;

    // 從終點回溯到起點
    int current = end.row * COLS + end.col;
    while (current != start.row * COLS + start.col) {
        path.push(current);
        current = prev[current / COLS][current % COLS];
    }
    path.push(start.row * COLS + start.col);

    // 輸出路徑
    cout << "最短路徑: ";
    while (!path.empty()) {
        int point = path.top();
        path.pop();
        cout << "(" << point / COLS << ", " << point % COLS << ") ";
    }
    cout << endl;
}

int main() {
    // 創建迷宮
    vector<vector<Cell>> maze(ROWS, vector<Cell>(COLS, {0, 0, EMPTY}));
    maze[0][0].state = START;
    maze[ROWS - 1][COLS - 1].state = END;

    // 設置牆
    maze[1][1].state = WALL;
    maze[1][2].state = WALL;
    maze[2][2].state = WALL;
    maze[3][2].state = WALL;

    // 使用Dijkstra算法找到最短路徑
    vector<vector<int>> prev(ROWS, vector<int>(COLS, -1));
    int shortestDistance = dijkstra(maze, maze[0][0], maze[ROWS - 1][COLS - 1], prev);

    // 輸出結果
    if (shortestDistance != -1) {
        cout << "最短路徑長度為: " << shortestDistance << endl;
        // 輸出最短路徑中所有的點
        printShortestPath(prev, maze[0][0], maze[ROWS - 1][COLS - 1]);
    } else {
        cout << "無法找到路徑" << endl;
    }

    return 0;
}