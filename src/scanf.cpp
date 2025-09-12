#include "scanf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "matrix_function.h"

static const int BUFFER_SIZE = 20;

static char buffer[BUFFER_SIZE];

enum ProgramState ReadInput()
{
    int index = 0;
    int character = getchar();

    memset(buffer, 0, BUFFER_SIZE * sizeof(char));


    while (!isspace(character) && index < BUFFER_SIZE)
    {
        buffer[index] = (char) character;
        index++;
        character = getchar();
    }

    ungetc(character, stdin);

    if (strcmp(buffer, "exit") == 0)
    {
        ClearBuffer();
        return PROGRAM_STATE_EXIT;
    }
    else if (strcmp(buffer, "print") == 0)
    {
        if (MAIN_MATRIX.matrix_type == RECTANGLE_MATRIX)
        {
            PrintMatrix(&MAIN_MATRIX, RectangleFormula);
        }
        else if (MAIN_MATRIX.matrix_type == TRIANGULAR_MATRIX)
        {
            PrintMatrix(&MAIN_MATRIX, TriangularFormula);
        }
        else if (MAIN_MATRIX.matrix_type == SQUARE_MATRIX)
        {
            PrintMatrix(&MAIN_MATRIX, SquareFormula);
        }
        ClearBuffer();
        return PROGRAM_STATE_MENU;
    }
    else if (strcmp(buffer, "matrixrect") == 0)
    {
        int size_x = 0;
        int size_y = 0;

        if (ReadMatrixSize(&size_x, &size_y) == 0)
        {
            CreateMatrix(size_x, size_y,  RECTANGLE_MATRIX, &MAIN_MATRIX);
        }

        ClearBuffer();

        return PROGRAM_STATE_MENU;
    }
    else if (strcmp(buffer, "matrixsquare") == 0)
    {
        int size_y = 0;

        if (scanf("%d", &size_y) == 1)
        {
            CreateMatrix(0, size_y,  SQUARE_MATRIX, &MAIN_MATRIX);
        }
        else
        {
            printf("Unable to create matrix with this size.\n");
        }

        ClearBuffer();

        return PROGRAM_STATE_MENU;

    }
    else if (strcmp(buffer, "determinant") == 0)
    {
        if (MAIN_MATRIX.matrix_type == SQUARE_MATRIX)
        {
            printf("Determinant of your matrix is equals to %.2f.\n", Determinant(&MAIN_MATRIX));
        }
        else
        {
            printf("Your matrix is not a square matrix.\n");
        }
        ClearBuffer();

        return PROGRAM_STATE_MENU;

    }
    else if (strcmp(buffer, "matrixtriangular") == 0)
    {
        int size_y = 0;

        if (scanf("%d", &size_y) == 1)
        {
            CreateMatrix(0, size_y,  TRIANGULAR_MATRIX, &MAIN_MATRIX);
        }
        else
        {
            printf("Unable to create matrix with this size.\n");
        }

        ClearBuffer();

        return PROGRAM_STATE_MENU;
    }
    else if (strcmp(buffer, "enter") == 0)
    {
        int coordinate_x = 0;
        int coordinate_y = 0;
        float value = 0;

        if (ReadMatrixParameters(&coordinate_x, &coordinate_y, &value) == 0)
        {
            if (MAIN_MATRIX.matrix_type == RECTANGLE_MATRIX)
            {
                if (EnterInMatrix(&MAIN_MATRIX, RectangleFormula, coordinate_x, coordinate_y, value) == 1)
                {
                    printf("Incorrect coordinates.\n");
                }
            }
            else if (MAIN_MATRIX.matrix_type == TRIANGULAR_MATRIX)
            {
                if (EnterInMatrix(&MAIN_MATRIX, TriangularFormula, coordinate_x, coordinate_y, value) == 1)
                {
                    printf("Incorrect coordinates.\n");
                }
            }
            else if (MAIN_MATRIX.matrix_type == SQUARE_MATRIX)
            {
                if (EnterInMatrix(&MAIN_MATRIX, SquareFormula, coordinate_x, coordinate_y, value) == 1)
                {
                    printf("Incorrect coordinates.\n");
                }
            }
        }

        ClearBuffer();
        return PROGRAM_STATE_MENU;
    }
    else
    {
        ClearBuffer();
        printf("Incorrect Input\n");
        return PROGRAM_STATE_MENU;
    }
}

bool ClearBuffer()
{
    bool flag = false;
    int character = 0;
    while ((character = getchar()) != '\n' && character != EOF)
    {
        if (!isspace(character))
        {
            flag = true;
        }
    }
    return flag;
}

int ReadMatrixSize(int* size_x, int* size_y)
{
    if (scanf("%d %d", size_x, size_y) != 2 || (*size_x < 1) || (*size_y < 1))
    {
        printf("Failed to create matrix with this size.\n");
        return 1;
    }

    return 0;
}

int ReadMatrixParameters(int* size_x, int* size_y, float* value)
{
    if (scanf("%d %d %f", size_x, size_y, value) != 3)
    {
        printf("Failed to create matrix with this size.\n");
        return 1;
    }

    return 0;
}



