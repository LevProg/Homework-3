#include <iostream>
#include <fstream>

using namespace std;

struct MatrixElement {
    int col;
    int value;
    MatrixElement* next;
};

void insertSorted(MatrixElement*& head, int col, int value) {
    MatrixElement* newNode = new MatrixElement{ col, value, nullptr };
    if (!head || head->col > col) {
        newNode->next = head;
        head = newNode;
    }
    else {
        MatrixElement* temp = head;
        while (temp->next && temp->next->col < col) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void readMatrix(const string& filename, MatrixElement* matrix[], int n) {
    ifstream file(filename);
    int value;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            file >> value;
            if (value != 0) insertSorted(matrix[row], col, value);
        }
    }
    file.close();
}

void combineSparseMatrices(
    MatrixElement* result[],
    const MatrixElement* const matrix1[],
    const MatrixElement* const matrix2[],
    const MatrixElement* const matrix3[],
    const MatrixElement* const matrix4[],
    int n) {
    for (int row = 0; row < n; row++) {
        const MatrixElement* current = matrix1[row];
        while (current) {
            insertSorted(result[row], current->col, current->value);
            current = current->next;
        }
        current = matrix2[row];
        while (current) {
            insertSorted(result[row], current->col + n, current->value);
            current = current->next;
        }
    }
    for (int row = n; row < 2 * n; row++) {
        const MatrixElement* current = matrix3[row - n];
        while (current) {
            insertSorted(result[row], current->col, current->value);
            current = current->next;
        }

        current = matrix4[row - n];
        while (current) {
            insertSorted(result[row], current->col + n, current->value);
            current = current->next;
        }
    }
}

void printMatrix(const MatrixElement* const matrix[], int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        const MatrixElement* current = matrix[row];
        for (int j = 0; j < cols; j++) {
            if (current && current->col == j) {
                cout << current->value << " ";
                current = current->next;
            }
            else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

int main() {
    const int n = 2;

    MatrixElement* matrix1[n] = { nullptr }, * matrix2[n] = { nullptr }, * matrix3[n] = { nullptr }, * matrix4[n] = { nullptr };
    MatrixElement* result[2 * n] = { nullptr };
    readMatrix("matrix1.txt", matrix1, n);
    readMatrix("matrix2.txt", matrix2, n);
    readMatrix("matrix3.txt", matrix3, n);
    readMatrix("matrix4.txt", matrix4, n);

    combineSparseMatrices(result, matrix1, matrix2, matrix3, matrix4, n);

    printMatrix(result, 2 * n, 2 * n);

    return 0;
}
