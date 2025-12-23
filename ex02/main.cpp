/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/23 20:14:33 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include "PmergeMe.hpp"

bool isValidInput(const std::string &param) {
    if (param.empty() == true) {
        return false;
    }
    for (size_t i = 0; i <  param.size(); i++) {
        if (std::isdigit(static_cast<unsigned char>(param[i])) == false) {
            std::cerr << "Error: Your input must contain only positive digits" << std::endl;
            return false;
        }
    }
    return true;
}

bool convert(const std::string &param, int &value)
{
    if (param.empty())
    {
        std::cerr << "Error: empty argument" << std::endl;
        return false;
    }

    char *end;
    long tmp = std::strtol(param.c_str(), &end, 10);

    if (*end != '\0')
    {
        std::cerr << "Error: invalid number" << std::endl;
        return false;
    }
    if (tmp < 0 || tmp > INT_MAX)
    {
        std::cerr << "Error: number out of int range" << std::endl;
        return false;
    }

    value = static_cast<int>(tmp);
    return true;
}

/* ===================== MAIN ===================== */

int main(int argc, char **argv) {

    std::set<int> unic;
    std::vector<int> arr;
    std::deque<int>  deq;
    
    if (argc < 2) {
        std::cerr << "Error: Wrong amount of input params" << std::endl;
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        if (isValidInput(argv[i]) == false) {
            return 1;
        }
    }

    for (int i = 1; i < argc; i++) {
        
        int num;
        if (convert(std::string(argv[i]), num) == false)
            return 2;
            
        if (unic.insert(num).second == false) {
            std::cerr << "Error: Your input contains duplicates" << std::endl;
            return 3;   
        }
        
        arr.push_back(num);
        deq.push_back(num);
    }

    PmergeMe test = PmergeMe(arr, deq);
    test.sort();
    
    return 0;
}