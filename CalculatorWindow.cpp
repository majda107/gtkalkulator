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

    for (int i = 0; i < 9; i++) {
//        this->m_number_grid.add(this->m_buttons[i]);
        this->m_number_grid.attach(this->m_buttons[i], i % 3, i / 3 + 1);
        this->m_buttons[i].set_label(std::to_string(i + 1));
        this->m_buttons[i].signal_clicked().connect(
                sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::m_button_press), i + 1));
    }

//    this->m_op_grid.add(this->m_result_button);
    this->m_number_grid.attach(this->m_result_button, 1, 5);
    this->m_result_button.signal_clicked().connect(
            sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::m_button_press), 10));
    this->m_result_button.set_label("=");

    this->m_number_grid.show_all();
//    this->m_op_grid.show_all();

    this->m_print_result();
}

void CalculatorWindow::m_print_result() {
    auto val = std::to_string(this->m_sum);
    bool dot = false;
    auto cut = 0;

    while ((cut < val.size()) && (!dot || val[cut] != '0')) {
        if (val[cut++] == '.') dot = true;
    }

    if (val[cut - 1] == '.') cut--;

    this->m_result_label.set_label(val.substr(0, cut));
}

void CalculatorWindow::m_button_press(int num) {
//    std::cout << num << std::endl;
    if (num == 10) {
        this->m_sum += this->m_last;
        this->m_print_result();
        this->m_sum = this->m_last = 0;
        return;
    }

    this->m_last = num;
    this->m_sum /= this->m_last;

    this->m_print_result();
}
