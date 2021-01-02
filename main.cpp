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

    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data("button {color: #C71EFF; border-radius: 100px;}");

    Glib::RefPtr<Gtk::StyleContext> styleContext = Gtk::StyleContext::create();

    //get default screen
    Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();

    //add provider for screen in all application
    styleContext->add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    return app->run(calc);
}
