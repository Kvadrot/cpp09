/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:51:49 by ufo               #+#    #+#             */
/*   Updated: 2025/12/25 15:14:47 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <utility>

class PmergeMe {
private:
    std::vector<int> _arr;
    std::vector<int> _sortedArr;
    std::deque<int> _deq;
    std::deque<int> _sortedDeq;

    double _timeVec;
    double _timeDeq;
    
    std::vector<int> sortArr(const std::vector<int> &arr);
    std::deque<int> sortDeq(const std::deque<int> &deq);


    void splitArrIntoPairs(const std::vector<int> &arrToSplit, std::vector< std::pair<int,int> > &splitedPairs,
        bool &hasRemainder,int &remainder);
    void applySortingAlgo(std::vector<int> &big, std::vector<int> &small,
        bool &hasRemainder,int &remainder);
    
    void splitDequeIntoPairs(const std::deque<int> &deqToSplit, std::deque< std::pair<int,int> > &splitedPairs,
        bool &hasRemainder,int &remainder);
    void applySortingAlgoDeq(std::deque<int> &big, const std::deque<int> &small,
        bool hasRemainder, int remainder);

public:
    PmergeMe();
    PmergeMe(const std::vector<int> &v, const std::deque<int> &d);
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();
    
    void sort();
    std::vector<int> &getOGArr(void);
    std::vector<int> &getSortedArr(void);
    std::deque<int> &getOGDeq(void);
    std::deque<int> &getSortedDeq(void);
    double getSortTimeArray();
    double getSortTimeDeque();

};

#endif