/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 08:45:55 by ufo               #+#    #+#             */
/*   Updated: 2025/12/19 20:20:19 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange:: BitcoinExchange() {};
BitcoinExchange::BitcoinExchange(const std::map<std::string, double> &mappedData) : _db(mappedData) {}

BitcoinExchange:: BitcoinExchange(const BitcoinExchange& other) {
    if (this != &other) {
        this->_db = other._db;
    }
}

BitcoinExchange &BitcoinExchange:: operator=(const BitcoinExchange &other) {
    if (this != &other) {
        this->_db = other._db;
    }
    return (*this);
}

BitcoinExchange:: ~BitcoinExchange() {}

std::map<std::string, double> BitcoinExchange:: getDB() {
    return this->_db;
}

int BitcoinExchange:: convert(const std::string &date, const double val, double *result) const {
    if (result == NULL)
        return 404;
    if (_db.empty() == true)
        return 404;
    std::map<std::string, double>::const_iterator dbRelevantIter = _db.lower_bound(date);
    if (dbRelevantIter == _db.begin() && dbRelevantIter->first > date) {
        return 404;
    } else {
        if (dbRelevantIter == _db.end() || dbRelevantIter->first != date)
            --dbRelevantIter;

        *result = val * dbRelevantIter->second;
    }
    return 200;
}
