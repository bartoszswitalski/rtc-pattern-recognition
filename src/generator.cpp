#include "generator.hpp"

cv::Rect getCropROI(cv::VideoCapture *camera) {
    cv::Mat img;
    *camera >> img;

    int width = img.size().width;
    int height = img.size().height;

    int size = std::min(width, height);

    int dw = std::abs(width - size);
    int dh = std::abs(height - size);

    return cv::Rect(dw / 2, dh / 2, size, size);
}

int main() {
//    struct sched_param sp;
//    sp.sched_priority = 99;
//    sched_setscheduler(0, SCHED_FIFO, &sp);

    cv::VideoCapture camera(CAMERA_IDX);

    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    int shmidA = shmget(KEY_A, sizeof(PQueue<ImageRaw>), 0);
    PQueue<ImageRaw> *pqA = (PQueue<ImageRaw> *)shmat(shmidA, NULL, 0);

    cv::Rect roi = getCropROI(&camera);
    cv::Mat img;
    ImageRaw message;

    while (true) {
        camera >> img;
        img = img(roi);
        cv::resize(img, img, cv::Size(MAX_PIXELS, MAX_PIXELS), 0, 0, cv::INTER_LINEAR);

        memcpy(&message.data, img.data, sizeof(uint8_t) * IMG_SIZE);
        message.tstamp.init_time = std::chrono::system_clock::now();

        down(pqA->getSemid(), EMPTY);
        down(pqA->getSemid(), BIN);

        pqA->push(&message);

        up(pqA->getSemid(), BIN);
        up(pqA->getSemid(), FULL);

        //std::cout << "[GENE] added value: " << (int)m.data[0] << std::endl;
    }

    return 0;
}
