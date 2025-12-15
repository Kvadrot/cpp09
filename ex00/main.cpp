/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:34 by ufo               #+#    #+#             */
/*   Updated: 2025/12/15 11:36:33 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

int main(int argc, char **argv) {

    std::ifstream db;
    std::ifstream inputFile;
    std::map<std::string, double> dict_db;
    
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
    printMap(dict_db);

    inputFile.open(argv[1]);
    // if (!inputFile.is_open()) {
    //     std::cerr << "Error: during the file openning\n";
    //     db.close();
    //     return (1);
    // }
    
    return (0);
}
