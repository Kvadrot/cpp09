/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:51:52 by ufo               #+#    #+#             */
/*   Updated: 2025/12/23 21:31:35 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename PairContainer>
void printPairedContainer(const PairContainer &paired)
{
    for (size_t i = 0; i < paired.size(); i++)
    {
        std::cout
            << "(small = " << paired[i].first
            << " | big = " << paired[i].second
            << ") ";
    }
    std::cout << std::endl;
}

PmergeMe::PmergeMe() : _timeVec(0.0), _timeDeq(0.0) {}

PmergeMe::PmergeMe(const std::vector<int> &v, const std::deque<int> &d)
    : _arr(v), _deq(d), _timeVec(0.0), _timeDeq(0.0) {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _arr(other._arr), _deq(other._deq),
      _timeVec(other._timeVec), _timeDeq(other._timeDeq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _arr = other._arr;
        _deq = other._deq;
        _timeVec = other._timeVec;
        _timeDeq = other._timeDeq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::splitArrIntoPairs(
    const std::vector<int> &arrToSplit,
    std::vector< std::pair<int,int> > &splitedPairs,
    bool &hasRemainder,
    int &remainder) {

    size_t arrSize;
    splitedPairs.clear();
    
    if (arrToSplit.size() % 2 != 0) {
        hasRemainder = true;
        arrSize = arrToSplit.size() - 1;
        remainder = arrToSplit[arrToSplit.size() - 1];
    } else {
        hasRemainder = false;
        arrSize = arrToSplit.size();
        remainder = 0;
    }
    
    for (size_t i = 0; i < arrSize - 1; i += 2) {
        int smaller = arrToSplit[i];
        int bigger = arrToSplit[i + 1];
        
        if (smaller > bigger)
            std::swap(smaller, bigger);

        std::pair<int,int> pair = std::make_pair(smaller, bigger);
        splitedPairs.push_back(pair);
    }
}

void  PmergeMe::splitDequeIntoPairs(
    const std::deque<int> &deqToSplit, 
    std::deque< std::pair<int,int> > &splitedPairs,
    bool &hasRemainder,
    int &remainder) {

    size_t deqSize;
    splitedPairs.clear();
    
    if (deqToSplit.size() % 2 != 0) {
        hasRemainder = true;
        deqSize = deqToSplit.size() - 1;
        remainder = deqToSplit[deqToSplit.size() - 1];
    } else {
        hasRemainder = false;
        deqSize = deqToSplit.size();
        remainder = 0;
    }
    
    for (size_t i = 0; i < deqSize - 1; i += 2) {
        int smaller = deqToSplit[i];
        int bigger = deqToSplit[i + 1];
        
        if (smaller > bigger)
            std::swap(smaller, bigger);

        std::pair<int,int> pair = std::make_pair(smaller, bigger);
        splitedPairs.push_back(pair);
    }
}

std::vector<int> PmergeMe::sortArr(const std::vector<int> &arr) {
    std::vector< std::pair<int,int> > splitedPairs;
    bool hasRemainder = false;
    int remainder = 0;

    splitArrIntoPairs(arr, splitedPairs, hasRemainder, remainder);
    // std::cout << "check the splited arr after splitArrIntoPairs()" << std::endl;
    // std::cout << "======================================================================" << std::endl;
    // printPairedContainer(splitedPairs);
    // std::cout << "======================================================================" << std::endl;
    std::vector <int> bigNums;
    std::vector <int> smallNums;

    for (int i = 0; i < splitedPairs.size(); i++) {
        smallNums.push_back(splitedPairs[i].first);
        bigNums.push_back(splitedPairs[i].second);
    }
    
    return _arr;
}

std::deque<int> PmergeMe::sortDeq(const std::deque<int> &deq) {
    std::deque< std::pair<int,int> > splitedPairs;
    bool hasRemainder = false;
    int remainder = 0;
    
    splitDequeIntoPairs(deq, splitedPairs, hasRemainder, remainder);
    // std::cout << "check the splited deq after splitDequeIntoPairs()" << std::endl;
    // std::cout << "======================================================================" << std::endl;
    // printPairedContainer(splitedPairs);
    // std::cout << "======================================================================" << std::endl;

    std::deque <int> bigNums;
    std::deque <int> smallNums;

    for (int i = 0; i < splitedPairs.size(); i++) {
        smallNums.push_back(splitedPairs[i].first);
        bigNums.push_back(splitedPairs[i].second);
    }
    
    return _deq;
}

void PmergeMe::sort() {
    clock_t start;
    clock_t end;

    start = clock();
    _arr = sortArr(_arr);
    end = clock();
    _timeVec = static_cast<double>(end - start);

    start = clock();
    _deq = sortDeq(_deq);
    end = clock();
    _timeDeq = static_cast<double>(end - start);

    std::cout << std::endl;
    std::cout << std::endl;
}