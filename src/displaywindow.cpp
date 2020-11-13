#include "displaywindow.hpp"

DisplayWindow::DisplayWindow() {
    shmidB = shmget(KEY_B, sizeof(PQueue<ProcessedValue>), 0);
    pqB = (PQueue<ProcessedValue> *)shmat(shmidB, NULL, 0);


    set_default_size(180, 40);
    set_title("Displayer");
    
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // Create a Label to display the values, centered and expanded horizontally
    view = Gtk::manage(new Gtk::Label{"", Gtk::ALIGN_CENTER});
    view->set_hexpand(true);
    vbox->add(*view);

    // Connect the "timeout" signal to the on_timer method
    // Call it once every 1000 milliseconds until it returns false
    Glib::signal_timeout().connect([this] {return this->on_new_value();}, 50);
    // Prior to lambdas, we would have done this instead:
    //    Glib::signal_timeout().connect(sigc::mem_fun(*this, &Mainwin::on_timer), 1000);

    // Initialize the display during the first second
    on_new_value();

    vbox->show_all();
}

DisplayWindow::~DisplayWindow() { }

bool DisplayWindow::on_new_value() {
    ProcessedValue v;

    down(pqB->getSemid(), FULL);
    down(pqB->getSemid(), BIN);

    v = pqB->pop();
    view->set_text(std::to_string(v.data));

    up(pqB->getSemid(), BIN);
    up(pqB->getSemid(), EMPTY);

    return true; 
}

