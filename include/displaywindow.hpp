#pragma once

#include <gtkmm.h>
#include <string>
#include <fstream>

#include "pqueue.hpp"

#define WIDTH 180
#define HEIGHT 40

class DisplayWindow : public Gtk::Window {
    public:
        DisplayWindow();
        virtual ~DisplayWindow();
    protected:
        bool on_new_value();
    private:
        int shmidB;
        PQueue<ProcessedValue> *pqB;
        Gtk::Label *view;
        void log_time(ProcessedValue v);
};