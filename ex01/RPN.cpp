/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:33:25 by ufo               #+#    #+#             */
/*   Updated: 2025/12/19 23:30:31 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN:: RPN() {}
RPN:: RPN(const RPN& other) {
    this->_mainStack = other._mainStack;
}
RPN &RPN::operator = (const RPN &other) {
    if (this != &other) {
        this->_mainStack = other._mainStack;
    }
    return (*this);
}
RPN:: ~RPN() {}


int RPN::handle_digit(std::string token) {
    if (_mainStack.size() < 2) {
        _mainStack.push(token[0] - 48);

        return 200;
    }
    return -404;
}

int RPN::handle_sign(std::string token) {
    return 200;
}

int RPN:: calculate(const std::string &input, int &result) {
    std::string token;

    if (input.empty()) {
        return -404;
    }
    std::istringstream iss(input);
    while (iss >> token) {

        if (token.size() != 1) {
            return -405;

        } else if (token[0] == '+' || token[0] == '-' || 
                    token[0] == '*' || token[0] == '/') {
            if (handle_sign(token) < 0)
                return -406;

        } else if (std::isdigit(token[0]) == true) {
            if (handle_digit(token) < 0)
                return -407;
                
        } else {
            return -408;
            
        }
    }
    return 200;
}


