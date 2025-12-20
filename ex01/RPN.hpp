/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:25:17 by ufo               #+#    #+#             */
/*   Updated: 2025/12/20 19:51:48 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN {
    private:
        std::stack<int> _mainStack;
        int handle_sign(const std::string &token);
        void handle_digit(const std::string &token);

    public:
        RPN();
        RPN(const RPN& other);
        RPN &operator=(const RPN& other);
        ~RPN();

        int calculate(const std::string &input, int &result);
    
    
};

#endif