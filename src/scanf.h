#ifndef SCANF_H
#define SCANF_H

#include <stdio.h>
#include "main.h"


enum ProgramState ReadInput();
bool ClearBuffer();
int ReadMatrixSize(int* size_x, int* size_y);
int ReadMatrixParameters(int* size_x, int* size_y, float* value);

#endif
