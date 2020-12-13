#include <algorithm>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "pqueue.hpp"

int h_min, h_max, s_min, S_MAX, V_MIN, V_MAX;

double process(cv::Mat img) {
    if (img.empty()) {
        std::cout << "Image is empty." << std::endl;
        return 0;
    }

    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::Mat thresh;
    cv::inRange(hsv, cv::Scalar(h_min, s_min, V_MIN), cv::Scalar(h_max, S_MAX, V_MAX), thresh);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    std::sort(contours.begin(), contours.end(), [](auto lhs, auto rhs) {
        return lhs.size() > rhs.size();
    });

    if (contours.size() <= 0) {
        return 0;
    }

    cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    cv::drawContours(mask, contours, 0, 255, cv::FILLED);

    std::vector<std::vector<cv::Point>> hulls(1);
    cv::convexHull(contours[0], hulls[0]);

    cv::Mat hull_mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    cv::drawContours(hull_mask, hulls, 0, 255, cv::FILLED);

    cv::Point center(0, 0);

    for (cv::Point p : contours[0]) {
        center += p;
    }

    center.x /= contours[0].size();
    center.y /= contours[0].size();

    cv::circle(img, center, 2, cv::Scalar(0, 0, 255), cv::FILLED);

    cv::Point max_point;
    long long max_dist = 0;

    for (cv::Point p : hulls[0]) {
        long long dist = (center.x - p.x) * (center.x - p.x) + (center.y - p.y) * (center.y - p.y);

        if (dist > max_dist) {
            max_point = p;
            max_dist = dist;
        }
    }

    cv::circle(img, max_point, 2, cv::Scalar(255, 0, 0), cv::FILLED);

    double dy = center.y - max_point.y;
    double dx = center.x - max_point.x;
    double a = dy / dx;

    cv::imshow("img", img);
    cv::imshow("thresh", thresh);
    cv::imshow("mask", mask);
    cv::imshow("hull_mask", hull_mask);

    return a;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./converter config.txt" << std::endl;
        return 1;
    }

    std::ifstream config(argv[1]);

    if (!config.is_open()) {
        std::cout << "Failed to open config file." << std::endl;
        return 1;
    }

    config >> h_min >> s_min >> V_MIN >> h_max >> S_MAX >> V_MAX;
    config.close();

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    PQueue<ProcessedValue> *pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    ImageRaw m;
    ProcessedValue v;

    // TODO: while true
    while (cv::waitKey(10) != 27) {
        down(pqA->getSemid(), FULL);
        down(pqA->getSemid(), BIN);

        m = pqA->pop();

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), EMPTY);

        cv::Mat img(256, 256, CV_8UC3, m.data);
        cv::imshow("Converter", img);

        v.data = process(img);
        // TODO:
        //   should timestamp be set before mutex or inside mutex?
        //   or multiple timestamp variables?
        //   timestampInit, timestampPush, timestampPop
        v.timestamp = clock();

        down(pqB->getSemid(), EMPTY);
        down(pqB->getSemid(), BIN);

        pqB->push(&v);

        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), FULL);
    }
}
