/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:51:52 by ufo               #+#    #+#             */
/*   Updated: 2025/12/25 15:16:13 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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

//=============== Print helpers ================================

// template <typename PairContainer>
// void printPairedContainer(const PairContainer &paired)
// {
//     for (size_t i = 0; i < paired.size(); i++)
//     {
//         std::cout
//             << "(small = " << paired[i].first
//             << " | big = " << paired[i].second
//             << ") ";
//     }
//     std::cout << std::endl;
// }

// template <typename Container>
// void printContainer(const Container &c)
// {
//     typename Container::const_iterator it = c.begin();
//     while (it != c.end())
//     {
//         std::cout << *it << " ";
//         ++it;
//     }
//     std::cout << std::endl;
// }

//===================== Getters ========================
    std::vector<int> &PmergeMe:: getOGArr(void) {
        return _arr;
    }
    std::vector<int> &PmergeMe:: getSortedArr(void){
        return _sortedArr;
    }
    std::deque<int> &PmergeMe:: getOGDeq(void) {
        return _deq;
    }
    std::deque<int> &PmergeMe:: getSortedDeq(void){
        return _sortedDeq;
    }

    double PmergeMe:: getSortTimeArray() {
        return _timeVec;
    }
    
    double PmergeMe:: getSortTimeDeque() {
        return _timeDeq;
    }

// ++++++++ ================== ++++++++++++ ======================= +++++++++++++

//========================== Deque Part =========================================

// file-private: binary search insertion position for deque
static size_t findPosWithBinarySearchDeq(int value,
                                        const std::deque<int> &big,
                                        size_t left,
                                        size_t right)
{
    if (left >= right)
        return left;

    size_t mid = (left + right) / 2;

    if (value < big[mid])
        return findPosWithBinarySearchDeq(value, big, left, mid);
    else
        return findPosWithBinarySearchDeq(value, big, mid + 1, right);
}

void PmergeMe::applySortingAlgoDeq(std::deque<int> &big, const std::deque<int> &small,
    bool hasRemainder, int remainder)
{
    for (size_t i = 0; i < small.size(); i++)
    {
        int x = small[i];
        size_t pos = findPosWithBinarySearchDeq(x, big, 0, big.size());
        big.insert(big.begin() + pos, x);
    }

    if (hasRemainder)
    {
        size_t pos = findPosWithBinarySearchDeq(remainder, big, 0, big.size());
        big.insert(big.begin() + pos, remainder);
    }
}

void PmergeMe::splitDequeIntoPairs(const std::deque<int> &deqToSplit,
                                  std::deque< std::pair<int,int> > &splitedPairs,
                                  bool &hasRemainder,
                                  int &remainder)
{
    size_t deqSize;
    splitedPairs.clear();

    if (deqToSplit.size() % 2 != 0)
    {
        hasRemainder = true;
        deqSize = deqToSplit.size() - 1;
        remainder = deqToSplit[deqToSplit.size() - 1];
    }
    else
    {
        hasRemainder = false;
        deqSize = deqToSplit.size();
        remainder = 0;
    }

    for (size_t i = 0; i + 1 < deqSize; i += 2)
    {
        int smaller = deqToSplit[i];
        int bigger  = deqToSplit[i + 1];

        if (smaller > bigger)
            std::swap(smaller, bigger);

        splitedPairs.push_back(std::make_pair(smaller, bigger));
    }
}

std::deque<int> PmergeMe::sortDeq(const std::deque<int> &deq)
{
    if (deq.size() <= 1)
        return deq;

    std::deque< std::pair<int,int> > splitedPairs;
    bool hasRemainder = false;
    int remainder = 0;

    splitDequeIntoPairs(deq, splitedPairs, hasRemainder, remainder);

    std::deque<int> bigNums;
    std::deque<int> smallNums;

    for (size_t i = 0; i < splitedPairs.size(); i++)
    {
        smallNums.push_back(splitedPairs[i].first);
        bigNums.push_back(splitedPairs[i].second);
    }

    bigNums = sortDeq(bigNums);

    applySortingAlgoDeq(bigNums, smallNums, hasRemainder, remainder);

    return bigNums;
}
// ++++++++ ================== ++++++++++++ ======================= +++++++++++++

//========================== ArrayPart ===========================================
static size_t findPosWithBinarySearch(int smallNum, std::vector<int> &bigArr, size_t left, size_t right) {

    if (left >= right)
        return left;

    size_t mid = (left + right) / 2;

    if (smallNum < bigArr[mid])
        return findPosWithBinarySearch(smallNum, bigArr, left, mid);
    else
        return findPosWithBinarySearch(smallNum, bigArr,  mid + 1, right);
}

void PmergeMe::applySortingAlgo(std::vector<int> &bigArr, std::vector<int> &small,
        bool &hasRemainder,int &remainder) {
        
    size_t pos;
    std::vector<int>::iterator iter;

    for (size_t i = 0; i < small.size(); i++) {
        int smallNum = small[i];
        pos = findPosWithBinarySearch(smallNum, bigArr, 0, bigArr.size());
        iter = bigArr.begin() + pos;
        bigArr.insert(iter, smallNum);
    }

    if (hasRemainder == true) {
        pos = findPosWithBinarySearch(remainder, bigArr, 0, bigArr.size());
        iter = iter = bigArr.begin() + pos;
        bigArr.insert(iter, remainder);
    }
}

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

std::vector<int> PmergeMe::sortArr(const std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return arr;

    std::vector< std::pair<int,int> > splitedPairs;
    bool hasRemainder = false;
    int remainder = 0;

    splitArrIntoPairs(arr, splitedPairs, hasRemainder, remainder);

    std::vector<int> bigNums;
    std::vector<int> smallNums;

    for (size_t i = 0; i < splitedPairs.size(); i++)
    {
        smallNums.push_back(splitedPairs[i].first);
        bigNums.push_back(splitedPairs[i].second);
    }

    bigNums = sortArr(bigNums);

    applySortingAlgo(bigNums, smallNums, hasRemainder, remainder);

    return bigNums;
}
// ++++++++ ================== ++++++++++++ ======================= +++++++++++++


void PmergeMe::sort()
{
    clock_t start;
    clock_t end;

    start = clock();
    _sortedArr = sortArr(_arr);
    end = clock();
    _timeVec = (static_cast<double>(end - start) * 1000000.0)
               / CLOCKS_PER_SEC;

    start = clock();
    _sortedDeq = sortDeq(_deq);
    end = clock();
    _timeDeq = (static_cast<double>(end - start) * 1000000.0)
               / CLOCKS_PER_SEC;
}