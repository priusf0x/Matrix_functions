#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>

enum ProgramState
{
    PROGRAM_STATE_MENU,
    PROGRAM_STATE_EXIT,
    PROGRAM_STATE_ERROR,
};

enum MatrixType
{
    RECTANGLE_MATRIX,
    TRIANGULAR_MATRIX,
    SQUARE_MATRIX
};

struct MatrixCharacteristic
{
    enum MatrixType matrix_type = RECTANGLE_MATRIX;
    float * matrix_pointer = NULL;
    int size_x = 0;
    int size_y = 0;
};

extern MatrixCharacteristic MAIN_MATRIX;

void StartStateMachine();

#endif
