#pragma once

#include <gtkmm.h>
#include <string>

#include "pqueue.hpp"

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
};