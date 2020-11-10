#include <opencv2/opencv.hpp>

#include "pqueue.hpp"

int main() {
    cv::VideoCapture camera(-1);

    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    cv::Mat img;

    /*
    while (cv::waitKey(10) != 27) {
        camera >> img;
        cv::resize(img, img, cv::Size(256, 256), 0, 0, CV_INTER_LINEAR);
        uint8_t *pixels = (uint8_t *)img.data;
        // cv::rotate(img, img, cv::ROTATE_90_CLOCKWISE);
        // cv::rotate(img, img, cv::ROTATE_90_COUNTERCLOCKWISE);
        // cv::rotate(img, img, cv::ROTATE_180);
        cv::imshow("Generator", img);
    };

    // TODO: add the image to the queue
    return 0;*/

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    ImageRaw m;

    while (true) {
        camera >> img;
        cv::resize(img, img, cv::Size(256, 256), 0, 0, CV_INTER_LINEAR);
        uint8_t *pixels = (uint8_t *)img.data;

        memcpy(&m.data, pixels, sizeof(uint8_t) * IMG_SIZE);
        m.timestamp = clock();

        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&m);
        std::cout << "[GENE] added value: " << (int)m.data[0] << std::endl;

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);
    }

    return 0;
}
