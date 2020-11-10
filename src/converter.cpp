#include <opencv2/opencv.hpp>

#include "pqueue.hpp"

int main() {
    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    PQueue<ProcessedValue> *pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    while (cv::waitKey(10) != 27) {
        ImageRaw m;

        down(pqA->getSemid(), FULL);
        down(pqA->getSemid(), BIN);

        m = pqA->pop();
        cv::Mat img(256, 256, CV_8UC3, m.data);
        cv::imshow("Converter", img);
        std::cout << "[CONV] got value: " << (int)m.data[0] << std::endl;

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), EMPTY);
    }
}
