#include <torch/script.h>

#include <opencv2/opencv.hpp>

#include "pqueue.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./conv path-to-model" << std::endl;
        exit(1);
    }

    torch::jit::script::Module model;

    try {
        model = torch::jit::load(argv[1]);
    } catch (const c10::Error &e) {
        std::cerr << "Failed to load model." << std::endl;
        exit(1);
    }
    return 0;

    // TODO: use the loaded model

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    int shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    PQueue<ProcessedValue> *pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    ImageRaw m;
    ProcessedValue v;

    while (true) {
        down(pqA->getSemid(), FULL);
        down(pqA->getSemid(), BIN);

        m = pqA->pop();

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), EMPTY);

        cv::Mat img(256, 256, CV_8UC3, m.data);
        cv::imshow("Converter", img);
        std::cout << "[CONV] got value: " << (int)m.data[0] << std::endl;

        v.data = (int)m.data[0];
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
