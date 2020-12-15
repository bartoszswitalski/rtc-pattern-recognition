#include "displaywindow.hpp"

int main(int argc, char *argv[]) {
//    struct sched_param sp;
//    sp.sched_priority = 99;
//    sched_setscheduler(0, SCHED_FIFO, &sp);
    // Make a new app
    auto app = Gtk::Application::create(argc, argv, "com.lg.clock");

    // Instance a Window
    DisplayWindow disp;

    // Tell the app to run the Window
    return app->run(disp);
}