/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:59 by llacsivy          #+#    #+#             */
/*   Updated: 2025/04/28 20:47:40 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	
}

BitcoinExchange::BitcoinExchange(const std::string dataFile)
{
	parseData(dataFile);
// printData();
		std::cout << "_data map stored successfully" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::calcTurnOver(const std::string& inputFile)
{
	readInputLineByLine(inputFile);
}

void openFile(const std::string& dataFile, 	std::ifstream& file)
{
	file.open(dataFile);
	if (!file.is_open())
		throw std::runtime_error("open file failed!");
}

void BitcoinExchange::parseData(const std::string& dataFile)
{
	std::ifstream	file;
	std::string 	nextLine;
	bool			isFirstLine;
	
	isFirstLine = true;

	openFile(dataFile, file);
	while (std::getline(file, nextLine))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;	
		}
		parseDataLine(nextLine);
	}
	file.close();
}

void BitcoinExchange::parseDataLine(const std::string& nextLine)
{
	std::string			date;
	std::string			exchangeRateStr;
	double				exchangeRate;
	std::stringstream 	ss(nextLine);
	if (std::getline(ss, date, ',') && std::getline(ss, exchangeRateStr))
	{
		try
		{
			exchangeRate = std::stod(exchangeRateStr);
			if (isValidDate(date))
			{
				if(!(_data.insert({date, exchangeRate})).second)
				std::cerr << "duplicate date! taken: " << date << \
					"," << exchangeRate << std::endl;
			}
			else
				std::cerr << "invalid date: " << date << std::endl;
			
		}
		catch(const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}
}

void BitcoinExchange::readInputLineByLine(const std::string& inputFile)
{
	bool 				isFirstLine;
	std::ifstream		file;
	std::string 		nextLine;
	
	isFirstLine = true;
	openFile(inputFile, file);
	while (std::getline(file, nextLine))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}
		parseInputLine(nextLine);
	}
	file.close();
}

void BitcoinExchange::parseInputLine(std::string nextLine)
{
	std::string		valStr;
	nextLine.erase(std::remove(nextLine.begin(), nextLine.end(), ' '), nextLine.end());
	std::stringstream 	ss(nextLine);
	
	if (std::getline(ss, _inputDate, '|') && std::getline(ss, valStr))
	{
		//TODO check valid date here
		if (valStr.empty())
		{
			std::cerr << "Error: value is empty" << std::endl;
		}
		else
		{
			if (isUnsignedInt(valStr))
				_inputValue = convertToUnsignedInt(valStr);
			else
			{
std::cout << valStr << "\n";
				_inputValue = convertToFloat(valStr);
std::cout << _inputValue << "\n";
			}
			// else
			// {
			// 	std::cerr << "Error: invalid value" << std::endl;
			// 	return false;	
			// }
		}
	}
printInput();
}

template <typename T>
bool BitcoinExchange::isInRange(T value)
{
	if (value >= 0 && value <= 1000)
	{
		return true;
	}
	else
	{
		std::cerr << "Error: " << value << " not in range [0, 1000]" << std::endl;
		_inputValue = std::nan("");
if (std::isnan(_inputValue)) printInput();
		return false;
	}
}

void BitcoinExchange::printData()
{
	std::cout << "_data map:" << std::endl;
	for (const auto& pair : _data)
	{
		std::cout << std::fixed << std::setprecision(2);
		std::cout << pair.first << "," << pair.second << std::endl;
	}
}

void BitcoinExchange::printInput()
{
	if (std::isnan(_inputValue))
		std::cout << _inputDate << " | " << "nan" << std::endl;
	else
		std::cout << _inputDate << " | " << _inputValue << std::endl;
}
bool isValidDate(std::string date)
{	
	int year, month, day;
	char dash1, dash2;
	
	int daysInFebruary;
	std::istringstream iss(date);
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	if (!(iss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (month < 1 || month > 12)
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (isLeapYear(year))
		daysInFebruary = 29;
	else
		daysInFebruary = 28;
	int maxDaysOfMonth[12] = {31, daysInFebruary, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day < 1 || day > maxDaysOfMonth[month - 1])
		return false;
	return true;
}

bool isLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
		return true;
	else
		return false;
}
bool isUnsignedInt(std::string nbrStr)
{
	for (char c : nbrStr) 
	{
		if (!std::isdigit(c)) 
			return false;
	}
	return true;
}

unsigned int convertToUnsignedInt(std::string nbr)
{
	unsigned int unsignedIntVal;
	
	try
	{
		unsignedIntVal = static_cast<unsigned int>(std::stoul(nbr));
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	if (!isInRange(unsignedIntVal))
		std::cerr << "Error: conversion failed1" << std::endl;
	return unsignedIntVal;
}

float convertToFloat(std::string nbrStr)
{
	float floatVal;
	try
	{
		floatVal = std::stof(nbrStr);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	if (!isInRange(floatVal))
		std::cerr << "Error: conversion failed2" << std::endl;
	return floatVal;
}
