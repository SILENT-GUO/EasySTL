//
// Created by Zebin Guo on 12/14/24.
//

#ifndef MATRIXROTATION_HPP
#define MATRIXROTATION_HPP

#include "Vector.hpp"
#include <iostream>

class MatrixRotation {
    public:
    static void MatrixRotationMatrix(Vector<Vector<int> > &matrix);
    static std::ostream printMatrix(Vector<Vector<int> > &matrix);
};

#endif //MATRIXROTATION_HPP
