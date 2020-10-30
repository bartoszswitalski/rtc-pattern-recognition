#pragma once

#include <iostream>
#include <time.h>

#define IMG_SIZE 100

typedef struct ImageRaw{
    
    char c[IMG_SIZE];
    clock_t mesTime;

} ImageRaw;

typedef struct ProcessedValue{

    double v;
    clock_t mesTime;

} ProcessedValue;
