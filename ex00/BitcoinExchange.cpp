/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 08:45:55 by ufo               #+#    #+#             */
/*   Updated: 2025/12/17 19:09:34 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"



BitcoinExchange:: BitcoinExchange() {};
BitcoinExchange:: BitcoinExchange(std::map<std::string, double> mappedData) {
    _db = mappedData;
}

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

double BitcoinExchange:: convert(const std::string date, const std::string val) const {
    date + val;
    return 200;
}
