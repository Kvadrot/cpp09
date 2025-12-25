/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/25 12:16:57 by ufo              ###   ########.fr       */
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
    
    if (calculator.calculate(argv[1], result) < 0) {
        return 1;
    }
    std::cout << "result is: " << result << std::endl;
    
    return 0;
}