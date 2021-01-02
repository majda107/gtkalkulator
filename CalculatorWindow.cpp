//
// Created by Majda on 30/12/2020.
//

#include "CalculatorWindow.h"


CalculatorWindow::CalculatorWindow() {
    this->add(this->m_number_grid);
//    this->add(this->m_op_grid);

    this->m_number_grid.set_row_homogeneous(true);
    this->m_number_grid.set_column_homogeneous(true);

    this->m_number_grid.attach(this->m_result_label, 1, 0);

    for (int i = 0; i < 10; i++) {
//        this->m_number_grid.add(this->m_buttons[i]);
        if (i == 0)
            this->m_number_grid.attach(this->m_buttons[i], 0, 5);
        else
            this->m_number_grid.attach(this->m_buttons[i], (i - 1) % 3, 4 - (i - 1) / 3);

        this->m_buttons[i].set_label(std::to_string(i));
        this->m_buttons[i].signal_clicked().connect(
                sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::m_button_press), i));
    }

    for (int i = 0; i < 4; i++) {
        this->m_number_grid.attach(this->m_operations[i], 3, 1 + i);
        this->m_operations[i].set_label(std::string(1, this->m_operation_chars[i]));
        this->m_operations[i].signal_clicked().connect(
                sigc::bind<char>(sigc::mem_fun(*this, &CalculatorWindow::m_operation_press),
                                 this->m_operation_chars[i]));
    }

//    this->m_op_grid.add(this->m_result_button);
    this->m_number_grid.attach(this->m_result_button, 3, 5);
    this->m_result_button.signal_clicked().connect(
            sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::m_button_press), 10));
    this->m_result_button.set_label("=");


    this->m_number_grid.attach(this->m_comma, 2, 5);
    this->m_comma.signal_clicked().connect(sigc::mem_fun(*this, &CalculatorWindow::m_add_comma));
    this->m_comma.set_label(",");

    this->m_number_grid.attach(this->m_clear_button, 0, 1);
    this->m_clear_button.signal_clicked().connect(sigc::mem_fun(*this, &CalculatorWindow::m_clear));
    this->m_clear_button.set_label("C");

    this->m_number_grid.show_all();
//    this->m_op_grid.show_all();

    this->m_number_grid.set_size_request(30, 30);

    this->m_refresh(this->m_sum);
}

void CalculatorWindow::m_operation_press(char op) {
//    if (this->m_op != 0) {
//        this->m_sum = this->m_operate(this->m_op, this->m_sum, this->m_last);
//        this->m_refresh(this->m_sum);
//    }

    this->m_op = op;
//    this->m_last = this->m_sum;
//    this->m_sum = 0;

//    this->m_buffer2 = this->m_buffer;
    if (this->m_result != "")
        this->m_buffer = std::stod(this->m_result);
    else
        this->m_buffer = std::stod(this->m_input);

    this->m_input = this->m_result = "";
    this->m_refresh(0);
}

void CalculatorWindow::m_add_comma() {
//    std::cout << "." << std::endl;

    if (this->m_input.find('.') != std::string::npos || this->m_input.size() <= 0) return;
    this->m_input += ".";

    this->m_refresh(0);
}

void CalculatorWindow::m_clear() {
    this->m_input = this->m_result = "";
    this->m_buffer = 0;
    this->m_refresh(0);
}

float CalculatorWindow::m_operate(char op, float n, float m) {
    switch (op) {
        case '+':
            return n + m;
        case '-':
            return n - m;
        case '*':
            return n * m;
        case '/':
            return n / m;
    }

    return 0;
}

void CalculatorWindow::m_refresh(float n) {
//    auto val = std::to_string(n);
    auto val = this->m_input;
    if (this->m_result != "") val = this->m_result;

    bool dot = false;
    auto cut = 0;

    while ((cut < val.size()) && (!dot || val[cut] != '0')) {
        if (val[cut++] == '.') dot = true;
    }

    if (val[cut - 1] == '.') cut--;

    this->m_result_label.set_label(val.substr(0, cut));
    if (val == "") this->m_result_label.set_label("0");

//    this->m_result_label.set_label(val);
}

void CalculatorWindow::m_button_press(int num) {
//    if (num == 10) {
//        this->m_sum += this->m_last;
//        this->m_print_result();
//        this->m_sum = this->m_last = 0;
//        return;
//    }
//
//    this->m_last = num;
//    this->m_sum /= this->m_last;
//
//    this->m_print_result();

//    if (num == 10) {
//        this->m_last = this->m_operate(this->m_op, this->m_sum, this->m_last);
//        this->m_print_result(this->m_last);
//        return;
//    }
//
//    this->m_sum = this->m_sum * 10 + num;
//    this->m_print_result(this->m_sum);

    if (num == 10) {
//        auto tmp = this->m_buffer;
//        this->m_buffer = std::stod(this->m_input);
//        this->m_input = std::to_string(this->m_operate(this->m_op, tmp, this->m_buffer));
//        this->m_input = std::to_string(this->m_operate(this->m_op, tmp, this->m_buffer));

        this->m_buffer = this->m_operate(this->m_op, std::stod(this->m_input), this->m_buffer);
        this->m_result = std::to_string(this->m_buffer);
//        this->m_input = std::to_string(this->m_buffer2);

//        this->m_result_label.set_label(std::to_string(this->m_buffer));
        this->m_refresh(0);

        return;

//        this->m_refresh(0);
    }

    this->m_input += std::to_string(num);
    this->m_refresh(0);
}
