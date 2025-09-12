#ifndef MATRIX_FUNCTION_H
#define MATRIX_FUNCTION_H

#include "main.h"

const double EPSILON = 0.001;

void CreateMatrix(int size_x, int size_y, enum MatrixType matrix_type, MatrixCharacteristic* matrix);
inline void CreateMatrix(MatrixCharacteristic* matrix);
int RectangleFormula(int line, int column, MatrixCharacteristic* matrix);
void PrintMatrix(MatrixCharacteristic* matrix, int (*Formula) (int, int, struct MatrixCharacteristic*));
int EnterInMatrix(struct MatrixCharacteristic* matrix, int (*Formula) (int, int, struct MatrixCharacteristic*), int coordinate_x, int coordinate_y, float value);
int TriangularFormula(int coordinate_y, int coordinate_x, struct MatrixCharacteristic* matrix);
int SquareFormula(int coordinate_y, int coordinate_x, struct MatrixCharacteristic* matrix);
float Determinant(struct MatrixCharacteristic* matrix);


#endif
