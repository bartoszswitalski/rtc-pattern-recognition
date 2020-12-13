#pragma once

#include <algorithm>
#include <opencv2/opencv.hpp>

#include "pqueue.hpp"
#include "configure.hpp"

cv::Rect getCropROI(cv::VideoCapture *camera);

int main();