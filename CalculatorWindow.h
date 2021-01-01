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

    float m_operate(char op, float n, float m);

    void m_print_result();

    double m_sum = 0;
    double m_last = 0;
    char m_op = 0;

    Gtk::Grid m_number_grid;
//    Gtk::Grid m_op_grid;

    Gtk::Button m_buttons[9];

    Gtk::Button m_operations[4];
    char m_operation_chars[4] = {'+', '-', '/', '*'};

    Gtk::Button m_result_button;

    Gtk::Label m_result_label;
};


#endif //GTKALKULATOR_CALCULATORWINDOW_H
