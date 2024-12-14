//
// Created by Zebin Guo on 12/14/24.
//
// 给定一幅N * N的图像，每个像素大小为4字节 (int)，将图像旋转90度，不占用额外空间

#include "MatrixRotation.hpp"

void MatrixRotation::MatrixRotationMatrix(Vector<Vector<int> > &matrix) {
    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols / 2; j++) {
            // do four operations.
            const int element = matrix[i][j];
            matrix[i][j] = matrix[cols - 1 - j][i];
            matrix[cols - 1 - j][i] = matrix[rows - 1 - i][cols - 1 - j];
            matrix[rows - 1 - i][cols - 1 - j] = matrix[j][cols - 1 - i];
            matrix[j][cols - 1 - i] = element;
        }
    }
}

