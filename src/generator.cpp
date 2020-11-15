#include <algorithm>
#include <opencv2/opencv.hpp>

#include "pqueue.hpp"

cv::Rect getCropROI(cv::VideoCapture *camera) {
    cv::Mat img;
    *camera >> img;

    int w = img.size().width;
    int h = img.size().height;

    int size = std::min(w, h);

    int dw = std::abs(w - size);
    int dh = std::abs(h - size);

    return cv::Rect(dw / 2, dh / 2, size, size);
}

int main() {
    cv::VideoCapture camera(-1);

    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    cv::Rect roi = getCropROI(&camera);

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    cv::Mat img;
    ImageRaw m;

    while (true) {
        camera >> img;
        img = img(roi);
        cv::resize(img, img, cv::Size(256, 256), 0, 0, cv::INTER_LINEAR);

        memcpy(&m.data, img.data, sizeof(uint8_t) * IMG_SIZE);

        // TODO:
        //   should timestamp be set before mutex or inside mutex?
        //   or multiple timestamp variables?
        //   timestampInit, timestampPush, timestampPop
        m.timestamp = clock();

        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&m);

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);

        std::cout << "[GENE] added value: " << (int)m.data[0] << std::endl;
    }

    return 0;
}
