/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/18 19:44:51 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <exception>
#include "BitcoinExchange.hpp"

void printMap(std::map<std::string, double> givvenMap) {
    std::map<std::string, double>::iterator iter = givvenMap.begin();
    while (iter != givvenMap.end()) {
        std::cout << "key = " << iter->first << " val: " << iter->second << std::endl;
        iter++;
    }
}

std::map<std::string, double> convert_file_into_map(std::ifstream &file ) {
    std::string line;
    std::map<std::string, double> dictionary;

    if (!std::getline(file, line))
        return dictionary;
    while (std::getline(file, line)) {
        size_t comaInd = line.find(",");
        if (std::string::npos == comaInd) {
            continue;
        }
        std::string date = line.substr(0, comaInd);
        std::string priceStr = line.substr(comaInd  + 1, line.size() - 1);
        double price = std::atof(priceStr.c_str());
        dictionary[date] = price;
    }
    return (dictionary);
}


void parseInputLine(const std::string &line,
                    std::string *date,
                    std::string *value)
{
    size_t separator = line.find(" | ");
    if (separator == std::string::npos)
        return;

    *date = line.substr(0, separator);
    *value = line.substr(separator + 3);
}


int validateValue(double *val) {
    // double converted val
    if (val == NULL)
        return 404;
    else if (*val < 0)
        return 404;
    else if (*val > 1000)
        return 404;

    return 200;
}
int validateDate(const std::string &date) {
    if (date.size() != 10)
        return 404;
    if (date[4] != '-' || date[7] != '-')
        return 404;
    for (size_t i = 0; i < 10; i++) {
        if (i == 4 || i == 7)
            continue;
        if(!isdigit(date[i])) {
            return 404;
        }
    }
    int year = atoi(date.substr(0,3).c_str());
    int month = atoi(date.substr(5,6).c_str());
    int day = atoi(date.substr(8,9).c_str());

    if (month < 1 || month > 12)
        return 404;

    if (day < 1 || day > 31) {
        return 404;
    }
    
    return 200;
}

void processInput(std::ifstream &inputFile, const BitcoinExchange &btcEx)
{
    std::string line;
    std::string date;
    std::string value;
    double digitVal;
    double result;

    while (std::getline(inputFile, line))
    {
        parseInputLine(line, &date, &value);

        if (validateDate(date) == 404)
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        digitVal = atof(value.c_str());
        if (validateValue(&digitVal) == 404)
        {
            std::cerr << "Error: not valid value => " << value << std::endl;
            continue;
        }
        if (btcEx.convert(date, digitVal, &result) == 404) {
            std::cerr << "Error: wrong Date => " << date << std::endl;
            continue;
        }
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}

int main(int argc, char **argv) {

    std::ifstream db;
    std::ifstream inputFile;
    std::map<std::string, double> dict_db;
    BitcoinExchange btcEx;
    
    if (argc != 2 ) {
        std::cerr << "Error: Not enough args (input.txt is expected as an input)\n";
        return (1);
    }

    db.open("data.csv");
    if (!db.is_open()) {
        std::cerr << "Error: reading the data.csv \n";
        return (1);
    }
    dict_db = convert_file_into_map(db);
    db.close();
    btcEx = BitcoinExchange(dict_db);
    // printMap(dict_db); only for testing db
    
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: during the file openning\n";
        return (1);
    }
    
    processInput(inputFile, btcEx);
    inputFile.close();
    
    return (0);
}
