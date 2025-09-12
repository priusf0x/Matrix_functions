#include <stdio.h>
#include "main.h"
#include "scanf.h"
#include "matrix_function.h"

MatrixCharacteristic MAIN_MATRIX  = {.matrix_type = RECTANGLE_MATRIX, .matrix_pointer = NULL, .size_x = 0, .size_y = 0};

int main(void)
{

    printf("Hello, This is my matrix functions demo.\n");

    StartStateMachine();

    free(MAIN_MATRIX.matrix_pointer);

    return 0;
}


void StartStateMachine()
{
    enum ProgramState state = PROGRAM_STATE_MENU;

    while (state != PROGRAM_STATE_EXIT)
    {
        switch (state)
        {
            case PROGRAM_STATE_MENU:
                state = ReadInput();
                break;

            case PROGRAM_STATE_EXIT:
                break;

            case PROGRAM_STATE_ERROR:
                printf("something bad happened\n");
                state = PROGRAM_STATE_EXIT;
                break;

            default:
                break;
        }
    }
}
