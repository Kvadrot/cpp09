/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/19 23:41:18 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "RPN.hpp"



/* ===================== MAIN ===================== */

int main(int argc, char **argv) {
    std::string token;
    RPN calculator;
    int result;
    
    if (argc != 2) {
        std::cerr << "wrong num of input param" << std::endl;
        return 1;
    }
    
    calculator.calculate(argv[1], result);
    
    
    return 0;
}