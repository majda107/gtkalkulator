//
// Created by Majda on 30/12/2020.
//

#include "CalculatorWindow.h"


CalculatorWindow::CalculatorWindow() {
    this->get_style_context()->add_class("window");

    this->add(this->m_number_grid);
    this->set_title("Calculator");

    this->m_number_grid.set_row_homogeneous(true);
    this->m_number_grid.set_column_homogeneous(true);
    this->m_number_grid.set_column_spacing(8);
    this->m_number_grid.set_row_spacing(8);
    this->m_number_grid.get_style_context()->add_class("grid");

    this->m_number_grid.attach(this->m_result_label, 0, 0, 4);
    this->m_result_label.get_style_context()->add_class("result");
    this->m_result_label.set_justify(Gtk::JUSTIFY_RIGHT);

    for (int i = 0; i < 10; i++) {
        this->m_buttons[i].set_size_request(60, 60);
//        this->m_number_grid.add(this->m_buttons[i]);
        if (i == 0)
            this->m_number_grid.attach(this->m_buttons[i], 0, 5, 2);
        else
            this->m_number_grid.attach(this->m_buttons[i], (i - 1) % 3, 4 - (i - 1) / 3);

        this->m_buttons[i].set_label(std::to_string(i));
        this->m_buttons[i].signal_clicked().connect(
                sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::m_button_press), i));
    }

    for (int i = 0; i < 4; i++) {
        this->m_number_grid.attach(this->m_operations[i], 3, 1 + i);
        this->m_operations[i].set_label(std::string(1, this->m_operation_chars[i]));
        this->m_operations[i].get_style_context()->add_class("orange");
        this->m_operations[i].signal_clicked().connect(
                sigc::bind<char>(sigc::mem_fun(*this, &CalculatorWindow::m_operation_press),
                                 this->m_operation_chars[i]));
    }

//    this->m_op_grid.add(this->m_result_button);
    this->m_number_grid.attach(this->m_result_button, 3, 5);
    this->m_result_button.signal_clicked().connect(
            sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::m_button_press), 10));
    this->m_result_button.set_label("=");
    this->m_result_button.get_style_context()->add_class("orange");


    this->m_number_grid.attach(this->m_comma_button, 2, 5);
    this->m_comma_button.signal_clicked().connect(sigc::mem_fun(*this, &CalculatorWindow::m_add_comma));
    this->m_comma_button.set_label(",");

    this->m_number_grid.attach(this->m_clear_button, 0, 1);
    this->m_clear_button.signal_clicked().connect(sigc::mem_fun(*this, &CalculatorWindow::m_clear));
    this->m_clear_button.set_label("C");
    this->m_clear_button.get_style_context()->add_class("gray");

    this->m_number_grid.attach(this->m_sign_button, 1, 1);
    this->m_sign_button.signal_clicked().connect(sigc::mem_fun(*this, &CalculatorWindow::m_toggle_sign));
    this->m_sign_button.set_label("+/-");
    this->m_sign_button.get_style_context()->add_class("gray");

    this->m_number_grid.attach(this->m_perc_button, 2, 1);
    this->m_perc_button.signal_clicked().connect(sigc::mem_fun(*this, &CalculatorWindow::m_perc));
    this->m_perc_button.set_label("%");
    this->m_perc_button.get_style_context()->add_class("gray");

    this->m_number_grid.show_all();
//    this->m_op_grid.show_all();

    this->m_number_grid.set_size_request(30, 30);

    this->m_refresh();
}

void CalculatorWindow::m_operation_press(char op) {

    this->m_op = op;

    try {

        // BUFFER RESULT IF ITS NOT EMPTY
        if (this->m_result != "")
            this->m_buffer = std::stod(this->m_result);
        else
            this->m_buffer = std::stod(this->m_input);

    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

    this->m_input = this->m_result = "";
    this->m_refresh();
}

void CalculatorWindow::m_perc() {
    try {
        double p = std::stod(this->m_input);
        p /= 100.0;
        this->m_input = std::to_string(p);
        this->m_refresh();
    } catch (const std::exception e) {
        std::cout << "error!" << std::endl;
    }
}

void CalculatorWindow::m_toggle_sign() {
    if (this->m_input.size() <= 0) return;

    if (this->m_input[0] == '-') this->m_input = this->m_input.substr(1, this->m_input.size() - 1);
    else this->m_input = "-" + this->m_input;

    this->m_refresh();
}

void CalculatorWindow::m_add_comma() {
//    std::cout << "." << std::endl;

    if (this->m_input.find('.') != std::string::npos || this->m_input.size() <= 0) return;
    this->m_input += ".";

    this->m_refresh();
}

void CalculatorWindow::m_clear() {
    this->m_input = this->m_result = "";
    this->m_buffer = 0;
    this->m_refresh();
}

double CalculatorWindow::m_operate(char op, double n, double m) {
    switch (op) {
        case '+':
            return n + m;
        case '-':
            return n - m;
        case '*':
            return n * m;
        case '/':
            if (m == 0) return NAN;
            return n / m;
    }

    return 0;
}

void CalculatorWindow::m_refresh() {
//    auto val = std::to_string(n);
    auto val = this->m_input;
    if (this->m_result != "") val = this->m_result;

    bool dot = false;
//    auto cut = 0;
//    auto last_nonzero;
//
//    while ((cut < val.size()) && (!dot || val[cut] != '0')) {
//        if (val[cut++] == '.') dot = true;
//    }

    auto lnz = val.size();
//    auto dot = 0;
    for (int i = 0; i < val.size(); i++) {
        if (val[i] == '.') dot = true;
        if (dot && val[i] != '0') lnz = i + 1;
    }

    if (val[lnz - 1] == '.') lnz--;

//    this->m_result_label.set_label(val.substr(0, cut));
    this->m_result_label.set_label(val.substr(0, lnz));
    if (val == "") this->m_result_label.set_label("0");

//    this->m_result_label.set_label(val);
}

void CalculatorWindow::m_button_press(int num) {

    if (num == 10) {
//        auto tmp = this->m_buffer;
//        this->m_buffer = std::stod(this->m_input);
//        this->m_input = std::to_string(this->m_operate(this->m_op, tmp, this->m_buffer));
//        this->m_input = std::to_string(this->m_operate(this->m_op, tmp, this->m_buffer));

        try {

            std::cout << this->m_input << std::endl;

            auto num = this->m_input == "" ? 0 : std::stod(this->m_input);

            this->m_buffer = this->m_operate(this->m_op, this->m_buffer, num);
            this->m_result = std::to_string(this->m_buffer);
            this->m_refresh();

        } catch (std::exception e) {
            std::cout << "error " << e.what() << std::endl;
        }

        return;

//        this->m_refresh(0);
    }

    // CLEAR IF OVERRIDING PREV RESULT
    if (this->m_result != "")
        this->m_clear();


    if (this->m_input.size() > 0 || num != 0)
        this->m_input += std::to_string(num);

    this->m_refresh();
}
