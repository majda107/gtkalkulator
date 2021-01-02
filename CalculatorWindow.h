//
// Created by Majda on 30/12/2020.
//

#ifndef GTKALKULATOR_CALCULATORWINDOW_H
#define GTKALKULATOR_CALCULATORWINDOW_H

#include <gtkmm.h>;
#include <iostream>


class CalculatorWindow : public Gtk::Window {

public:
    CalculatorWindow();

private:
    void m_button_press(int num);

    void m_operation_press(char op);

    void m_add_comma();

    void m_toggle_sign();

    void m_perc();

    void m_clear();

    double m_operate(char op, double n, double m);

    void m_refresh();

    std::string m_input;
    std::string m_result;

    double m_buffer = 0;
    char m_op = 0;

    Gtk::Grid m_number_grid;

    Gtk::Button m_buttons[10];
    Gtk::Button m_result_button;
    Gtk::Button m_comma_button;
    Gtk::Button m_clear_button;
    Gtk::Button m_sign_button;
    Gtk::Button m_perc_button;
    Gtk::Button m_operations[4];

    char m_operation_chars[4] = {'+', '-', '/', '*'};


    Gtk::Label m_result_label;
};


#endif //GTKALKULATOR_CALCULATORWINDOW_H
