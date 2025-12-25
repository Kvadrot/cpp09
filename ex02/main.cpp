/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/25 15:21:19 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include "PmergeMe.hpp"

template <typename Container>
void printContainer(const Container &c)
{
    typename Container::const_iterator it = c.begin();
    while (it != c.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

template <typename Container>
bool isAscendingSort(const Container &c)
{
    typename Container::const_iterator it = c.begin();
    if (it == c.end())
        return true;

    typename Container::const_iterator next = it;
    ++next;

    while (next != c.end())
    {
        if (*it > *next)
            return false;
        ++it;
        ++next;
    }
    return true;
}


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
    
    std::vector <int> sortedArr = test.getSortedArr();
    std::deque <int> sortedDeq = test.getSortedDeq();
    double arrTime = test.getSortTimeArray() / 1000;
    double deqTime = test.getSortTimeDeque() / 1000;
    
    std::cout << "Before:  ";
    printContainer(arr);
    std::cout << std::endl;

    std::cout << "After:  ";
    printContainer(sortedArr);
    std::cout << std::endl;

    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << arrTime <<  " us" << std::endl;
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque : " << deqTime <<  " us" << std::endl;

    // printContainer(sortedArr);
    // if (isAscendingSort(sortedArr) == true)
    //     std::cout << "is sortedWell == true" << std::endl;
    // else
    //     std::cout << "is sortedWell == false" << std::endl;
    
    
    return 0;
}