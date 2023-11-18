#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> board;
vector<int> queens;
int n;

void printSol() {
    ofstream file("output.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] < 0) {
                file << i << ' ' << j << endl;
            }
        }
    }
}
void markFields(int row, int col, int val) {
    int k = 0;
    if (val == 0) k = col+1;
    else k = 0;
    for (int j = 0; j < n; j++) {
        if (board[col][j] == k) board[col][j] = val;
        if (board[j][row] == k) board[j][row] = val;
        if (col + j < n && row + j < n && board[col + j][row + j] == k) board[col + j][row + j] = val;
        if (col - j >= 0 && row - j >= 0 && board[col - j][row - j] == k) board[col - j][row - j] = val;
        if (col + j < n && row - j >= 0 && board[col + j][row - j] == k) board[col + j][row - j] = val;
        if (col - j >= 0 && row + j < n && board[col - j][row + j] == k) board[col - j][row + j] = val;
    }
    board[col][row] = -1 * val;
}
int chooseM() {
    int max = 0;
    int col = 0;
    for (int j = 0; j < n; j++) {
        int cur = 0;
        for (int i = 0; i < n; i++) {
            if (board[i][j] != 0) cur++;
        }
        if (cur > max && cur != n) {
            max = cur;
            col = j;
        }
    }
    return col;
}
void findFields(int m) {
    if (m >= n) {
        printSol();
        exit(0);
    }
    else {
        for (int col = 0; col < n; col++) {
            int row = chooseM();
            if (board[col][row] == 0) {
                queens[m] = col + 1;
                markFields(row, col, queens[m]);
                findFields(m + 1);
                markFields(row, col, 0);
            }
        }
    }
}
int main() {
    ifstream file("input.txt");
    file >> n;
    board=vector<vector<int>>(n, vector<int>(n, 0));
    queens=vector<int>(n, 0);
    file.close();
    findFields(0);
    return 0;
}