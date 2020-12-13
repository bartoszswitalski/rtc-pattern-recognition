#include "configure.hpp"

int main() {
    cv::VideoCapture camera(CAMERA_IDX);

    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    cv::namedWindow("img");

    std::cout << "Press 'space' to freeze frame." << std::endl;

    while (cv::waitKey(DELAY) != SPACE) {
        camera >> img;
        cv::imshow("img", img);
    };

    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::setMouseCallback("img", [](int event, int x, int y, int flags, void* param) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            cv::Point p(x, y);

            int h = hsv.at<cv::Vec3b>(p)[0];
            int s = hsv.at<cv::Vec3b>(p)[1];
            int v = hsv.at<cv::Vec3b>(p)[2];

            global_h_min = std::min(global_h_min, h);
            global_s_min = std::min(global_s_min, s);
            global_v_min = std::min(global_v_min, v);

            global_h_max = std::max(global_h_max, h);
            global_s_max = std::max(global_s_max, s);
            global_v_max = std::max(global_v_max, v);
        }
    });

    std::cout << "Image frozen." << std::endl;
    std::cout << "Start clicking on pixels of interest." << std::endl;
    std::cout << "Press 'space' to save and exit." << std::endl;

    while (cv::waitKey(DELAY) != SPACE) {
        cv::inRange(hsv, cv::Scalar(global_h_min, global_s_min, global_v_min), cv::Scalar(global_h_max, global_s_max, global_v_max), thresh);
        cv::imshow("img", img);
        cv::imshow("thresh", thresh);
    };

    std::ofstream config_file;
    config_file.open("config.txt");
    config_file << global_h_min << std::endl;
    config_file << global_s_min << std::endl;
    config_file << global_v_min << std::endl;
    config_file << global_h_max << std::endl;
    config_file << global_s_max << std::endl;
    config_file << global_v_max << std::endl;
    config_file.close();

    return 0;
}

