#include <algorithm>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat img, hsv, thresh;
std::vector<cv::Point> points;

int h_min = 255, h_max = 0;
int s_min = 255, s_max = 0;
int v_min = 255, v_max = 0;

int main() {
    cv::VideoCapture camera(-1);

    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    cv::namedWindow("img");

    std::cout << "Press 'space' to freeze frame." << std::endl;

    while (cv::waitKey(10) != 32) {
        camera >> img;
        cv::imshow("img", img);
    };

    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::setMouseCallback("img", [](int event, int x, int y, int flags, void *param) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            cv::Point p(x, y);

            int h = hsv.at<cv::Vec3b>(p)[0];
            int s = hsv.at<cv::Vec3b>(p)[1];
            int v = hsv.at<cv::Vec3b>(p)[2];

            h_min = std::min(h_min, h);
            s_min = std::min(s_min, s);
            v_min = std::min(v_min, v);

            h_max = std::max(h_max, h);
            s_max = std::max(s_max, s);
            v_max = std::max(v_max, v);
        }
    });

    std::cout << "Image frozen." << std::endl;
    std::cout << "Start clicking on pixels of interest." << std::endl;
    std::cout << "Press 'space' to save and exit." << std::endl;

    while (cv::waitKey(10) != 32) {
        cv::inRange(hsv, cv::Scalar(h_min, s_min, v_min), cv::Scalar(h_max, s_max, v_max), thresh);
        cv::imshow("img", img);
        cv::imshow("thresh", thresh);
    };

    std::ofstream config_file;
    config_file.open("config.txt");
    config_file << h_min << std::endl;
    config_file << s_min << std::endl;
    config_file << v_min << std::endl;
    config_file << h_max << std::endl;
    config_file << s_max << std::endl;
    config_file << v_max << std::endl;
    config_file.close();

    return 0;
}

