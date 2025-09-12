#include "matrix_function.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "main.h"

static void ChangeLinesInSqrMatrix(int line_1, int line_2, struct MatrixCharacteristic* matrix);
static int IsZero(float parameter);

static void ChangeLinesInSqrMatrix(int line_1, int line_2, struct MatrixCharacteristic* matrix)
{
    float exchange_value = 0.0;
    float* matrix_pointer = matrix->matrix_pointer;

    for (int index = 0; index < matrix->size_x; index++)
    {
        exchange_value = matrix_pointer[SquareFormula(line_1, index, matrix)];
        matrix_pointer[SquareFormula(line_1, index, matrix)] = matrix_pointer[SquareFormula(line_2, index, matrix)];
        matrix_pointer[SquareFormula(line_2, index, matrix)] = -exchange_value; //minus from analytic geometry)
    }

}

static int IsZero(float parameter)
{
    return (fabs(parameter) < EPSILON) ? 1 : 0;
}

int RectangleFormula(int coordinate_y, int coordinate_x, struct MatrixCharacteristic* matrix)
{
    return (coordinate_y * matrix->size_x + coordinate_x);
}

int TriangularFormula(int coordinate_y, int coordinate_x, struct MatrixCharacteristic* matrix)
{
    return ((coordinate_y * (coordinate_y + 1)) / 2+ coordinate_x);
}

int SquareFormula(int coordinate_y, int coordinate_x, struct MatrixCharacteristic* matrix)
{
    return (coordinate_y * (matrix->size_x) + coordinate_x);
}

inline void CreateMatrix(MatrixCharacteristic* matrix, int (*Formula) (int, int, struct MatrixCharacteristic*))
{
    free(matrix->matrix_pointer);
    matrix->matrix_pointer = (float*) calloc(size_t(Formula(matrix->size_y, 0, matrix)), sizeof(int));
}

void CreateMatrix(int size_x, int size_y, enum MatrixType matrix_type,struct MatrixCharacteristic* matrix)
{
    assert(matrix != NULL);
    if (matrix_type == RECTANGLE_MATRIX)
    {
        matrix->size_x = size_x;
        matrix->size_y = size_y;
        matrix->matrix_type = RECTANGLE_MATRIX;
        CreateMatrix(matrix, RectangleFormula);
    }
    else if (matrix_type == TRIANGULAR_MATRIX)
    {
        matrix->size_x = 0;
        matrix->size_y = size_y;
        matrix->matrix_type = TRIANGULAR_MATRIX;
        CreateMatrix(matrix, TriangularFormula);
    }
    else if (matrix_type == SQUARE_MATRIX)
    {
        matrix->size_x = size_y;
        matrix->size_y = size_y;
        matrix->matrix_type = SQUARE_MATRIX;
        CreateMatrix(matrix, SquareFormula);
    }

}

void PrintMatrix(struct MatrixCharacteristic* matrix, int (*Formula) (int, int, struct MatrixCharacteristic*))
{
    int size_x = matrix->size_x, size_y = matrix->size_y;

    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < Formula(y + 1, 0, matrix) - Formula(y, 0, matrix); x++)
        {
            //printf("%d-%d ", x, y);
            printf("%5.2f", (matrix->matrix_pointer)[Formula(y, x, matrix)]);
        }

        printf("\n");
    }
}

int EnterInMatrix(struct MatrixCharacteristic* matrix, int (*Formula) (int, int, struct MatrixCharacteristic*), int coordinate_x, int coordinate_y, float value)
{
    int absolute_coordinate = Formula(coordinate_y, coordinate_x, matrix);

    if (absolute_coordinate >= Formula(matrix->size_y, 0, matrix))
    {
        return 1;
    }
    //printf("%d %d %d %d\n", coordinate_x, coordinate_y, absolute_coordinate, value);
    (matrix->matrix_pointer)[absolute_coordinate] = value;

    return 0;
}

float Determinant(struct MatrixCharacteristic* matrix)
{
    bool flag = true;
    float determinant = 1;

    for (int start_xy = 0; start_xy < (matrix->size_x - 1); start_xy++)
    {
        flag = false;

        if (IsZero((matrix->matrix_pointer)[SquareFormula(start_xy, start_xy, matrix)]))
        {
            flag = true;
            for (int line = start_xy + 1; line < matrix->size_y; line++)
            {
                if (!IsZero((matrix->matrix_pointer)[SquareFormula(line, start_xy, matrix)]))
                {
                    flag = false;
                    ChangeLinesInSqrMatrix(line, start_xy, matrix);
                    break;
                }

            }
        }

        if (flag == true)
        {
            return 0.0;
        }

        float proportional_coefficient = 1;

        for (int line = start_xy + 1; line < matrix->size_y; line++)
        {
            proportional_coefficient = (matrix->matrix_pointer)[SquareFormula(line, start_xy, matrix)] /  (matrix->matrix_pointer)[SquareFormula(start_xy, start_xy, matrix)];
            for (int column = start_xy; column < matrix->size_x; column++)
            {
                (matrix->matrix_pointer)[SquareFormula(line, column, matrix)] -= proportional_coefficient * (matrix->matrix_pointer)[SquareFormula(start_xy, column, matrix)];
            }
        }

        determinant *= (matrix->matrix_pointer)[SquareFormula(start_xy, start_xy, matrix)];
        //PrintMatrix(matrix, SquareFormula);
    }
    determinant *= (matrix->matrix_pointer)[SquareFormula(matrix->size_x - 1, matrix->size_y - 1, matrix)];

    return determinant;

}


