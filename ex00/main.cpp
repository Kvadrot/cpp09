/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/19 20:32:08 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <cstdlib>

#include "BitcoinExchange.hpp"

/* ===================== CSV DB ===================== */

std::map<std::string, double> convert_file_into_map(std::ifstream &file)
{
    std::string line;
    std::map<std::string, double> dictionary;

    if (!std::getline(file, line)) // skip header
        return dictionary;

    while (std::getline(file, line))
    {
        size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue;

        std::string date = line.substr(0, comma);
        std::string priceStr = line.substr(comma + 1);

        // trim possible '\r'
        if (!priceStr.empty() && priceStr[priceStr.size() - 1] == '\r')
            priceStr.erase(priceStr.size() - 1);

        double price = std::atof(priceStr.c_str());
        dictionary[date] = price;
    }
    return dictionary;
}

/* ===================== INPUT PARSE ===================== */

int parseInputLine(const std::string &line,
                   std::string *date,
                   std::string *value)
{
    size_t sep = line.find(" | ");
    if (sep == std::string::npos)
        return 404;

    *date = line.substr(0, sep);
    *value = line.substr(sep + 3);
    return 200;
}

/* ===================== VALIDATION ===================== */

int validateDate(const std::string &date)
{
    if (date.size() != 10)
        return 404;

    if (date[4] != '-' || date[7] != '-')
        return 404;

    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return 404;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return 404;

    return 200;
}

int validateValue(const std::string &val)
{
    if (val.empty())
        return 404;

    int dotCount = 0;
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i] == '.')
            dotCount++;
        else if (!std::isdigit(val[i]))
            return 404;
    }

    if (dotCount > 1)
        return 404;

    double v = std::atof(val.c_str());

    if (v < 0)
        return 404;
    if (v > 1000)
        return 405;

    return 200;
}

/* ===================== INPUT PROCESS ===================== */

void processInput(std::ifstream &inputFile, const BitcoinExchange &btcEx)
{
    std::string line;
    std::string date;
    std::string value;

    if (!std::getline(inputFile, line)) // skip header
        return;

    while (std::getline(inputFile, line))
    {
        if (parseInputLine(line, &date, &value) == 404)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (validateDate(date) == 404)
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (validateValue(value) == 404)
        {
            std::cerr << "Error: not a positive number " << value << std::endl;
            continue;
        } else if (validateValue(value) == 405) {
            std::cerr << "Error: too big val => " << value << std::endl;
            continue;
        }

        double result;
        if (btcEx.convert(date, std::atof(value.c_str()), &result) == 404)
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}

/* ===================== MAIN ===================== */

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::ifstream db("data.csv");
    if (!db.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::map<std::string, double> dict_db = convert_file_into_map(db);
    db.close();

    BitcoinExchange btcEx(dict_db);

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    processInput(inputFile, btcEx);
    inputFile.close();

    return 0;
}