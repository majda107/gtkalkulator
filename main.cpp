#include <iostream>
#include <gtkmm.h>
#include <gtkmm/builder.h>

#include "CalculatorWindow.h"

int main(int argc, char *argv[]) {
    auto app =
            Gtk::Application::create(argc, argv,
                                     "org.gtkmm.examples.base");

//    Gtk::Window window;
//    window.set_default_size(200, 200);

    CalculatorWindow calc;

//    auto b = Gtk::Builder::create_from_file("gui.glade");
//    auto b = Gtk::Builder::create_from_file("gui.glade");

//    FrmMain *win = 0;
//    b->get_widget("main", win);

    return app->run(calc);
}
