#include "displaywindow.hpp"

DisplayWindow::DisplayWindow() {
    shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);

    set_default_size(WIDTH, HEIGHT);
    set_title("Displayer");

    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    view = Gtk::manage(new Gtk::Label {"", Gtk::ALIGN_CENTER});
    view->set_hexpand(true);
    vbox->add(*view);

    Glib::signal_idle().connect([this]() { return this->on_new_value(); });

    vbox->show_all();
}

DisplayWindow::~DisplayWindow() {
}

bool DisplayWindow::on_new_value() {
    ProcessedValue v;

    down(pqB->getSemid(), FULL);
    down(pqB->getSemid(), BIN);

    v = pqB->pop();
   
    up(pqB->getSemid(), BIN);
    up(pqB->getSemid(), EMPTY);

    view->set_text(std::to_string(v.data));

    log_time(v);

    return true;
}

void DisplayWindow::log_time(ProcessedValue v) {
    std::ofstream fout;
    fout.open("times.log", std::ios::app);
    fout<<std::chrono::duration_cast<std::chrono::nanoseconds>(v.img_tstamp.init_time.time_since_epoch()).count()<<" "
        <<std::chrono::duration_cast<std::chrono::nanoseconds>(v.img_tstamp.push_time.time_since_epoch()).count()<<" "
        <<std::chrono::duration_cast<std::chrono::nanoseconds>(v.img_tstamp.pop_time.time_since_epoch()).count()<<" "
        <<std::chrono::duration_cast<std::chrono::nanoseconds>(v.tstamp.init_time.time_since_epoch()).count()<<" "
        <<std::chrono::duration_cast<std::chrono::nanoseconds>(v.tstamp.push_time.time_since_epoch()).count()<<" "
        <<std::chrono::duration_cast<std::chrono::nanoseconds>(v.tstamp.pop_time.time_since_epoch()).count()<<std::endl;
    fout.close();
}