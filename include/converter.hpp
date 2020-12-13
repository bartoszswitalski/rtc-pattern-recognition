#pragma once

#include <algorithm>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "pqueue.hpp"

#define MAX_COLOR 255
#define MIN_COLOR 0
#define MAX_PIXELS 256
#define DELAY 10
#define ESC_KEY 27
#define CONV_ARGS 2
#define CONFIG_IDX 1
#define POINT_RADIUS 2
#define LONGEST_CONTOUR 0
#define HULLS_NUMBER 1
#define INIT_ZERO 0
#define CONTOUR_IDX 0
#define MAIN_HULL 0

int global_h_min;
int global_h_max;
int global_s_min;
int global_s_max;
int global_v_min;
int global_v_max;

double process(cv::Mat img);

int main(int argc, char *argv[]);