#include "displaywindow.hpp"

int main(int argc, char *argv[]) {
    // Make a new app
    auto app = Gtk::Application::create(argc, argv, "com.lg.clock");

    // Instance a Window
    DisplayWindow disp;

    // Tell the app to run the Window
    return app->run(disp);
}