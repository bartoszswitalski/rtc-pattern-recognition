#pragma once

#include <cstdint>
#include <ctime>

#define IMG_SIZE 256 * 256 * 3

typedef struct ImageRaw {
    uint8_t data[IMG_SIZE];
    clock_t timestamp;
} ImageRaw;

typedef struct ProcessedValue {
    double data;
    clock_t timestamp;
} ProcessedValue;
