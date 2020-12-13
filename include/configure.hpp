#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <fstream>

#define CAMERA_IDX 2
#define SPACE 32
#define DELAY 10

int global_h_max = 0;
int global_s_max = 0;
int global_v_max = 0;
int global_h_min = 255;
int global_s_min = 255;
int global_v_min = 255;

cv::Mat img, hsv, thresh;
std::vector<cv::Point> points;

int main();