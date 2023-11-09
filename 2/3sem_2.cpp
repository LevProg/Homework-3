#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct MatrixElement {
    int col;
    int value;
};

void readMatrix(const string& filename, list<MatrixElement> matrix[], int n) {
    ifstream file(filename);
    int value;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            file >> value;
            if (value > 0) matrix[row].push_back({ col, value });
        }
    }
    file.close();
}

void combineSparseMatrices(
    list<MatrixElement> *result,
    const list<MatrixElement> *matrix1,
    const list<MatrixElement> *matrix2,
    const list<MatrixElement> *matrix3,
    const list<MatrixElement> *matrix4,
    int n) {
    for (int row = 0; row < n; row++) {
        for (const auto& elem : matrix1[row]) {
            result[row].push_back({ elem.col, elem.value });
        }
        for (const auto& elem : matrix2[row]) {
            result[row].push_back({ elem.col + n, elem.value });
        }
    }
    for (int row = n; row < 2*n; row++) {
        for (const auto& elem : matrix3[row-n]) {
            result[row].push_back({ elem.col, elem.value });
        }
        for (const auto& elem : matrix4[row - n]) {
            result[row].push_back({ elem.col + n, elem.value });
        }
    }
    
}

int main() {
    const int n = 2;

    list<MatrixElement> matrix1[n], matrix2[n], matrix3[n], matrix4[n];
    list<MatrixElement> result[n * 2];
    readMatrix("matrix1.txt", matrix1, n);
    readMatrix("matrix2.txt", matrix2, n);
    readMatrix("matrix3.txt", matrix3, n);
    readMatrix("matrix4.txt", matrix4, n);

    combineSparseMatrices(result, matrix1, matrix2, matrix3, matrix4, n);

    for (int row = 0; row < 2 * n; row++) {
        for (int j = 0; j < 2 * n; j++) {
            bool found = false;
            for (const auto& elem : result[row]) {
                if (elem.col == j) {
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
