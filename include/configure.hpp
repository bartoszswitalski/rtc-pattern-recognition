#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <fstream>

#define CAMERA_IDX 2
#define SPACE 32
#define DELAY 10
#define H_MIN 255
#define S_MIN 255
#define V_MIN 255
#define H_MAX 0
#define S_MAX 0
#define V_MAX 0

int global_h_max = 255;
int global_s_max = 255;
int global_v_max = 255;
int global_h_min = 0;
int global_s_min = 0;
int global_v_min = 0;

cv::Mat img, hsv, thresh;
std::vector<cv::Point> points;

bool getHSV(int event, int x, int y, int flags, void* param);

int main();