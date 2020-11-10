#include "opencv2/opencv.hpp"
#include "pqueue.hpp"

int main() {
    cv::VideoCapture camera(-1);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    cv::Mat frame;

    while (cv::waitKey(10) != 27) {
        camera >> frame;
        cv::imshow("Source", frame);
    };

    // TODO: add the image to the queue
    return 0;

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    while (true) {
        ImageRaw m;
        m.data[0] = 123;
        m.timestamp = clock();

        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&m);
        std::cout << "[GENE] added item" << std::endl;

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);
    }

    return 0;
}
