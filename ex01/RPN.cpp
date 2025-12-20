/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:33:25 by ufo               #+#    #+#             */
/*   Updated: 2025/12/20 20:30:08 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void printStack(std::stack<int> st)
{
    while (!st.empty())
    {
        std::cout << st.top() << std::endl;
        st.pop();
    }
}

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


void RPN::handle_digit(const std::string &token) {
    _mainStack.push(token[0] - '0'); 
}

int RPN::handle_sign(const std::string &token) {

    if (_mainStack.size() < 2) {
        std::cerr << "Error: not enough args for operation: " << token[0] << std::endl;
        return -404;
    }

    int recent = _mainStack.top(); _mainStack.pop();
    int older = _mainStack.top(); _mainStack.pop();
    if (recent == 0 && token[0] == '/') {
        std::cerr << "Error: forbiden operation(devision by 0)" << std::endl;
        return -406;
    }
    // std::cout << "older: " << older  << " operation: " << token[0] << " recent:  " << recent  << std::endl;
     
    switch (token[0]) {
        case '+':
            _mainStack.push(older + recent);
            break;
            
        case '-':
            _mainStack.push(older - recent);
            break;

        case '*':
            _mainStack.push(older * recent);
            break;

        case '/':
            _mainStack.push(older / recent);
            break;

        default:
            return (-405);
    }
    return 200;
}

int RPN:: calculate(const std::string &input, int &result) {
    std::string token;

    while (!_mainStack.empty())
        _mainStack.pop();

    if (input.empty()) {
        std::cerr << "Error: input is empty \n";
        return -404;
    }
    std::istringstream iss(input);
    while (iss >> token) {

        if (token.size() != 1) {
            std::cerr << "Error: wrong args, args might be single digit numbers, separated by space \n";
            return -405;

        } else if (token[0] == '+' || token[0] == '-' || 
                    token[0] == '*' || token[0] == '/') {
            int code = handle_sign(token);
            if (code < 0)
                return code;   

        } else if (std::isdigit(token[0]) == true) {
            handle_digit(token);
                
        } else {
            std::cerr << "Error: wrong arg type: " << token[0] << " args might be single digit numbers, separated by space \n";
            return -408;
        }
    }
    
    if (_mainStack.size() != 1) {
        std::cerr << "Error: couldn't calculate result as there more than 1 num in stack after all operations \n";
        return (-409);
    }
    result = _mainStack.top();

    return 200;
}


