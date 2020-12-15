#include "converter.hpp"

double process(cv::Mat img) {
    if (img.empty()) {
        std::cout << "Image is empty." << std::endl;
        return 0;
    }

    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::Mat thresh;
    cv::inRange(hsv, cv::Scalar(global_h_min, global_s_min, global_v_min),
                cv::Scalar(global_h_max, global_s_max, global_v_max), thresh);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    std::sort(contours.begin(), contours.end(), [](auto lhs, auto rhs) {
        return lhs.size() > rhs.size();
    });

    if (contours.size() <= 0) {
        return 0;
    }

    cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    cv::drawContours(mask, contours, CONTOUR_IDX, MAX_COLOR, cv::FILLED);

    std::vector<std::vector<cv::Point>> hulls(HULLS_NUMBER);
    cv::convexHull(contours[LONGEST_CONTOUR], hulls[MAIN_HULL]);

    cv::Mat hull_mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    cv::drawContours(hull_mask, hulls, CONTOUR_IDX, MAX_COLOR, cv::FILLED);

    cv::Point center(INIT_ZERO, INIT_ZERO);

    for (cv::Point p : contours[0]) {
        center += p;
    }

    center.x /= contours[LONGEST_CONTOUR].size();
    center.y /= contours[LONGEST_CONTOUR].size();

    // Blue colored circle
    cv::circle(img, center, POINT_RADIUS, cv::Scalar(MIN_COLOR, MIN_COLOR, MAX_COLOR), cv::FILLED);

    cv::Point max_point;
    long long max_dist = INIT_ZERO;

    for (cv::Point p : hulls[MAIN_HULL]) {
        long long dist = (center.x - p.x) * (center.x - p.x) + (center.y - p.y) * (center.y - p.y);

        if (dist > max_dist) {
            max_point = p;
            max_dist = dist;
        }
    }

    // Red colored circle
    cv::circle(img, max_point, POINT_RADIUS, cv::Scalar(MAX_COLOR, MIN_COLOR, MIN_COLOR), cv::FILLED);

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
//    struct sched_param sp;
//    sp.sched_priority = 99;
//    sched_setscheduler(0, SCHED_FIFO, &sp);

    if (argc != CONV_ARGS) {
        std::cout << "Usage: ./converter config.txt" << std::endl;
        return 1;
    }

    std::ifstream config(argv[CONFIG_IDX]);

    if (!config.is_open()) {
        std::cout << "Failed to open config file." << std::endl;
        return 1;
    }

    config >> global_h_min >> global_s_min >> global_v_min >> global_h_max >> global_s_max >> global_v_max;
    config.close();

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    PQueue<ProcessedValue> *pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    ImageRaw m;
    ProcessedValue v;

    // TODO: while true
    while (cv::waitKey(DELAY) != ESC_KEY) {
        down(pqA->getSemid(), FULL);
        down(pqA->getSemid(), BIN);

        m = pqA->pop();

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), EMPTY);

        cv::Mat img(MAX_PIXELS, MAX_PIXELS, CV_8UC3, m.data);
        cv::imshow("Converter", img);

        v.data = process(img);
        v.tstamp.init_time = std::chrono::system_clock::now();
        v.img_tstamp = m.tstamp;

        down(pqB->getSemid(), EMPTY);
        down(pqB->getSemid(), BIN);

        pqB->push(&v);

        up(pqB->getSemid(), BIN);
        up(pqB->getSemid(), FULL);
    }
}
