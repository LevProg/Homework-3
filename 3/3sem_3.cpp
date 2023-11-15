#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> board(8, vector<int>(8, 0));
vector<int> queens(8, 0);
int n = 0;

void printSol() {
    ofstream file("output.txt");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] < 0) {
                file << i << ' ' << j << endl;
            }
        }
    }
}
void markFields(int row, int col, int val) {
    int k = 0;
    if (val == 0) k = row;
    else k = 0;
    for (int j = 0; j < 8; j++) {
        if (board[col][j] == 0) board[col][j] = val;
        if (board[j][row] == 0) board[j][row] = val;
        if (col + j < 8 && row + j < 8 && board[col + j][row + j] == k ) board[col + j][row + j] = val;
        if (col - j >= 0 && row - j >= 0 && board[col - j][row - j] == k) board[col - j][row - j] = val;
        if (col + j < 8 && row - j >= 0 && board[col + j][row - j] == k) board[col + j][row - j] = val;
        if (col - j >= 0 && row + j < 8 && board[col - j][row + j] == k) board[col - j][row + j] = val;
    }
    board[col][row] = -1 * val;
}
int chooseM() {
    int max = 0;
    int col=0;
    for (int j = 0; j < 8; j++) {
        int cur = 0;
        for (int i = 0; i < 8; i++) {
            if (board[i][j] != 0) cur++;
        }
        if (cur > max && cur!=8) {
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
        for (int col = 0; col < 8; col++) {
            int row = chooseM();
            if (board[col][row] == 0) {
                queens[m] = m+1;
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
    file.close();
    findFields(0);
    return 0;
}