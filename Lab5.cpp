#include <iostream>

using namespace std;

constexpr int SIZE = 4;

double determinant(double mat[SIZE][SIZE]) {
    return mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) -
                         mat[1][2] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) +
                         mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1])) -
           mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) -
                         mat[1][2] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) +
                         mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0])) +
           mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) -
                         mat[1][1] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) +
                         mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) -
           mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) -
                         mat[1][1] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]) +
                         mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
}

void minor(double mat[SIZE][SIZE], double temp[SIZE-1][SIZE-1], int row, int col) {
    int r = 0, c = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i != row && j != col) {
                temp[r][c++] = mat[i][j];
                if (c == SIZE - 1) { c = 0; ++r; }
            }
        }
    }
}

double determinant3x3(double mat[SIZE-1][SIZE-1]) {
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

void inverse(double mat[SIZE][SIZE], double inv[SIZE][SIZE]) {
    const double det = determinant(mat);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            double temp[SIZE-1][SIZE-1];
            minor(mat, temp, i, j);
            inv[j][i] = (determinant3x3(temp) * ((i + j) % 2 == 0 ? 1 : -1)) / det;
        }
    }
}

int main() {
    double mat[SIZE][SIZE] = {
        {4, 3, 2, 1},
        {3, 2, 1, 4},
        {2, 1, 4, 3},
        {1, 4, 3, 2}
    };

    double inv[SIZE][SIZE];
    inverse(mat, inv);

    for (auto & i : inv) {
        for (const double j : i) {
            cout << j << " ";
        }
        cout << endl;
    }

}
