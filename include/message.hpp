#pragma once

#include <cstdint>
#include <ctime>

#define MAX_PIXELS 256
#define IMG_SIZE MAX_PIXELS * MAX_PIXELS * 3

typedef struct ImageRaw {
    uint8_t data[IMG_SIZE];
    clock_t timestamp;
} ImageRaw;

typedef struct ProcessedValue {
    double data;
    clock_t timestamp;
} ProcessedValue;
