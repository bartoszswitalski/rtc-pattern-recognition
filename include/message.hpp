#pragma once

#include <cstdint>
#include <chrono>

#define MAX_PIXELS 256
#define IMG_SIZE MAX_PIXELS * MAX_PIXELS * 3

typedef std::chrono::time_point<std::chrono::system_clock> time_point;

typedef struct Timestamp {
    time_point init_time;
    time_point push_time;
    time_point pop_time;
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
