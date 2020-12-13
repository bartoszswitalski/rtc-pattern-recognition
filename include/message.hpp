#pragma once

#include <cstdint>
#include <ctime>

#define MAX_PIXELS 256
#define IMG_SIZE MAX_PIXELS * MAX_PIXELS * 3

typedef struct Timestamp {
    clock_t init_time;
    clock_t push_time;
    clock_t pop_time;
} Timestamp;

typedef struct ImageRaw {
    uint8_t data[IMG_SIZE];
    Timestamp tstamp;
} ImageRaw;

typedef struct ProcessedValue {
    double data;
    Timestamp img_tstamp;
    Timestamp tstamp;
} ProcessedValue;
