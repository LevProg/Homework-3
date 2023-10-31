#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct MatrixElement {
    int row;
    int col;
    int value;
};

void readMatrix(const string& filename, list<MatrixElement>& matrix, int n) {
    ifstream file(filename);
    int value;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            file >> value;
            if (value>0) matrix.push_back({ row, col, value });
        }
    }
    file.close();
}

list<MatrixElement> combineSparseMatrices(
    const list<MatrixElement>& matrix1,
    const list<MatrixElement>& matrix2,
    const list<MatrixElement>& matrix3,
    const list<MatrixElement>& matrix4,
    int n) {
    list<MatrixElement> result;

    for (const auto& elem : matrix1) {
        result.push_back({ elem.row, elem.col, elem.value });
    }
    for (const auto& elem : matrix2) {
        result.push_back({ elem.row, elem.col + n, elem.value });
    }
    for (const auto& elem : matrix3) {
        result.push_back({ elem.row + n, elem.col, elem.value });
    }
    for (const auto& elem : matrix4) {
        result.push_back({ elem.row + n, elem.col + n, elem.value });
    }
    return result;
}

int main() {
    int n = 2;

    list<MatrixElement> matrix1, matrix2, matrix3, matrix4;

    readMatrix("matrix1.txt", matrix1, n);
    readMatrix("matrix2.txt", matrix2, n);
    readMatrix("matrix3.txt", matrix3, n);
    readMatrix("matrix4.txt", matrix4, n);

    list<MatrixElement> result = combineSparseMatrices(matrix1, matrix2, matrix3, matrix4, n);

    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            bool found = false;
            for (const auto& elem : result) {
                if (elem.row == i && elem.col == j) {
                    cout << elem.value << " ";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "0 ";
            }
        }
        cout << endl;
    }
    return 0;
}
